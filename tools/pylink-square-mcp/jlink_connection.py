"""Shared J-Link connection helper for the pylink-square MCP tools.

By default, tools connect to a locally running J-Link Remote Server
(https://kb.segger.com/J-Link_Remote_Server) instead of opening the USB
link directly.  Keeping USB in a persistent daemon means each tool call
only opens a TCP socket, which avoids the repeated J-Link DLL load /
USB connect-disconnect churn that made long-lived MCP processes crash.

Device and speed are still passed client-side via ``jlink.connect()``;
the Remote Server only needs to know the listening ``-Port`` and
optionally ``-USB <serial/nickname>`` (see mcp_server.py).
"""

import argparse

import pylink

DEFAULT_REMOTE_HOST = "127.0.0.1"
DEFAULT_REMOTE_PORT = 19020


def add_connection_args(parser: argparse.ArgumentParser) -> None:
    """Add the shared back-end options to a tool's argument parser."""
    parser.add_argument(
        "--remote-host",
        default=DEFAULT_REMOTE_HOST,
        help=f"J-Link Remote Server host (default: {DEFAULT_REMOTE_HOST}). Use 'none' to force a direct USB connection.",
    )
    parser.add_argument(
        "--remote-port",
        type=int,
        default=DEFAULT_REMOTE_PORT,
        help=f"J-Link Remote Server TCP port (default: {DEFAULT_REMOTE_PORT})",
    )
    parser.add_argument(
        "--direct",
        action="store_true",
        help="Force a direct USB connection, ignoring --remote-host/--remote-port.",
    )


def connect(
    device: str,
    speed: int,
    remote_host: str = DEFAULT_REMOTE_HOST,
    remote_port: int = DEFAULT_REMOTE_PORT,
    interface: int = pylink.enums.JLinkInterfaces.SWD,
) -> pylink.JLink:
    """Open a J-Link and connect to ``device``.

    Opens the device through the J-Link Remote Server when ``remote_host``
    is given (the default), falling back to a direct USB connection if the
    Remote Server is not reachable.  Pass ``remote_host="none"`` or use the
    ``--direct`` flag to always use USB directly.
    """
    use_remote = (
        remote_host is not None
        and str(remote_host).lower() not in ("none", "direct", "")
    )
    if use_remote:
        try:
            return _connect_remote(device, speed, remote_host, remote_port, interface)
        except pylink.errors.JLinkException as e:
            import sys

            print(
                f"Warning: could not reach J-Link Remote Server at "
                f"{remote_host}:{remote_port} ({e}). Falling back to direct USB.",
                file=sys.stderr,
            )
    return _connect_direct(device, speed, interface)


def _connect_remote(device: str, speed: int, host: str, port: int, interface: int) -> pylink.JLink:
    jlink = pylink.JLink()
    # ip_addr format: host:port (see pylink.JLink.open)
    jlink.open(ip_addr=f"{host}:{port}")
    jlink.set_tif(interface)
    jlink.connect(device, speed=speed)
    return jlink


def _connect_direct(device: str, speed: int, interface: int) -> pylink.JLink:
    jlink = pylink.JLink()
    jlink.open()
    jlink.set_tif(interface)
    jlink.connect(device, speed=speed)
    return jlink