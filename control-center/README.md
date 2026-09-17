# Xbox Elite Series 2 Control Center v1.5

Native Win32/GDI utility for the Xbox Elite Series 2 Windows XP compatibility project.

This directory is intentionally **source-only**. The compiled `XboxElite2ControlCenter.exe` belongs in the GitHub **v1.0 Release**, together with the final driver package.

## Source layout

```text
control-center/
├── README.md
└── src/
    ├── XboxElite2ControlCenter.cpp
    ├── BUILD_LINUX_CLANG.sh
    ├── imports_gui.s
    ├── XInputBridgeXP.ini
    └── parts/
        ├── XboxElite2ControlCenter_part01.inc
        ├── XboxElite2ControlCenter_part02.inc
        ├── XboxElite2ControlCenter_part03.inc
        ├── XboxElite2ControlCenter_part04.inc
        ├── XboxElite2ControlCenter_part05.inc
        ├── XboxElite2ControlCenter_part06.inc
        └── XboxElite2ControlCenter_part07.inc
```

`XboxElite2ControlCenter.cpp` is a thin wrapper that includes the seven fragments in their original order. The split exists only to keep the GitHub source readable; together they are the complete v1.5 Control Center source.

## Features

- real-time left/right stick visualization
- LT / RT values
- D-Pad and buttons
- independent rear paddles P1-P4 through the bridge RAW extension
- left/right/both motor rumble tests
- STOP control with a safety timeout
- diagnostic session logging
- visual P1-P4 remapping
- dynamic game `.exe` selection
- per-game local XInput bridge deployment

The Games screen is not hard-coded to GTA III or Vice City. Any game executable can be selected.

## Build

From `control-center/src/` on a Linux system with clang and lld:

```sh
sh BUILD_LINUX_CLANG.sh
```

Expected output:

```text
XboxElite2ControlCenter.exe
```

The build targets PE32 i386 / Windows GUI subsystem 5.01 for Windows XP compatibility.

## Runtime files

The Release package keeps these files beside the executable:

```text
XboxElite2ControlCenter.exe
XInputBridgeXP.ini
xinput1_3.dll
xinput9_1_0.dll
```

Do not copy the bridge DLLs globally to `System32`; keep them local to the Control Center or the game that needs them.

## Validated hashes

```text
XboxElite2ControlCenter.exe
SHA-256: eea2c2660f723083990890dedcfbe6503cdd03a1e252a53e9ba9cf4872197f0c

xinput1_3.dll / xinput9_1_0.dll
SHA-256: 1e8800389f72dd54cb784f3fbab6704d046e1e32f1cac94de6e9325184bcbccb

XInputBridgeXP.ini
SHA-256: 44291dbb7061188a09448a1556c8e5ca00e76570f345645ac465ddaf26e33d3e
```
