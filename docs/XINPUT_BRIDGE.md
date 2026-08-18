# XInput bridge

The XP kernel driver exposes HID/DirectInput. A separate user-mode bridge provides XInput compatibility for games that expect `xinput1_3.dll` or `xinput9_1_0.dll`.

## Input mapping

- HID button 1 → A
- 2 → B
- 3 → X
- 4 → Y
- 5 → LB
- 6 → RB
- 7 → Back/View
- 8 → Start/Menu
- 9 → L3
- 10 → R3
- POV → XInput D-Pad
- left stick → LX/LY
- right stick → RX/RY
- combined DirectInput Z axis is split around center into LT/RT 0-255

The validated right-stick mapping for this driver/controller combination swaps the raw R/U axes and inverts Y.

## Paddles

Classic XInput has no four independent Elite paddle bits. The bridge therefore keeps the physical buttons 11-14 visible through a private RAW extension while optionally mapping each paddle to a standard XInput button. The Control Center edits this mapping visually.

## Rumble

`XInputSetState()` sends real vibration through the Microsoft XUSB device interface. The bridge opens the XUSB interface class and sends IOCTL `0x8000A010` using the five-byte set-state structure (device index, LED state, left motor, right motor, flags). The tested chain is:

```text
Game → XInputSetState → bridge → XUSB IOCTL → xb1usb → GIP → Elite 2 motors
```

Left motor, right motor and both motors were verified physically.

## Deployment

Keep the bridge DLL local to the game directory. Do **not** replace XInput DLLs in `System32`.
