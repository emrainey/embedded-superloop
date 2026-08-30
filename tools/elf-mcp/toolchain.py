"""Toolchain resolution for the ARM GNU binutils used by elf-mcp.

Resolves the ``arm-none-eabi-{size,nm,readelf,objdump,addr2line}`` executables
by searching (in order):

1. Install trees under ``/Applications/ArmGNUToolchain/**/arm-none-eabi/bin``
   (newest version wins),
2. ``/opt/homebrew/bin`` and ``/usr/local/bin``,
3. ``$PATH`` (``shutil.which``).

A ``binutils`` runner is provided so tools can be unit tested with a fake
executable resolver.
"""

from __future__ import annotations

import glob
import shutil
import subprocess
from dataclasses import dataclass
from typing import Callable, Protocol

#: Tool names we are interested in.
TOOL_NAMES = ("size", "nm", "readelf", "objdump", "addr2line")

#: Candidate install roots on this host (Darwin oriented, Harmless if absent).
CANDIDATE_ROOTS = (
    "/Applications/ArmGNUToolchain",
    "/Applications/arm-gnu-toolchain",
)


def _arm_install_bin_dirs() -> list[str]:
    """Return candidate ``arm-none-eabi/bin`` directories, newest release first."""
    dirs: list[str] = []
    for root in CANDIDATE_ROOTS:
        for release_dir in glob.glob(f"{root}/*"):
            bin_dir = f"{release_dir}/arm-none-eabi/bin"
            if glob.glob(f"{bin_dir}/arm-none-eabi-size"):
                dirs.append(bin_dir)
    # Newest release first (versions like "14.2.rel1" sort lexicographically close
    # enough for our purposes; a numeric sort below is more robust).
    def _version_key(path: str) -> tuple[int, ...]:
        tail = path.split("/")[-2]
        nums = []
        for part in tail.split("."):
            digits = "".join(ch for ch in part if ch.isdigit())
            try:
                nums.append(int(digits))
            except ValueError:
                nums.append(0)
        return tuple(nums)

    dirs.sort(key=_version_key, reverse=True)
    return dirs


def resolve_binutils_tool(tool: str, root: str | None = None) -> str | None:
    """Return the absolute path to a binutils tool, or ``None`` if not found.

    ``tool`` is the short name without the ``arm-none-eabi-`` prefix (e.g.
    ``"size"``).  ``root`` optionally points at an explicit
    ``.../arm-none-eabi/bin`` directory to skip all discovery.
    """
    if tool not in TOOL_NAMES:
        raise ValueError(f"unsupported binutils tool: {tool!r}")
    if root:
        cand = f"{root}/arm-none-eabi-{tool}"
        return cand if glob.glob(cand) else None
    for bin_dir in _arm_install_bin_dirs():
        cand = f"{bin_dir}/arm-none-eabi-{tool}"
        if glob.glob(cand):
            return cand
    return shutil.which(f"arm-none-eabi-{tool}")


@dataclass
class CommandResult:
    """Result of running a binutils command."""

    returncode: int
    stdout: str
    stderr: str


class BinutilsRunner(Protocol):
    """Minimal runner protocol; tools accept any callable matching it."""

    def __call__(self, tool: str, args: list[str], *, cwd: str | None = None) -> CommandResult:
        ...


def run_binutils(tool: str, args: list[str], *, root: str | None = None,
                 cwd: str | None = None, timeout: float = 60.0) -> CommandResult:
    """Run ``arm-none-eabi-<tool> <args>`` and return its captured output.

    Raises ``FileNotFoundError`` if the tool cannot be resolved.
    """
    exe = resolve_binutils_tool(tool, root=root)
    if exe is None:
        raise FileNotFoundError(
            f"arm-none-eabi-{tool} not found in any known location; install the ARM "
            "GNU toolchain or add it to $PATH"
        )
    proc = subprocess.run(
        [exe, *args],
        capture_output=True,
        text=True,
        cwd=cwd,
        timeout=timeout,
        check=False,
    )
    return CommandResult(proc.returncode, proc.stdout or "", proc.stderr or "")


def make_runner(root: str | None = None) -> BinutilsRunner:
    """Factory for a runner bound to a specific toolchain root (or auto-detected)."""

    def runner(tool: str, args: list[str], *, cwd: str | None = None) -> CommandResult:
        return run_binutils(tool, args, root=root, cwd=cwd)

    return runner