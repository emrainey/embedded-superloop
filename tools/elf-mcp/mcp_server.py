"""elf-mcp: embeddded flash/RAM analysis MCP server (JSON-RPC 2.0 over stdio).

Exposes arm binutils + linker-script/.map analysis as structured-JSON tools so
an AI agent can inspect firmware size, regions, per-object bloat, heap usage and
code addresses.  Mirrors the stdio protocol of tools/pylink-square-mcp.
"""

from __future__ import annotations

import json
import os
import sys
import traceback

try:
    from tools import TOOLS
except ImportError:
    sys.path.append(os.path.dirname(os.path.abspath(__file__)))
    from tools import TOOLS


def log(msg: str) -> None:
    sys.stderr.write(f"[elf-mcp] {msg}\n")
    sys.stderr.flush()


def _reply(response: dict) -> None:
    sys.stdout.write(json.dumps(response) + "\n")
    sys.stdout.flush()


def main() -> None:
    log("elf-mcp server starting...")
    log(f"Exposing {len(TOOLS)} tools.")

    for line in sys.stdin:
        if not line.strip():
            continue
        try:
            request = json.loads(line)
        except Exception as exc:  # noqa: BLE001 - keep the loop alive
            log(f"Failed to parse JSON: {line.strip()}. Error: {exc}")
            continue

        method = request.get("method")
        req_id = request.get("id")

        if method == "initialize":
            _reply({
                "jsonrpc": "2.0",
                "id": req_id,
                "result": {
                    "protocolVersion": "2024-11-05",
                    "capabilities": {"tools": {}},
                    "serverInfo": {"name": "elf-mcp", "version": "0.1.0"},
                },
            })
            log("Initialized protocol session.")

        elif method == "notifications/initialized":
            log("Received notifications/initialized from client.")

        elif method == "tools/list":
            tools_list = [
                {"name": t["name"], "description": t["description"],
                 "inputSchema": t["inputSchema"]}
                for t in TOOLS
            ]
            _reply({
                "jsonrpc": "2.0",
                "id": req_id,
                "result": {"tools": tools_list},
            })
            log(f"Listed {len(tools_list)} tools.")

        elif method == "tools/call":
            params = request.get("params", {})
            name = params.get("name")
            arguments = params.get("arguments", {})
            log(f"Calling tool '{name}'...")

            tool = next((t for t in TOOLS if t["name"] == name), None)
            if not tool:
                _reply({
                    "jsonrpc": "2.0",
                    "id": req_id,
                    "error": {"code": -32601, "message": f"Method not found: {name}"},
                })
            else:
                try:
                    exit_code, output = tool["handler"](arguments)
                    response = {
                        "jsonrpc": "2.0",
                        "id": req_id,
                        "result": {
                            "content": [{"type": "text", "text": output}],
                            "isError": exit_code != 0,
                        },
                    }
                except Exception as exc:  # noqa: BLE001
                    log(f"Error handling tool '{name}': {exc}\n{traceback.format_exc()}")
                    response = {
                        "jsonrpc": "2.0",
                        "id": req_id,
                        "result": {
                            "content": [{
                                "type": "text",
                                "text": f"Internal error executing tool '{name}': "
                                        f"{exc}\n{traceback.format_exc()}",
                            }],
                            "isError": True,
                        },
                    }
                _reply(response)
                log(f"Tool '{name}' finished execution.")

        else:
            if req_id is not None:
                _reply({
                    "jsonrpc": "2.0",
                    "id": req_id,
                    "error": {
                        "code": -32601,
                        "message": f"Unsupported or unknown method: {method}",
                    },
                })


if __name__ == "__main__":
    main()