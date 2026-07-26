import os
import xml.etree.ElementTree as ET
from glob import glob

_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
_SVD_CACHE: dict[str, dict] = {}


def _parse_int(text: str) -> int:
    text = text.strip()
    if text.startswith("0x") or text.startswith("0X"):
        return int(text, 16)
    return int(text)


def _find_svd_files() -> list[dict]:
    repo_root = os.path.normpath(os.path.join(_SCRIPT_DIR, "../.."))
    files = []
    for svd_path in glob(os.path.join(repo_root, "**/*.svd"), recursive=True):
        rel = os.path.relpath(svd_path, repo_root)
        files.append({"path": rel, "absolute": os.path.abspath(svd_path)})
    return files


def _parse_all_peripherals(svd_path: str) -> dict:
    abs_path = os.path.abspath(svd_path)
    if abs_path in _SVD_CACHE:
        return _SVD_CACHE[abs_path]

    if not os.path.isfile(abs_path):
        raise FileNotFoundError(f"SVD file not found: {abs_path}")

    tree = ET.parse(abs_path)
    root = tree.getroot()
    result = {}

    for p in root.iter("peripheral"):
        name = p.findtext("name", "").strip()
        if not name:
            continue
        base = _parse_int(p.findtext("baseAddress", "0"))
        registers = {}
        for reg in p.iter("register"):
            rname = reg.findtext("name", "").strip()
            if not rname:
                continue
            offset = _parse_int(reg.findtext("addressOffset", "0"))
            reset = _parse_int(reg.findtext("resetValue", "0"))
            desc = (reg.findtext("description") or "").strip()
            size = _parse_int(reg.findtext("size", "32"))
            fields = {}
            for field in reg.iter("field"):
                fname = field.findtext("name", "").strip()
                if not fname:
                    continue
                lsb = _parse_int(field.findtext("bitOffset", "0"))
                width = _parse_int(field.findtext("bitWidth", "1"))
                fdesc = (field.findtext("description") or "").strip()
                fields[fname] = {"lsb": lsb, "width": width, "description": fdesc}
            registers[rname] = {
                "offset": offset,
                "address": base + offset,
                "reset": reset,
                "size": size,
                "description": desc,
                "fields": fields,
            }
        result[name] = {"base": base, "registers": registers}

    _SVD_CACHE[abs_path] = result
    return result


def list_svds() -> list[dict]:
    return _find_svd_files()


def list_peripherals(svd_path: str) -> list[dict]:
    data = _parse_all_peripherals(svd_path)
    results = []
    for name, info in sorted(data.items()):
        results.append({
            "name": name,
            "baseAddress": f"0x{info['base']:08X}",
            "registerCount": len(info["registers"]),
        })
    return results


def list_registers(svd_path: str, peripheral: str) -> list[dict]:
    data = _parse_all_peripherals(svd_path)
    p = data.get(peripheral)
    if not p:
        return []
    results = []
    for rname, info in sorted(p["registers"].items()):
        results.append({
            "name": rname,
            "offset": f"0x{info['offset']:04X}",
            "address": f"0x{info['address']:08X}",
            "size": info["size"],
            "description": info["description"],
            "fieldCount": len(info["fields"]),
        })
    return results


def get_register(svd_path: str, peripheral: str, register: str) -> dict | None:
    data = _parse_all_peripherals(svd_path)
    p = data.get(peripheral)
    if not p:
        return None
    r = p["registers"].get(register)
    if not r:
        return None
    fields = []
    for fname, finfo in sorted(r["fields"].items(), key=lambda x: -x[1]["lsb"]):
        mask = ((1 << finfo["width"]) - 1) << finfo["lsb"]
        fields.append({
            "name": fname,
            "lsb": finfo["lsb"],
            "width": finfo["width"],
            "mask": f"0x{mask:08X}",
            "description": finfo["description"],
        })
    return {
        "peripheral": peripheral,
        "register": register,
        "offset": f"0x{r['offset']:04X}",
        "address": f"0x{r['address']:08X}",
        "size": r["size"],
        "resetValue": f"0x{r['reset']:08X}",
        "description": r["description"],
        "fields": fields,
    }
