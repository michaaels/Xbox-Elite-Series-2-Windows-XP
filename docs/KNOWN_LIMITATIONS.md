# Known limitations

- Experimental, unofficial and unsigned driver.
- Validated on Windows XP SP3 **x86 only**.
- Validated over wired USB only.
- Formally validated hardware ID: `USB\VID_045E&PID_0B00`.
- Tested revision / bcdDevice: `0x0517`.
- No claim for Bluetooth, wireless adapters, Windows XP x64 or other Xbox controller PIDs yet.
- Classic XInput has no four independent Elite paddle fields. Paddles are preserved as HID/RAW buttons 11-14 and may be remapped to standard XInput buttons.
- Some DirectInput-era games display generic `Button N` / `Axis N` labels; that is controlled by the game UI/input layer.
- Battery/audio/Guide/keystroke XInput edge APIs are not claimed as full Microsoft-driver parity.
- Only controller index 0 is the primary validated bridge path.

New hardware/firmware should be treated as unvalidated until enumeration, normal input, paddles and rumble are all tested.
