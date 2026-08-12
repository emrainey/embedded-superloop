"""Host-run unit tests for the SWO (Serial Wire Output) support in tools/jalo.py.

These tests mock pylink-square and run without any J-Link hardware. Run with:

    .venv/bin/python -m pytest tools/test_jalo_swo.py -v
"""

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from unittest import mock

import pytest

import jalo
from jalo import JLinkController, decode_trace_chunk

TEST_SIZE = (200, 50)


@pytest.fixture
def connected_controller():
    controller = JLinkController()
    controller.connected = True
    controller.link = mock.MagicMock()
    return controller


@pytest.fixture
def disconnected_controller():
    return JLinkController()


# ---------------------------------------------------------------------------
# decode_trace_chunk
# ---------------------------------------------------------------------------


class TestDecodeTraceChunk:
    def test_complete_lines_are_emitted(self):
        pending, lines = decode_trace_chunk(b"hello\nworld\n", "")
        assert pending == ""
        assert lines == ["hello", "world"]

    def test_partial_line_is_buffered(self):
        pending, lines = decode_trace_chunk(b"hel", "")
        assert pending == "hel"
        assert lines == []

    def test_partial_line_completes_across_chunks(self):
        pending, lines = decode_trace_chunk(b"wor", "hel")
        assert pending == "helwor"
        assert lines == []
        pending, lines = decode_trace_chunk(b"\n", pending)
        assert pending == ""
        assert lines == ["helwor"]

    def test_crlf_is_normalized(self):
        pending, lines = decode_trace_chunk(b"a\r\nb\r\n", "")
        assert pending == ""
        assert lines == ["a", "b"]

    def test_mixed_newlines_are_split(self):
        pending, lines = decode_trace_chunk(b"a\r\nb\nc\n", "")
        assert pending == ""
        assert lines == ["a", "b", "c"]

    def test_empty_payload_keeps_pending(self):
        pending, lines = decode_trace_chunk(b"", "abc")
        assert pending == "abc"
        assert lines == []

    def test_binary_garbage_is_replaced_not_crashing(self):
        pending, lines = decode_trace_chunk(b"\xff\xfe\n", "")
        assert pending == ""
        assert lines == ["\ufffd\ufffd"]


# ---------------------------------------------------------------------------
# JLinkController.swo_* wrappers
# ---------------------------------------------------------------------------


class TestSwoEnable:
    def test_connected(self, connected_controller):
        assert connected_controller.swo_enable(480_000_000, 2_000_000, 0x3) is True
        connected_controller.link.swo_enable.assert_called_once_with(
            480_000_000, 2_000_000, 0x3
        )
        assert connected_controller.last_error == ""

    def test_disconnected(self, disconnected_controller):
        assert disconnected_controller.swo_enable(1, 2, 3) is False
        assert disconnected_controller.last_error == "probe not connected"

    def test_raises_sets_last_error(self, connected_controller):
        connected_controller.link.swo_enable.side_effect = RuntimeError("boom")
        assert connected_controller.swo_enable(1, 2, 3) is False
        assert connected_controller.last_error == "boom"


class TestSwoStart:
    def test_connected(self, connected_controller):
        assert connected_controller.swo_start(2_000_000) is True
        connected_controller.link.swo_start.assert_called_once_with(2_000_000)

    def test_disconnected(self, disconnected_controller):
        assert disconnected_controller.swo_start(2_000_000) is False
        assert disconnected_controller.last_error == "probe not connected"

    def test_raises_sets_last_error(self, connected_controller):
        connected_controller.link.swo_start.side_effect = RuntimeError("boom")
        assert connected_controller.swo_start(2_000_000) is False
        assert connected_controller.last_error == "boom"


class TestSwoStop:
    def test_connected(self, connected_controller):
        assert connected_controller.swo_stop() is True
        connected_controller.link.swo_stop.assert_called_once_with()

    def test_disconnected(self, disconnected_controller):
        assert disconnected_controller.swo_stop() is False
        assert disconnected_controller.last_error == "probe not connected"

    def test_raises_sets_last_error(self, connected_controller):
        connected_controller.link.swo_stop.side_effect = RuntimeError("boom")
        assert connected_controller.swo_stop() is False
        assert connected_controller.last_error == "boom"


class TestSwoFlush:
    def test_connected(self, connected_controller):
        assert connected_controller.swo_flush() is True
        connected_controller.link.swo_flush.assert_called_once_with()

    def test_disconnected(self, disconnected_controller):
        assert disconnected_controller.swo_flush() is False
        assert disconnected_controller.last_error == "probe not connected"


