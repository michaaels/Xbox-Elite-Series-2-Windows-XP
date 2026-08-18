# Experimental test history

This file records the important milestones so future work does not repeat failed experiments.

## TEST1 — INF-only PID addition

Added `USB\VID_045E&PID_0B00` to the Microsoft package. Device associated but failed DriverEntry / Code 37.

## TEST2 — WDF bind retarget

Embedded WDF bind metadata changed from KMDF 1.11 to 1.9 and function count 432 → 396. This was necessary but not sufficient.

## TEST2C / TEST2D — clean service names

Unique service/SYS names were introduced to avoid XP reusing an old loaded image. Intermediate Code 38 results demonstrated that reusing the same binary/service name during iterative kernel testing can be misleading.

## TEST2E — `WDF_IO_QUEUE_CONFIG` ABI fix

DebugView showed:

```text
XB1USB: WdfIoQueueCreate failed with status 0xC0000004
```

All three `WDF_IO_QUEUE_CONFIG.Size` immediates were changed from `0x38` to `0x34`. Parent device could start further than previous builds.

## TEST2F / TEST2F2 / TEST2G

Experimental proactive power/init attempts. These contained control-flow/stack issues and are not bases for later work.

## TEST2H / TEST2I

Control flow was corrected and additional logging/wrapping explored. Still no complete Elite 2 enumeration.

## TEST2J — PnP breakthrough

`WDF_PNPPOWER_EVENT_CALLBACKS.Size` changed from `0x48` to `0x44`. This allowed the physical parent to start and the `USB/HID ... IG_00` children to appear. Startup vibration and LED also worked.

## TEST2K — modern Elite 2 initialization

Based directly on TEST2J. Two modern GIP packets were inserted immediately after Microsoft's original POWER_ON call:

```text
05 20 <seq> 0F 06
4D 10 <seq> 02 07 00
```

This became the known-good standard-input baseline. `joy.cpl` and normal controls worked.

## TEST2L — failed paddle experiment

Attempted a compact replacement HID descriptor plus immediate report submission from the firmware callback. This regressed to Code 10. It is intentionally not reused.

## TEST2M — stable final kernel

Built from TEST2K, not TEST2L.

Key design decisions:

- keep original 14-byte report length
- keep descriptor at 120 bytes
- expose buttons 11-14 using existing padding bits
- parse paddle nibble from firmware command `0x0C`
- store paddle state and merge it into the next normal input report
- do not force an HID report directly from the firmware callback

Validated SHA-256:

```text
1fe18559ae33e46694669556177cdacf1b39f104fa9760d5563696dffd4fa649
```

TEST2M is the kernel payload renamed to `xboxelite2xp.sys` for version 1.0.

## User-mode work after TEST2M

A native XP-compatible tester confirmed full stick range, all ten standard buttons, four paddles and POV directions. A user-mode XInput bridge then added XInput state and real rumble through XUSB. GTA III and GTA Vice City were subsequently confirmed through GInput with vibration working in-game.
