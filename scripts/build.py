#!/usr/bin/env python3
import json
import os
import subprocess
import sys
import typing
from typing import List, Dict, Any
from pathlib import Path


def get_workflow_presets() -> List[Dict[str, Any]]:
    """Get all build presets from CMakePresets.json"""
    presets: Dict[str, Any] = dict()
    assert os.path.exists(
        "CMakePresets.json"
    ), "CMakePresets.json not found in current directory"
    with open("CMakePresets.json", "r") as f:
        presets.update(json.load(f))
    if os.path.exists("CMakeUserPresets.json"):
        with open("CMakeUserPresets.json", "r") as f:
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


def main(args: List[str]) -> int:
    presets = get_workflow_presets()

    if not presets:
        print("No workflow presets found in CMakePresets.json or CMakeUserPresets.json")
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
