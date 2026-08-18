# Troubleshooting

## Code 38 / previous driver image still loaded

During development XP sometimes retained an older SYS image after switching service names/builds. If Device Manager reports Code 38 (`CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD`):

1. disconnect the controller;
2. reboot Windows XP;
3. keep the controller disconnected until the new driver package is ready;
4. install/update the INF;
5. reconnect the controller.

## Code 37 / failed DriverEntry

An INF-only PID addition is not sufficient. The original 2014 driver is KMDF 1.11 and fails on XP/KMDF 1.9 without the ABI corrections documented in `KMDF_ABI.md`.

## `WdfIoQueueCreate` = `0xC0000004`

This was the proven `WDF_IO_QUEUE_CONFIG.Size` mismatch. The validated patch changes all three `0x38` size immediates to `0x34`.

## Parent starts but no useful input

For Elite Series 2, the old driver also needs the modern GIP initialization documented in `GIP_NOTES.md`.

## Standard buttons work but paddles do not

The final kernel exposes paddles as HID buttons 11-14. Verify RAW/HID first. Classic XInput does not have four dedicated paddle fields; the user-mode bridge maps paddles to ordinary XInput buttons while retaining independent RAW state.

## A game shows Button 1 / Axis instead of A/B/X/Y

That is usually a DirectInput-era game UI issue. The driver cannot force every game to display Xbox glyph/name labels. Use a game-specific compatibility layer where appropriate (for example GInput for GTA III/VC or controller-label support in other mods).

## Rumble keeps running

Use the Control Center STOP command. Games should send zero motor state when vibration ends; the bridge also supports explicit stop via `XInputSetState()`.
