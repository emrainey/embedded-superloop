#!/usr/bin/env python3
import argparse
import json
import os
import re
import sys
from pathlib import Path

def main():
    parser = argparse.ArgumentParser(
        description="Generate VS Code launch.json from configured CMake build targets."
    )
    parser.add_argument(
        "--build-dir",
        type=str,
        required=True,
        help="Path to the active CMake build directory.",
    )
    args = parser.parse_args()

    workspace_root = Path(__file__).resolve().parent.parent
    build_dir = Path(args.build_dir).resolve()

    if not build_dir.exists():
        print(f"Error: Build directory {build_dir} does not exist.", file=sys.stderr)
        sys.exit(1)

    # 1. Read targets from debug_targets.json inside build_dir
    json_path = build_dir / "debug_targets.json"
    if not json_path.exists():
        print(f"No debug_targets.json found in {build_dir}. Skipping generation.", file=sys.stderr)
        sys.exit(0)

    try:
        targets = json.loads(json_path.read_text(encoding="utf-8"))
    except Exception as e:
        print(f"Error reading/parsing {json_path}: {e}", file=sys.stderr)
        sys.exit(1)

    new_configs = []

    for target in targets:
        name = target.get("name")
        device = target.get("device")
        exec_path_str = target.get("executable")

        if not name or not device or not exec_path_str:
            continue

        exec_path = Path(exec_path_str)

        # Derive SVD file path
        rel_svd = ""
        if device.startswith("STM32"):
            # The naming convention for SVDs is STM32 + first 4 chars of model + .svd
            # e.g., STM32F407VE -> STM32F407.svd
            svd_name = f"{device[:9]}.svd"
            svd_path = workspace_root / "modules" / "stm32" / "scripts" / svd_name
            if svd_path.exists():
                rel_svd = "${workspaceFolder}/" + str(svd_path.resolve().relative_to(workspace_root.resolve()))

        # Convert absolute paths to workspace-relative using VS Code variable
        try:
            rel_exec = "${workspaceFolder}/" + str(exec_path.resolve().relative_to(workspace_root.resolve()))
        except ValueError:
            rel_exec = str(exec_path)

        # Create launch configuration
        config = {
            "name": f"Cortex-Debug (JLink): {name}",
            "cwd": "${workspaceFolder}",
            "executable": rel_exec,
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "jlink",
            "interface": "swd",
            "runToEntryPoint": "reset_entry",
            "device": device,
            "internalConsoleOptions": "openOnSessionStart",
            "showDevDebugOutput": "both",
            "preLaunchCommands": [
                "set mem inaccessible-by-default off"
            ],
            "preResetCommands": [
                "monitor reset 0"
            ],
            "rttConfig": {
                "enabled": True,
                "address": "auto",
                "decoders": [
                    {
                        "port": 0,
                        "type": "console",
                        "label": "RTT Channel 0 (Log)"
                    }
                ]
            }
        }

        if rel_svd:
            config["svdFile"] = rel_svd

        new_configs.append(config)

    print(f"Generated {len(new_configs)} debug configurations for build directory {build_dir.name}.")

    # 2. Read existing launch.json, filter/merge, and write back
    launch_json_path = workspace_root / ".vscode" / "launch.json"
    existing_launch = {"version": "0.2.0", "configurations": []}

    if launch_json_path.exists():
        try:
            raw_content = launch_json_path.read_text(encoding="utf-8")
            # Strip comments and trailing commas to parse with standard json
            clean_content = re.sub(r'//.*', '', raw_content)
            clean_content = re.sub(r',\s*([\]}])', r'\1', clean_content)
            existing_launch = json.loads(clean_content)
        except Exception as e:
            print(f"Warning: Could not parse existing launch.json ({e}). Overwriting.", file=sys.stderr)

    # Filter out existing cortex-debug configurations to avoid duplication/stale entries
    non_cortex_configs = [
        c for c in existing_launch.get("configurations", [])
        if c.get("type") != "cortex-debug"
    ]

    # Ensure Local Debug via LLDB is present
    has_lldb = any(c.get("name") == "Local Debug via LLDB" for c in non_cortex_configs)
    if not has_lldb:
        non_cortex_configs.insert(0, {
            "name": "Local Debug via LLDB",
            "cwd": "${workspaceRoot}",
            "type": "lldb",
            "request": "launch",
            "args": [],
            "linux": {},
            "osx": {}
        })

    # Merge
    merged_configs = non_cortex_configs + new_configs
    existing_launch["configurations"] = merged_configs

    # Ensure .vscode dir exists
    launch_json_path.parent.mkdir(parents=True, exist_ok=True)

    # Write back
    try:
        with open(launch_json_path, "w", encoding="utf-8") as f:
            f.write("// Auto-generated debug configurations. Do not edit manually.\n")
            f.write("// Run CMake configure to update.\n")
            json.dump(existing_launch, f, indent=4)
            f.write("\n")
        print(f"Successfully updated {launch_json_path}")
    except Exception as e:
        print(f"Error: Could not write to {launch_json_path} ({e})", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
