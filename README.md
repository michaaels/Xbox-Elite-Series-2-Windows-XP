# Xbox Elite Series 2 on Windows XP SP3 (x86)

Unofficial reverse-engineering project that adds **wired USB support for the Xbox Elite Wireless Controller Series 2 (VID `045E`, PID `0B00`) on Windows XP SP3 32-bit**.

The project started from Microsoft's 2014 x86 Xbox One USB driver (`xb1usb.sys` 6.2.11059.0) and experimentally retargeted it from **KMDF 1.11 to KMDF 1.9**, corrected the KMDF ABI differences that blocked XP, added the modern GIP initialization needed by an Elite Series 2, extended the HID report for the four rear paddles, and added a user-mode XInput bridge with real rumble.

> **Status:** experimental / unofficial. Not affiliated with or endorsed by Microsoft. The kernel driver is unsigned. Use only on test/retro systems with a recovery plan.

## Validated hardware / OS

- Windows XP SP3 **x86 / 32-bit**
- Xbox Elite Wireless Controller Series 2 over **USB cable**
- USB hardware ID: `USB\\VID_045E&PID_0B00`
- Tested `bcdDevice / REV`: `0x0517`
- KMDF 1.9

Wireless, Bluetooth, Windows XP x64, other Xbox PIDs and other firmware revisions are **not claimed as supported**.

## What works in the validated build

- left and right sticks
- D-Pad / POV
- A/B/X/Y, LB/RB, View/Back, Menu/Start, L3/R3
- four rear paddles as independent HID buttons 11-14
- LT / RT exposed to games through the XInput bridge
- `XInputGetState()`
- `XInputSetState()` with left/right/both motor rumble
- per-game paddle remapping
- Control Center / diagnostic UI compatible from XP through modern Windows
- GTA III and GTA Vice City confirmed with GInput, including vibration

A recorded validation session produced 0 XInput errors, 0 RAW errors, buttons `10/10`, paddles `4/4`, POV `8/8`, full LT/RT values, and essentially full stick range. See [`validation/`](validation/).

## Downloads

Compiled end-user binaries are intended to live in the **GitHub v1.0 Release**, not inside the source tree.

The v1.0 Release should contain these two primary assets:

```text
Xbox_Elite_Series2_XP_Driver_v1.0.zip
XboxElite2ControlCenter_v1.5.exe
```

Reference hashes for the validated assets:

```text
Xbox_Elite_Series2_XP_Driver_v1.0.zip
SHA-256: 864c3b7d7171f1a1da7976feb58a8046e36bf1670f1be09011cebe61a5054a08

XboxElite2ControlCenter_v1.5.exe
SHA-256: eea2c2660f723083990890dedcfbe6503cdd03a1e252a53e9ba9cf4872197f0c
```

## Control Center v1.5 source

The [`control-center/`](control-center/) directory is source-only. The complete Control Center source is under:

- [`control-center/src/XboxElite2ControlCenter.cpp`](control-center/src/XboxElite2ControlCenter.cpp)
- [`control-center/src/parts/`](control-center/src/parts/) — ordered source fragments included by the wrapper
- [`control-center/src/imports_gui.s`](control-center/src/imports_gui.s)
- [`control-center/src/BUILD_LINUX_CLANG.sh`](control-center/src/BUILD_LINUX_CLANG.sh)
- [`control-center/src/XInputBridgeXP.ini`](control-center/src/XInputBridgeXP.ini)

The Games screen lets you choose any game `.exe`, install the local bridge into that game folder, and apply the current rear-paddle mapping. The game list is not hard-coded to GTA.

## Why the Microsoft driver did not start on XP

The 2014 package is a KMDF 1.11 driver and its MSI targets Windows 7+. XP supports KMDF 1.9. Simply changing the INF or the WDF bind version was not enough: two KMDF structures changed size between the versions.

The key failures found during debugging were:

1. `WdfIoQueueCreate` returned `0xC0000004` (`STATUS_INFO_LENGTH_MISMATCH`).
2. `WDF_IO_QUEUE_CONFIG.Size` was `0x38` for the 1.11 build but XP/KMDF 1.9 expects `0x34`.
3. `WDF_PNPPOWER_EVENT_CALLBACKS.Size` was `0x48` but KMDF 1.9 expects `0x44`.

After fixing those ABI differences, the parent device could start. Additional GIP initialization and HID work was required to get real controller input and the Elite paddles.

Read the full timeline in [`docs/TEST_HISTORY.md`](docs/TEST_HISTORY.md) and the ABI notes in [`docs/KMDF_ABI.md`](docs/KMDF_ABI.md).

## Reproducing the kernel patch

For copyright/licensing reasons this public source tree **does not need to redistribute Microsoft's original `xb1usb.sys`**. The exact tested binary can be reproduced from a legally obtained copy of the 2014 x86 driver.

Expected original file:

```text
xb1usb.sys
size    : 29408 bytes
SHA-256 : bd4cb415a34022ac01e5b8f4915735be421958e8534258c86f9805652736c73f
```

Expected patched output:

```text
xboxelite2xp.sys
size    : 29408 bytes
SHA-256 : 1fe18559ae33e46694669556177cdacf1b39f104fa9760d5563696dffd4fa649
```

Run:

```bash
python3 patcher/patch_xb1usb.py /path/to/xb1usb.sys -o driver/xboxelite2xp.sys
```

The patcher validates the input SHA, applies the exact byte ranges from [`patch_manifest.json`](patcher/patch_manifest.json), and validates the final SHA.

## Repository map

```text
patcher/         exact reproducible binary patch
driver/          clean XP INF (SYS intentionally generated locally)
control-center/  Control Center source only
installer/       XP installer script
src/             setup helper / other project source
docs/            reverse-engineering and protocol documentation
validation/      sanitized successful test summary
third-party/     integration notes (GInput / Chimera are not bundled)
```

## Installation on XP

See [`docs/INSTALLATION_XP.md`](docs/INSTALLATION_XP.md). The important constraints are:

- XP SP3 x86 only
- KMDF 1.9 / `WdfCoInstaller01009.dll`
- disconnect/reboot before replacing an older experimental service if XP reports Code 38
- do not install this XP kernel driver on Windows 10/11

## Game integration

The native XP driver exposes HID/DirectInput. A local `xinput1_3.dll` / `xinput9_1_0.dll` bridge is provided for games or wrappers that expect XInput. **Keep the bridge local to the game folder; do not copy it to System32.**

See [`docs/XINPUT_BRIDGE.md`](docs/XINPUT_BRIDGE.md) and [`docs/GAME_COMPATIBILITY.md`](docs/GAME_COMPATIBILITY.md).

## Important legal note

Microsoft binaries and third-party mods are not relicensed by this project. See [`docs/LEGAL.md`](docs/LEGAL.md).