class TestSwoEnabled:
    def test_connected(self, connected_controller):
        connected_controller.link.swo_enabled.return_value = True
        assert connected_controller.swo_enabled() is True

    def test_disconnected(self, disconnected_controller):
        assert disconnected_controller.swo_enabled() is False

    def test_raises_returns_false(self, connected_controller):
        connected_controller.link.swo_enabled.side_effect = RuntimeError("boom")
        assert connected_controller.swo_enabled() is False


class TestSwoNumBytes:
    def test_connected(self, connected_controller):
        connected_controller.link.swo_num_bytes.return_value = 42
        assert connected_controller.swo_num_bytes() == 42

    def test_disconnected(self, disconnected_controller):
        assert disconnected_controller.swo_num_bytes() is None

    def test_raises_returns_none(self, connected_controller):
        connected_controller.link.swo_num_bytes.side_effect = RuntimeError("boom")
        assert connected_controller.swo_num_bytes() is None


class TestSwoRead:
    def test_connected_passes_through_remove(self, connected_controller):
        connected_controller.link.swo_read.return_value = [1, 2, 3]
        assert connected_controller.swo_read(0, 16, remove=True) == [1, 2, 3]
        connected_controller.link.swo_read.assert_called_once_with(0, 16, remove=True)

    def test_disconnected(self, disconnected_controller):
        assert disconnected_controller.swo_read(0, 16) is None

    def test_invalid_count(self, connected_controller):
        assert connected_controller.swo_read(0, 0) is None
        assert connected_controller.swo_read(0, -1) is None

    def test_raises_returns_none(self, connected_controller):
        connected_controller.link.swo_read.side_effect = RuntimeError("boom")
        assert connected_controller.swo_read(0, 16) is None


class TestSwoReadStimulus:
    def test_connected(self, connected_controller):
        connected_controller.link.swo_read_stimulus.return_value = [ord("h"), ord("i")]
        assert connected_controller.swo_read_stimulus(0, 64) == [ord("h"), ord("i")]
        connected_controller.link.swo_read_stimulus.assert_called_once_with(0, 64)

    def test_disconnected(self, disconnected_controller):
        assert disconnected_controller.swo_read_stimulus(0, 64) is None

    def test_invalid_count(self, connected_controller):
        assert connected_controller.swo_read_stimulus(0, 0) is None

    def test_raises_returns_none(self, connected_controller):
        connected_controller.link.swo_read_stimulus.side_effect = RuntimeError("boom")
        assert connected_controller.swo_read_stimulus(0, 64) is None


# ---------------------------------------------------------------------------
# parse_args SWO validation
# ---------------------------------------------------------------------------


class TestArgumentParsing:
    def test_swo_defaults(self):
        args = jalo.parse_args([])
        assert args.swo_cpu_speed == 480_000_000
        assert args.swo_speed == 2_000_000
        assert args.swo_port_mask == 0x1
        assert args.swo_port == 0
        assert args.swo_auto_start is False

    def test_swo_custom_values(self):
        args = jalo.parse_args(
            [
                "--swo-cpu-speed",
                "400000000",
                "--swo-speed",
                "1000000",
                "--swo-port-mask",
                "0x7",
                "--swo-port",
                "3",
                "--swo-auto-start",
            ]
        )
        assert args.swo_cpu_speed == 400_000_000
        assert args.swo_speed == 1_000_000
        assert args.swo_port_mask == 0x7
        assert args.swo_port == 3
        assert args.swo_auto_start is True

    def test_swo_port_mask_decimal(self):
        args = jalo.parse_args(["--swo-port-mask", "3"])
        assert args.swo_port_mask == 3

    def test_swo_continuous_alias(self):
        args = jalo.parse_args(["--swo-continuous"])
        assert args.swo_auto_start is True

    @pytest.mark.parametrize(
        "argv",
        [
            ["--swo-cpu-speed", "0"],
            ["--swo-cpu-speed", "-1"],
            ["--swo-speed", "0"],
            ["--swo-speed", "-5"],
            ["--swo-port-mask", "0"],
            ["--swo-port-mask", "-2"],
            ["--swo-port", "-1"],
            ["--swo-port", "32"],
            ["--swo-port", "100"],
        ],
    )
    def test_swo_invalid_values_rejected(self, argv):
        with pytest.raises(SystemExit) as exc_info:
            jalo.parse_args(argv)
        assert exc_info.value.code == 2


# ---------------------------------------------------------------------------
# TUI app behaviour (headless textual harness, pylink mocked away)
# ---------------------------------------------------------------------------


def _log_text(app):
    log = app.query_one("#swo-log")
    return "".join(strip.text for strip in log.lines)


