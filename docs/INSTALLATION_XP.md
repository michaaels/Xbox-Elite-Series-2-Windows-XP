# Installation on Windows XP SP3 x86

## Requirements

- Windows XP SP3 32-bit
- Xbox Elite Wireless Controller Series 2 over USB
- hardware ID `USB\VID_045E&PID_0B00`
- KMDF 1.9 / `WdfCoInstaller01009.dll`
- patched `xboxelite2xp.sys` generated from the exact supported 2014 x86 `xb1usb.sys`

## Generate the driver

```text
python patcher\patch_xb1usb.py xb1usb.sys -o driver\xboxelite2xp.sys
```

The output SHA-256 must be:

```text
1fe18559ae33e46694669556177cdacf1b39f104fa9760d5563696dffd4fa649
```

Place `WdfCoInstaller01009.dll` beside the INF/SYS when installing on XP.

## Important migration rule

If an earlier experimental service is installed, disconnect the controller and reboot XP before installing the final service name. During development, XP sometimes kept the previous SYS image loaded and reported Code 38 (`CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD`).

## Install

Use the included INF or the installer package. The final service is:

```text
xb1usb_elite2xp
```

After installation, reconnect the controller and verify:

- no Device Manager error
- `joy.cpl` responds
- both sticks / D-Pad / buttons respond
- paddles appear as buttons 11-14
- Control Center can read the controller
- XInput bridge can command left/right rumble

## Do not

Do not install this experimental XP kernel driver on Windows 10/11. The Control Center is cross-version, but the kernel compatibility patch specifically targets XP/KMDF 1.9.
