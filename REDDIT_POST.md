# Suggested Reddit title

**[Release/Reverse Engineering] Xbox Elite Series 2 working on Windows XP SP3 x86 — USB driver, paddles, XInput and rumble**

I have been working on an unofficial compatibility project to get an **Xbox Elite Wireless Controller Series 2** working properly on **Windows XP SP3 32-bit** over USB.

Search keywords: **Xbox Elite Series 2 Windows XP driver, Xbox One controller Windows XP, VID_045E PID_0B00, xb1usb.sys XP, XInput Windows XP, Elite 2 paddles XP**.

### Tested hardware

- Xbox Elite Wireless Controller Series 2
- USB VID/PID: `045E:0B00`
- tested revision / bcdDevice: `0x0517`
- Windows XP SP3 x86

### Working

- both analog sticks
- D-Pad
- A/B/X/Y, LB/RB, View/Back, Menu/Start, L3/R3
- all four rear paddles as independent HID buttons 11-14
- LT/RT through the XInput bridge
- XInput input
- real left/right/both motor vibration
- visual remapping of P1/P2/P3/P4 to standard XInput buttons
- GTA III and GTA Vice City through GInput, including vibration

### Reverse-engineering summary

Microsoft's 2014 x86 Xbox One USB driver is built for **KMDF 1.11**, while Windows XP uses **KMDF 1.9**. Retargeting the WDF version alone was not enough. Runtime debugging revealed two ABI structure-size mismatches that blocked the driver:

```text
WDF_IO_QUEUE_CONFIG.Size          0x38 -> 0x34
WDF_PNPPOWER_EVENT_CALLBACKS.Size 0x48 -> 0x44
```

The first failure appeared as `WdfIoQueueCreate` returning `0xC0000004` (`STATUS_INFO_LENGTH_MISMATCH`). After the KMDF side was corrected, the Elite Series 2 also needed newer GIP initialization packets not sent by the old 2014 driver:

```text
05 20 <seq> 0F 06
4D 10 <seq> 02 07 00
```

The final HID implementation preserves the original 14-byte input report and exposes the four paddles using previously unused report bits. A separate user-mode XInput bridge provides LT/RT, normal XInput state and real XUSB/GIP rumble.

### Validation

A final diagnostic session reported:

```text
XInput errors: 0
RAW errors: 0
Buttons: 10/10
Paddles: 4/4
D-Pad directions: 8/8
LT max: 255
RT max: 255
Left stick coverage: 100% / 99%
Right stick coverage: 100% / 99%
```

### Limitations

- experimental, unofficial and unsigned
- Windows XP SP3 **32-bit only**
- wired USB is the validated path
- formally validated only on `VID_045E&PID_0B00`, revision `0x0517`
- no Bluetooth/wireless or XP x64 claim yet
- classic XInput has no four independent paddle bits, so paddles are remapped to standard XInput buttons while retaining independent RAW/HID state

### Source / technical documentation

GitHub: **https://github.com/michaaels/Xbox-Elite-Series-2-Windows-XP**

The repository contains the KMDF findings, GIP notes, HID layout, complete test history, validated hashes and a deterministic patcher. The original Microsoft SYS is not redistributed; the patcher expects the exact supported 2014 x86 `xb1usb.sys` and verifies both input and output SHA-256 values.

If anyone still runs XP and has another Xbox One / Series controller PID or Elite 2 firmware revision, test reports with VID/PID/REV would be useful.