def _make_connected_app():
    app = jalo.SVDDebuggerApp(swo_cpu_speed=400_000_000, swo_speed=1_000_000, swo_port_mask=0x3)
    app.jlink.connected = True
    app.jlink.link = mock.MagicMock()
    return app


@pytest.mark.anyio
async def test_app_mounts_swo_controls_with_configured_values():
    app = _make_connected_app()
    async with app.run_test(size=TEST_SIZE):
        assert app.query_one("#input-swo-cpu").value == "400000000"
        assert app.query_one("#input-swo-speed").value == "1000000"
        assert app.query_one("#input-swo-mask").value == "0x3"
        assert app.query_one("#input-swo-port").value == "0"
        assert app.query_one("#btn-swo-enable") is not None
        assert app.query_one("#btn-swo-read").disabled is False


@pytest.mark.anyio
async def test_enable_swo_button_configures_target_and_logs():
    app = _make_connected_app()
    async with app.run_test(size=TEST_SIZE) as pilot:
        app.query_one("#main-tabs").active = "tab-swo-view"
        await pilot.pause()
        await pilot.click("#btn-swo-enable")
        app.jlink.link.swo_enable.assert_called_once_with(400_000_000, 1_000_000, 0x3)
        assert "SWO enabled" in _log_text(app)


@pytest.mark.anyio
async def test_start_button_starts_collection():
    app = _make_connected_app()
    async with app.run_test(size=TEST_SIZE) as pilot:
        app.query_one("#main-tabs").active = "tab-swo-view"
        await pilot.pause()
        await pilot.click("#btn-swo-start")
        app.jlink.link.swo_start.assert_called_once_with(1_000_000)
        assert "collection started" in _log_text(app)


@pytest.mark.anyio
async def test_start_button_falls_back_to_enable_when_start_fails():
    app = _make_connected_app()
    app.jlink.link.swo_start.side_effect = RuntimeError("not enabled")
    async with app.run_test(size=TEST_SIZE) as pilot:
        app.query_one("#main-tabs").active = "tab-swo-view"
        await pilot.pause()
        await pilot.click("#btn-swo-start")
        app.jlink.link.swo_enable.assert_called_once_with(400_000_000, 1_000_000, 0x3)


@pytest.mark.anyio
async def test_read_button_decodes_stimulus_port_lines():
    app = _make_connected_app()
    app.jlink.link.swo_read_stimulus.return_value = list(b"hello from SWO\r\nworld\n")
    async with app.run_test(size=TEST_SIZE) as pilot:
        app.query_one("#main-tabs").active = "tab-swo-view"
        await pilot.pause()
        await pilot.click("#btn-swo-read")
        text = _log_text(app)
        assert "hello from SWO" in text
        assert "world" in text


@pytest.mark.anyio
async def test_read_button_buffers_partial_lines():
    app = _make_connected_app()
    app.jlink.link.swo_read_stimulus.side_effect = [list(b"partial"), list(b" line\n")]
    async with app.run_test(size=TEST_SIZE) as pilot:
        app.query_one("#main-tabs").active = "tab-swo-view"
        app.query_one("#btn-swo-read").active_effect_duration = 0
        await pilot.pause()
        await pilot.click("#btn-swo-read")
        assert "partial" not in _log_text(app)
        await pilot.pause()
        await pilot.click("#btn-swo-read")
        assert "partial line" in _log_text(app)


@pytest.mark.anyio
async def test_stop_button_stops_capture():
    app = _make_connected_app()
    async with app.run_test(size=TEST_SIZE) as pilot:
        app.query_one("#main-tabs").active = "tab-swo-view"
        await pilot.pause()
        await pilot.click("#btn-swo-stop")
        app.jlink.link.swo_stop.assert_called_once_with()
        assert app.query_one("#btn-swo-read").disabled is False


@pytest.mark.anyio
async def test_enable_ignored_when_disconnected():
    app = jalo.SVDDebuggerApp()
    async with app.run_test(size=TEST_SIZE) as pilot:
        app.query_one("#main-tabs").active = "tab-swo-view"
        await pilot.pause()
        await pilot.click("#btn-swo-enable")
        assert "not connected" in _log_text(app)


@pytest.mark.anyio
async def test_continuous_switch_disables_read_button():
    app = _make_connected_app()
    async with app.run_test(size=TEST_SIZE) as pilot:
        app.query_one("#main-tabs").active = "tab-swo-view"
        await pilot.pause()
        await pilot.click("#switch-swo-continuous")
        assert app.query_one("#btn-swo-read").disabled is True
        assert app.auto_swo_capture is True
