"""
STM32F4 clock tree decoder.

Reads RCC registers via J-Link and computes:
  - System clock frequency and source
  - Bus frequencies (AHB, APB1, APB2)
  - PLL configuration
  - Which peripherals have their clocks enabled
"""

HSI_FREQ = 16_000_000


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


def _pllp_div(val: int) -> int:
    return {0: 2, 1: 4, 2: 6, 3: 8}.get(val, 2)


def _get_field(reg_value: int, lsb: int, width: int) -> int:
    mask = (1 << width) - 1
    return (reg_value >> lsb) & mask


class ClockTreeF4:
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

    def _read_all(self):
        self.CR = self._r("CR")
        self.PLLCFGR = self._r("PLLCFGR")
        self.CFGR = self._r("CFGR")

    def _compute_pll(self) -> dict:
        src = _get_field(self.PLLCFGR, 22, 1)
        if src == 0:
            pll_src_name = "HSI"
            pll_src_freq = HSI_FREQ
        else:
            hse_rdy = (self.CR >> 17) & 1
            pll_src_name = "HSE" + (" (ready)" if hse_rdy else " (not ready)")
            pll_src_freq = 25_000_000

        m = _get_field(self.PLLCFGR, 0, 6)
        n = _get_field(self.PLLCFGR, 6, 9)
        p = _get_field(self.PLLCFGR, 16, 2)
        q = _get_field(self.PLLCFGR, 24, 4)

        if m == 0:
            m = 1
        vco = pll_src_freq // m * n

        p_div = _pllp_div(p)
        return {
            "source": f"{pll_src_name} ({pll_src_freq/1e6:.0f} MHz)",
            "M": m,
            "N": n,
            "VCO": vco,
            "P": vco // p_div,
            "P_div": p_div,
            "Q": vco // q if q else 0,
        }

    def compute(self) -> dict:
        sw = _get_field(self.CFGR, 2, 2)    # SWS (status), bits 2:3, not SW (requested) bits 0:1
        hse_rdy = bool((self.CR >> 17) & 1)

        if sw == 0:
            sysclk = HSI_FREQ
            sysclk_src = f"HSI ({HSI_FREQ/1e6:.0f} MHz)"
        elif sw == 1:
            sysclk = 25_000_000 if hse_rdy else 0
            sysclk_src = "HSE" + (" (ready)" if hse_rdy else " (not ready)")
        elif sw == 2:
            pll = self._compute_pll()
            sysclk = pll["P"]
            sysclk_src = f"PLL ({sysclk/1e6:.0f} MHz)"
        else:
            sysclk = 0
            sysclk_src = "unknown"

        hp = _get_field(self.CFGR, 4, 4)
        ahb = sysclk // _prescaler_ahb(hp)

        ppre1 = _get_field(self.CFGR, 10, 3)
        ppre2 = _get_field(self.CFGR, 13, 3)
        apb1 = ahb // _prescaler_apb(ppre1)
        apb2 = ahb // _prescaler_apb(ppre2)

        result = {
            "sysclk": sysclk,
            "sysclk_src": sysclk_src,
            "ahb": ahb,
            "apb1": apb1,
            "apb2": apb2,
            "hsi": HSI_FREQ,
            "hse_ready": hse_rdy,
            "pll_on": bool((self.CR >> 24) & 1),
        }

        if result["pll_on"]:
            result["pll"] = self._compute_pll()

        return result

    def peripheral_clocks(self) -> list[dict]:
        results = []
        enr_regs = [
            ("AHB1", "AHB1ENR"),
            ("AHB2", "AHB2ENR"),
            ("AHB3", "AHB3ENR"),
            ("APB1", "APB1ENR"),
            ("APB2", "APB2ENR"),
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
    ct = ClockTreeF4(jlink, svd_peripherals)
    info = ct.compute()
    lines = []

    lines.append("Clock Tree (STM32F4)")
    lines.append("=" * 40)
    lines.append(f"  SYSCLK:  {info['sysclk']/1e6:.0f} MHz  ({info['sysclk_src']})")
    lines.append(f"")
    lines.append(f"  Bus Tree:")
    lines.append(f"    AHB:    {info['ahb']/1e6:.0f} MHz")
    lines.append(f"    APB1:   {info['apb1']/1e6:.0f} MHz")
    lines.append(f"    APB2:   {info['apb2']/1e6:.0f} MHz")
    lines.append(f"")
    lines.append(f"  HSI:     {HSI_FREQ/1e6:.0f} MHz")
    lines.append(f"  HSE:     {'ready' if info['hse_ready'] else 'not ready'}")

    if info["pll_on"]:
        pll = info["pll"]
        lines.append(f"")
        lines.append(f"  PLL: ON")
        lines.append(f"    Source:  {pll['source']}")
        lines.append(f"    M/N/P:   {pll['M']}/{pll['N']}/{pll['P_div']}")
        lines.append(f"    VCO:     {pll['VCO']/1e6:.0f} MHz")
        lines.append(f"    P:       {pll['P']/1e6:.0f} MHz")
        if pll["Q"]:
            lines.append(f"    Q:       {pll['Q']/1e6:.0f} MHz")
    else:
        lines.append(f"")
        lines.append(f"  PLL: OFF")

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
