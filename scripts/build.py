#!/usr/bin/env python3
import os
import sys
import json
import argparse
import subprocess
from typing import List, Dict, Any
from pathlib import Path


def get_workflow_presets(
    preset_file: str = "CMakePresets.json",
    user_preset_file: str = "CMakeUserPresets.json",
) -> List[Dict[str, Any]]:
    """Get all build presets from Presets files"""
    presets: Dict[str, Any] = dict()
    assert os.path.exists(preset_file), f"{preset_file} not found in current directory"
    with open(preset_file, "r") as f:
        presets.update(json.load(f))
    if os.path.exists(user_preset_file):
        with open(user_preset_file, "r") as f:
            presets.update(json.load(f))

    # Get all build preset names
    workflow_Presets: List[Dict[str, Any]] = list()
    if "workflowPresets" in presets:
        workflow_Presets.extend(preset["name"] for preset in presets["workflowPresets"])

    return workflow_Presets


def workflow_preset(preset_name: str) -> bool:
    """Build a specific preset"""
    print(f"\nBuilding preset: {preset_name}")

    result = subprocess.run(
        ["cmake", "--workflow", "--preset", preset_name], capture_output=True, text=True
    )

    if result.returncode == 0:
        print(f"✓ Successfully built {preset_name}")
        return True
    else:
        print(f"✗ Failed to build {preset_name}")
        print("Error output:")
        print(result.stderr)
        return False


def main(argv: List[str]) -> int:
    parser = argparse.ArgumentParser(description="Build all CMake workflow presets")
    parser.add_argument(
        "--preset-file",
        type=str,
        action="store",
        help="Preset file to use (default: %(default)s)",
        default="CMakePresets.json",
    )
    parser.add_argument(
        "--user-preset-file",
        type=str,
        action="store",
        help="User preset file to use (default: %(default)s)",
        default="CMakeUserPresets.json",
    )
    args = parser.parse_args(argv)

    presets = get_workflow_presets(
        preset_file=args.preset_file,
        user_preset_file=args.user_preset_file,
    )

    if not presets:
        print(
            f"No workflow presets found in {args.preset_file} or {args.user_preset_file}"
        )
        sys.exit(1)

    print(f"Found {len(presets)} workflow presets: {', '.join(presets)}")
    failed_presets: List[Dict[str, Any]] = list()

    for preset in presets:
        if not workflow_preset(preset):
            failed_presets.append(preset)

    if failed_presets:
        print(
            f"\n❌ {len(failed_presets)} preset(s) failed to build: {', '.join(failed_presets)}"
        )
        return -1
    else:
        print(f"\n✅ Successfully built all {len(presets)} presets")
        return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

# I just kept hitting tab....
# vim: set ts=4 sw=4 et:
# vim: set filetype=python:
# vim: set expandtab:
# vim: set autoindent:
# vim: set smartindent:
# vim: set fileencoding=utf-8:
# vim: set syntax=python:
# vim: set foldmethod=marker:
# vim: set foldlevel=99:
# vim: set foldenable:
# vim: set colorcolumn=80:
# vim: set nowrap:
# vim: set showcmd:
# vim: set nospell:
