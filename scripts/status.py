#!/usr/bin/env python3
"""Resolve firmware addresses to source file and line information.

This script accepts either direct addresses or a log file/stdin containing
addresses. It resolves each address using an ELF with debug symbols via
addr2line, and optionally provides a nearest-symbol hint from a linker MAP file.
"""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple


HEX_RE = re.compile(r"0x[0-9a-fA-F]+")
MAP_ADDR_RE = re.compile(r"^\s*(0x[0-9a-fA-F]+)\s+(.*\S)\s*$")


@dataclass(frozen=True)
class AddressOccurrence:
	address: int
	raw: str
	line_number: Optional[int] = None
	line_text: Optional[str] = None


@dataclass(frozen=True)
class SymbolizedAddress:
	original: int
	normalized: int
	function: str
	file_line: str
	map_hint: Optional[str]

	@property
	def thumb_bit_cleared(self) -> bool:
		return self.original != self.normalized


class MapResolver:
	"""Best-effort MAP parser to provide nearest-address symbol hints."""

	def __init__(self, entries: Sequence[Tuple[int, str]]) -> None:
		self._entries = sorted(entries, key=lambda item: item[0])

	@classmethod
	def from_file(cls, path: Path) -> "MapResolver":
		entries: List[Tuple[int, str]] = []
		with path.open("r", encoding="utf-8", errors="replace") as infile:
			for line in infile:
				match = MAP_ADDR_RE.match(line)
				if not match:
					continue

				address = int(match.group(1), 16)
				detail = match.group(2).strip()

				# Skip lines that are usually just "address size" rows.
				if detail.startswith("0x"):
					continue

				entries.append((address, detail))

		return cls(entries)

	def find_hint(self, address: int) -> Optional[str]:
		if not self._entries:
			return None

		lo = 0
		hi = len(self._entries) - 1
		best_index = -1

		while lo <= hi:
			mid = (lo + hi) // 2
			candidate_addr = self._entries[mid][0]
			if candidate_addr <= address:
				best_index = mid
				lo = mid + 1
			else:
				hi = mid - 1

		if best_index < 0:
			return None

		base_addr, label = self._entries[best_index]
		offset = address - base_addr
		return f"{label} +0x{offset:x}"


def find_addr2line(explicit_tool: Optional[str]) -> str:
	candidates: List[str] = []
	if explicit_tool:
		candidates.append(explicit_tool)
	candidates.extend(
		[
			"arm-none-eabi-addr2line",
			"llvm-addr2line",
			"addr2line",
		]
	)

	for tool in candidates:
		resolved = shutil.which(tool)
		if resolved:
			return resolved

	candidate_list = ", ".join(candidates)
	raise RuntimeError(
		"Unable to find an addr2line tool in PATH. "
		f"Tried: {candidate_list}. Use --tool to set one explicitly."
	)


def normalize_pc_address(address: int) -> int:
	# Cortex-M return addresses often have Thumb bit set in bit0.
	return address & ~0x1


def parse_address(value: str) -> int:
	text = value.strip()
	if not text:
		raise ValueError("Empty address value")

	if text.lower().startswith("0x"):
		return int(text, 16)

	if re.fullmatch(r"[0-9a-fA-F]+", text):
		return int(text, 16)

	return int(text, 10)


def extract_occurrences_from_log(text: str) -> List[AddressOccurrence]:
	occurrences: List[AddressOccurrence] = []
	for line_no, line in enumerate(text.splitlines(), start=1):
		for token in HEX_RE.findall(line):
			occurrences.append(
				AddressOccurrence(
					address=int(token, 16),
					raw=token,
					line_number=line_no,
					line_text=line.strip(),
				)
			)
	return occurrences


def symbolize_address(
	addr2line_tool: str,
	elf: Path,
	address: int,
	map_resolver: Optional[MapResolver],
) -> SymbolizedAddress:
	normalized = normalize_pc_address(address)

	cmd = [
		addr2line_tool,
		"-e",
		str(elf),
		"-f",
		"-C",
		f"0x{normalized:x}",
	]
	result = subprocess.run(cmd, capture_output=True, text=True, check=False)

	if result.returncode != 0:
		function = "<addr2line failed>"
		file_line = result.stderr.strip() or "??:0"
	else:
		lines = [line.strip() for line in result.stdout.splitlines() if line.strip()]
		function = lines[0] if len(lines) >= 1 else "??"
		file_line = lines[1] if len(lines) >= 2 else "??:0"

	hint = map_resolver.find_hint(normalized) if map_resolver else None

	return SymbolizedAddress(
		original=address,
		normalized=normalized,
		function=function,
		file_line=file_line,
		map_hint=hint,
	)


