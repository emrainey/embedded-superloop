#!/usr/bin/env python3
import json
import subprocess
import sys
from pathlib import Path


def get_workflow_presets():
    """Get all build presets from CMakePresets.json"""
    presets = dict()
    try:
        with open("CMakePresets.json", "r") as f:
            presets.update(json.load(f))
        with open("CMakeUserPresets.json", "r") as f:
            presets.update(json.load(f))
    except FileNotFoundError:
        print("Error: CMakePresets.json not found in current directory")
        sys.exit(1)

    # Get all build preset names
    workflow_Presets = []
    if "workflowPresets" in presets:
        workflow_Presets.extend(preset["name"] for preset in presets["workflowPresets"])

    return workflow_Presets


def workflow_preset(preset_name):
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


def main():
    presets = get_workflow_presets()

    if not presets:
        print("No workflow presets found in CMakePresets.json or CMakeUserPresets.json")
        sys.exit(1)

    print(f"Found {len(presets)} workflow presets: {', '.join(presets)}")
    failed_presets = []

    for preset in presets:
        if not workflow_preset(preset):
            failed_presets.append(preset)

    if failed_presets:
        print(
            f"\n❌ {len(failed_presets)} preset(s) failed to build: {', '.join(failed_presets)}"
        )
        sys.exit(1)
    else:
        print(f"\n✅ Successfully built all {len(presets)} presets")


if __name__ == "__main__":
    main()
