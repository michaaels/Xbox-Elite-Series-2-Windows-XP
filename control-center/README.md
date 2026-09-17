# Xbox Elite Series 2 Control Center v1.5

Native Win32/GDI utility for the Xbox Elite Series 2 compatibility project.

## Purpose

The Control Center provides:

- real-time visualization of both sticks
- LT / RT values
- D-Pad and buttons
- independent rear paddles P1-P4 through the bridge RAW extension
- rumble tests for left, right and both motors
- STOP control with safety timeout
- diagnostic session logging
- visual rear-paddle remapping
- dynamic per-game profile selection by choosing any game `.exe`
- local XInput bridge deployment per game

The UI was built as native x86 Win32 code so the same application can run from Windows XP SP3 through modern Windows under WoW64.

## Build

The source is kept in `XboxElite2ControlCenter.cpp` plus ordered fragments in `parts/`. This split is only for repository readability; the wrapper includes the fragments in the original source order.

On a Linux system with clang and lld installed:

```sh
sh BUILD_LINUX_CLANG.sh
```

The produced binary is a PE32 i386 Windows GUI executable with subsystem version 5.01.

## Runtime files

Keep these files beside the executable:

```text
XboxElite2ControlCenter.exe
XInputBridgeXP.ini
xinput1_3.dll
xinput9_1_0.dll
```

The Control Center prefers the local XInput bridge and falls back to WinMM when required.

## Validated package hashes

Reference package used during validation:

```text
XboxElite2ControlCenter.exe
SHA-256: eea2c2660f723083990890dedcfbe6503cdd03a1e252a53e9ba9cf4872197f0c

xinput1_3.dll / xinput9_1_0.dll
SHA-256: 1e8800389f72dd54cb784f3fbab6704d046e1e32f1cac94de6e9325184bcbccb

XInputBridgeXP.ini
SHA-256: 44291dbb7061188a09448a1556c8e5ca00e76570f345645ac465ddaf26e33d3e
```

The compiled EXE/DLL package should be distributed as a GitHub Release asset. The source and configuration are kept in this repository.

## Game profiles

The Games screen is not hard-coded to GTA III / Vice City. Choose any `.exe`, then use the Control Center to install the local XInput bridge and apply a paddle profile to that game directory.

Do not copy the bridge DLLs to Windows `System32`; keep them local to the game that needs them.