def read_log_input(log_file: Optional[Path], read_stdin: bool) -> str:
	if log_file:
		return log_file.read_text(encoding="utf-8", errors="replace")
	if read_stdin:
		return sys.stdin.read()
	return ""


def render_result(
	occurrence: AddressOccurrence,
	symbolized: SymbolizedAddress,
	include_log_context: bool,
) -> str:
	base = (
		f"{occurrence.raw} -> {symbolized.function} @ {symbolized.file_line}"
	)

	extras: List[str] = []
	if symbolized.thumb_bit_cleared:
		extras.append(f"normalized=0x{symbolized.normalized:08x}")
	if symbolized.map_hint:
		extras.append(f"map={symbolized.map_hint}")
	if include_log_context and occurrence.line_number is not None and occurrence.line_text:
		extras.append(f"log:{occurrence.line_number}: {occurrence.line_text}")

	if extras:
		return f"{base} | " + " | ".join(extras)
	return base


def collect_manual_occurrences(values: Iterable[str]) -> List[AddressOccurrence]:
	occurrences: List[AddressOccurrence] = []
	for value in values:
		tokens = [token for token in re.split(r"[\s,]+", value.strip()) if token]
		for token in tokens:
			addr = parse_address(token)
			raw = token if token.lower().startswith("0x") else f"0x{addr:x}"
			occurrences.append(AddressOccurrence(address=addr, raw=raw))
	return occurrences


def build_parser() -> argparse.ArgumentParser:
	parser = argparse.ArgumentParser(
		description=(
			"Resolve firmware addresses from direct input or logs to file/line "
			"using an ELF and optional MAP hints."
		)
	)
	parser.add_argument(
		"--elf",
		type=Path,
		required=True,
		help="Path to firmware ELF with debug symbols",
	)
	parser.add_argument(
		"--map",
		dest="map_file",
		type=Path,
		help="Optional linker MAP file used for nearest-symbol hints",
	)
	parser.add_argument(
		"--tool",
		type=str,
		help="addr2line binary name/path (default: auto-detect)",
	)
	parser.add_argument(
		"--address",
		action="append",
		default=[],
		help="Address to decode. Can be repeated or comma/space separated.",
	)
	parser.add_argument(
		"--log",
		type=Path,
		help="Path to log file containing addresses (0x...) to decode",
	)
	parser.add_argument(
		"--stdin",
		action="store_true",
		help="Read log text from stdin",
	)
	parser.add_argument(
		"--with-log-context",
		action="store_true",
		help="Include source log line information for decoded log addresses",
	)
	parser.add_argument(
		"--unique",
		action="store_true",
		help="Only decode each unique address once",
	)
	return parser


def main(argv: Sequence[str]) -> int:
	parser = build_parser()
	args = parser.parse_args(argv)

	if not args.address and not args.log and not args.stdin:
		parser.error("Provide at least one input source: --address, --log, or --stdin")

	if args.log and args.stdin:
		parser.error("Use only one log source: --log or --stdin")

	elf_path = args.elf.resolve()
	if not elf_path.exists():
		parser.error(f"ELF file not found: {elf_path}")

	map_resolver: Optional[MapResolver] = None
	if args.map_file:
		map_path = args.map_file.resolve()
		if not map_path.exists():
			parser.error(f"MAP file not found: {map_path}")
		map_resolver = MapResolver.from_file(map_path)

	try:
		addr2line_tool = find_addr2line(args.tool)
	except RuntimeError as exc:
		print(str(exc), file=sys.stderr)
		return 2

	occurrences: List[AddressOccurrence] = []
	occurrences.extend(collect_manual_occurrences(args.address))

	log_text = read_log_input(args.log, args.stdin)
	if log_text:
		occurrences.extend(extract_occurrences_from_log(log_text))

	if not occurrences:
		print("No addresses found in provided input.")
		return 0

	if args.unique:
		seen: set[int] = set()
		unique_occurrences: List[AddressOccurrence] = []
		for occ in occurrences:
			if occ.address in seen:
				continue
			seen.add(occ.address)
			unique_occurrences.append(occ)
		occurrences = unique_occurrences

	symbol_cache: Dict[int, SymbolizedAddress] = {}
	for occ in occurrences:
		if occ.address not in symbol_cache:
			symbol_cache[occ.address] = symbolize_address(
				addr2line_tool=addr2line_tool,
				elf=elf_path,
				address=occ.address,
				map_resolver=map_resolver,
			)

	for occ in occurrences:
		print(
			render_result(
				occurrence=occ,
				symbolized=symbol_cache[occ.address],
				include_log_context=args.with_log_context,
			)
		)

	return 0


if __name__ == "__main__":
	sys.exit(main(sys.argv[1:]))

