"""
STM32H7 clock tree decoder.

Reads RCC registers via J-Link and computes:
  - System clock frequency and source
  - Bus frequencies (AHB, APB1, APB2, APB3, APB4)
  - PLL configuration
  - Which peripherals have their clocks enabled
"""

HSI_FREQ = 64_000_000
CSI_FREQ = 4_000_000
HSI48_FREQ = 48_000_000


def _prescaler_ahb(val: int) -> int:
    if val < 8:
        return 1
    table = {8: 2, 9: 4, 10: 8, 11: 16, 12: 64, 13: 128, 14: 256, 15: 512}
    return table.get(val, 1)


def _prescaler_apb(val: int) -> int:
    if val < 4:
        return 1
    table = {4: 2, 5: 4, 6: 8, 7: 16}
    return table.get(val, 1)


def _prescaler_cpu(val: int) -> int:
    return 1 if val == 0 else 2


def _hsidiv(val: int) -> int:
    table = {0: 1, 1: 2, 2: 4, 3: 8}
    return table.get(val, 1)


def _get_field(reg_value: int, lsb: int, width: int) -> int:
    mask = (1 << width) - 1
    return (reg_value >> lsb) & mask


class ClockTreeH7:
    def __init__(self, jlink, svd_peripherals: dict):
        self.jlink = jlink
        self.rcc_info = svd_peripherals.get("RCC", {})
        self.regs = self.rcc_info.get("registers", {})
        self._read_all()

    def _r(self, name: str) -> int:
        r = self.regs.get(name)
        if not r:
            return 0
        try:
            return self.jlink.memory_read32(self.rcc_info["base"] + r["offset"], 1)[0]
        except Exception:
            return 0

    def _fields_of(self, regname: str) -> dict:
        r = self.regs.get(regname)
        return r["fields"] if r else {}

    def _read_all(self):
        self.CR = self._r("CR")
        self.CFGR = self._r("CFGR")
        self.D1CFGR = self._r("D1CFGR")
        self.D2CFGR = self._r("D2CFGR")
        self.D3CFGR = self._r("D3CFGR")
        self.PLLCKSELR = self._r("PLLCKSELR")
        self.PLLCFGR = self._r("PLLCFGR")
        self.PLL1DIVR = self._r("PLL1DIVR")
        self.PLL2DIVR = self._r("PLL2DIVR")
        self.PLL3DIVR = self._r("PLL3DIVR")

    def _osc_source(self) -> tuple[str, int]:
        src = _get_field(self.PLLCKSELR, 0, 2)
        if src == 0:
            hsidiv = _hsidiv(_get_field(self.CR, 3, 2))
            return ("HSI", HSI_FREQ // hsidiv)
        if src == 1:
            if self.CR & (1 << 17):
                return ("HSE (ready)", 25_000_000)
            return ("HSE (not ready)", 25_000_000)
        if src == 3:
            return ("CSI", CSI_FREQ)
        return ("no clock", 0)

    def _compute_pll(self, m_lsb: int, m_width: int, divr_val: int,
                     p_field_lsb: int, q_field_lsb: int, r_field_lsb: int,
                     p_en_bit: int, q_en_bit: int, r_en_bit: int) -> dict:
        pllsrc_name, pllsrc_freq = self._osc_source()
        m_val = _get_field(self.PLLCKSELR, m_lsb, m_width)
        m = m_val if m_val != 0 else 1  # DIVMx is raw value (1-63), not +1 encoded
        n = _get_field(divr_val, 0, 9) + 1
        vco = pllsrc_freq // m * n

        p_en = (self.PLLCFGR >> p_en_bit) & 1
        q_en = (self.PLLCFGR >> q_en_bit) & 1
        r_en = (self.PLLCFGR >> r_en_bit) & 1
        p_div = _get_field(divr_val, 9, 7) + 1  # P = reg + 1 (not 2x)
        q_div = _get_field(divr_val, 16, 7) + 1
        r_div = _get_field(divr_val, 24, 7) + 1

        return {
            "source": f"{pllsrc_name} ({pllsrc_freq/1e6:.0f} MHz)",
            "M": m,
            "N": n,
            "VCO": vco,
            "P": vco // p_div if p_en and p_div else 0,
            "Q": vco // q_div if q_en and q_div else 0,
            "R": vco // r_div if r_en and r_div else 0,
            "P_en": p_en,
            "Q_en": q_en,
            "R_en": r_en,
        }

    def _compute_pll1(self) -> dict:
        return self._compute_pll(
            m_lsb=4, m_width=6,
            divr_val=self.PLL1DIVR,
            p_field_lsb=9, q_field_lsb=16, r_field_lsb=24,
            p_en_bit=16, q_en_bit=17, r_en_bit=18,
        )

    def _compute_pll2(self) -> dict:
        return self._compute_pll(
            m_lsb=12, m_width=6,
            divr_val=self.PLL2DIVR,
            p_field_lsb=9, q_field_lsb=16, r_field_lsb=24,
            p_en_bit=19, q_en_bit=20, r_en_bit=21,
        )

    def compute(self) -> dict:
        sws = _get_field(self.CFGR, 3, 3)
        hsidiv_val = _hsidiv(_get_field(self.CR, 3, 2))
        hsi = HSI_FREQ // hsidiv_val
        hse_rdy = (self.CR >> 17) & 1
        pll1_on = bool((self.CR >> 24) & 1)
        pll1_rdy = bool((self.CR >> 25) & 1)
        pll2_on = bool((self.CR >> 26) & 1)
        pll2_rdy = bool((self.CR >> 27) & 1)
        pll3_on = bool((self.CR >> 28) & 1)

        sysclk = hsi
        sysclk_src = f"HSI ({hsi/1e6:.0f} MHz)"
        sysclk_note = ""

        if sws == 0:
            pass  # HSI, already set
        elif sws == 1:
            sysclk = CSI_FREQ
            sysclk_src = f"CSI ({CSI_FREQ/1e6:.0f} MHz)"
        elif sws == 2:
            sysclk = 25_000_000 if hse_rdy else 0
            sysclk_src = "HSE" + (" (ready)" if hse_rdy else " (not ready)")
        elif sws == 3:
            pll1 = self._compute_pll1()
            if pll1_on and pll1_rdy:
                sysclk = pll1["P"]
                sysclk_src = f"PLL1P ({pll1['P']/1e6:.0f} MHz)"
            else:
                sysclk = hsi
                sysclk_src = f"PLL1P (selected but not ready! actual: HSI {hsi/1e6:.0f} MHz)"
        elif sws == 4:
            pll2 = self._compute_pll2()
            if pll2_on and pll2_rdy:
                sysclk = pll2["P"]
                sysclk_src = f"PLL2P ({pll2['P']/1e6:.0f} MHz)"
            else:
                sysclk = hsi
                sysclk_src = f"PLL2P (selected but not ready! actual: HSI {hsi/1e6:.0f} MHz)"
        elif sws == 5:
            sysclk = 0
            sysclk_src = "PLL3P (selected but not computed)"
        else:
            sysclk_src = f"unknown ({sws})"

        hp = _get_field(self.D1CFGR, 0, 4)
        ahb = sysclk // _prescaler_ahb(hp)

        ppre1 = _get_field(self.D2CFGR, 4, 3)
        ppre2 = _get_field(self.D2CFGR, 8, 3)
        ppre3 = _get_field(self.D1CFGR, 4, 3)
        ppre4 = _get_field(self.D3CFGR, 4, 3)

        apb1 = ahb // _prescaler_apb(ppre1)
        apb2 = ahb // _prescaler_apb(ppre2)
        apb3 = ahb // _prescaler_apb(ppre3)
        apb4 = ahb // _prescaler_apb(ppre4)

        cpu_pre = _get_field(self.D1CFGR, 8, 4)
        cpu_clk = sysclk // _prescaler_cpu(cpu_pre)

        pll1 = self._compute_pll1()
        result = {
            "sysclk": sysclk,
            "sysclk_src": sysclk_src,
            "sysclk_note": sysclk_note,
            "cpu": cpu_clk,
            "ahb": ahb,
            "apb1": apb1,
            "apb2": apb2,
            "apb3": apb3,
            "apb4": apb4,
            "hsi": hsi,
            "hse_ready": bool(hse_rdy),
            "pll1": pll1,
            "pll1_on": bool((self.CR >> 24) & 1),
            "pll2_on": bool((self.CR >> 26) & 1),
            "pll3_on": bool((self.CR >> 28) & 1),
        }
        if result["pll2_on"]:
            result["pll2"] = self._compute_pll2()
        if result["pll3_on"]:
            # Same structure but with M from DIVM3
            result["pll3"] = self._compute_pll(
                m_lsb=20, m_width=6, divr_val=self.PLL3DIVR,
                p_field_lsb=9, q_field_lsb=16, r_field_lsb=24,
                p_en_bit=22, q_en_bit=23, r_en_bit=24,
            )
        return result

    def peripheral_clocks(self) -> list[dict]:
        results = []
        enr_regs = [
            ("AHB1", "C1_AHB1ENR" if "C1_AHB1ENR" in self.regs else "AHB1ENR"),
            ("AHB2", "C1_AHB2ENR" if "C1_AHB2ENR" in self.regs else "AHB2ENR"),
            ("AHB3", "C1_AHB3ENR" if "C1_AHB3ENR" in self.regs else "AHB3ENR"),
            ("AHB4", "C1_AHB4ENR" if "C1_AHB4ENR" in self.regs else "AHB4ENR"),
            ("APB1", "C1_APB1LENR" if "C1_APB1LENR" in self.regs else "APB1LENR"),
            ("APB2", "C1_APB2ENR" if "C1_APB2ENR" in self.regs else "APB2ENR"),
            ("APB3", "C1_APB3ENR" if "C1_APB3ENR" in self.regs else "APB3ENR"),
            ("APB4", "C1_APB4ENR" if "C1_APB4ENR" in self.regs else "APB4ENR"),
        ]
        for bus_name, reg_name in enr_regs:
            r = self.regs.get(reg_name)
            if not r:
                continue
            addr = self.rcc_info["base"] + r["offset"]
            try:
                value = self.jlink.memory_read32(addr, 1)[0]
            except Exception:
                continue
            for fname, finfo in sorted(r["fields"].items(), key=lambda x: x[1]["lsb"]):
                bit = finfo["lsb"]
                enabled = bool((value >> bit) & 1)
                per_name = fname.replace("_EN", "").replace("EN", "")
                results.append({
                    "peripheral": per_name,
                    "bus": bus_name,
                    "enabled": enabled,
                    "bit": bit,
                })
        return results


def dump_clock_tree(jlink, svd_peripherals: dict) -> str:
    ct = ClockTreeH7(jlink, svd_peripherals)
    info = ct.compute()
    lines = []

    lines.append("Clock Tree (STM32H7)")
    lines.append("=" * 40)
    lines.append(f"  SYSCLK:  {info['sysclk']/1e6:.0f} MHz  ({info['sysclk_src']})")
    if info.get("sysclk_note"):
        lines.append(f"  {info['sysclk_note']}")
    lines.append(f"  CPU:     {info['cpu']/1e6:.0f} MHz")
    lines.append(f"")
    lines.append(f"  Bus Tree:")
    lines.append(f"    AHB:    {info['ahb']/1e6:.0f} MHz")
    lines.append(f"    APB1:   {info['apb1']/1e6:.0f} MHz")
    lines.append(f"    APB2:   {info['apb2']/1e6:.0f} MHz")
    lines.append(f"    APB3:   {info['apb3']/1e6:.0f} MHz")
    lines.append(f"    APB4:   {info['apb4']/1e6:.0f} MHz")
    lines.append(f"")
    lines.append(f"  HSI:     {info['hsi']/1e6:.0f} MHz")
    lines.append(f"  HSE:     {'ready' if info['hse_ready'] else 'not ready'}")

    p1 = info["pll1"]
    lines.append(f"")
    lines.append(f"  PLL1: {'ON' if info['pll1_on'] else 'OFF'}")
    if info["pll1_on"]:
        lines.append(f"    Source:  {p1['source']}")
        lines.append(f"    M/N:     {p1['M']}/{p1['N']}")
        lines.append(f"    VCO:     {p1['VCO']/1e6:.0f} MHz")
        if p1["P_en"]:
            lines.append(f"    P:       {p1['P']/1e6:.0f} MHz  (/{(p1['VCO']//p1['P']) if p1['P'] else 0})")
        if p1["Q_en"]:
            lines.append(f"    Q:       {p1['Q']/1e6:.0f} MHz")
        if p1["R_en"]:
            lines.append(f"    R:       {p1['R']/1e6:.0f} MHz")

    if info["pll2_on"]:
        p2 = info.get("pll2", {})
        lines.append(f"")
        lines.append(f"  PLL2: ON")
        if p2.get("VCO", 0) > 0:
            lines.append(f"    Source:  {p2.get('source', '?')}")
            lines.append(f"    M/N:     {p2['M']}/{p2['N']}")
            lines.append(f"    VCO:     {p2['VCO']/1e6:.0f} MHz")
            if p2["P_en"]:
                lines.append(f"    P:       {p2['P']/1e6:.0f} MHz")
            if p2["Q_en"]:
                lines.append(f"    Q:       {p2['Q']/1e6:.0f} MHz")
            if p2["R_en"]:
                lines.append(f"    R:       {p2['R']/1e6:.0f} MHz")

    # --- Peripheral clocks ---
    per_clocks = ct.peripheral_clocks()
    enabled = [p for p in per_clocks if p["enabled"]]
    if enabled:
        lines.append(f"")
        lines.append(f"  Peripheral Clocks Enabled ({len(enabled)}):")
        lines.append(f"    {'Peripheral':25s} {'Bus':6s}")
        lines.append(f"    {'-'*25} {'-'*6}")
        for p in sorted(enabled, key=lambda x: (x["bus"], x["peripheral"])):
            lines.append(f"    {p['peripheral']:25s} {p['bus']:6s}")

    return "\n".join(lines)
