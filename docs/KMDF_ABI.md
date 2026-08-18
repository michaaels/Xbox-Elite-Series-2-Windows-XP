# KMDF 1.11 → 1.9 ABI findings

The original 2014 x86 `xb1usb.sys` is a KMDF 1.11 driver. Windows XP SP3 uses KMDF 1.9. Editing only the INF or the embedded WDF bind metadata was insufficient because the driver passes structure sizes compiled for 1.11 into KMDF 1.9.

## WDF bind retarget

The driver bind metadata was retargeted from KMDF 1.11 to 1.9 and the function count reduced from 432 to 396. Static reverse engineering showed that the actual driver references stay below the KMDF 1.9 function-table limit.

## `WDF_IO_QUEUE_CONFIG`

DebugView exposed the first concrete failure:

```text
XB1USB: WdfIoQueueCreate failed with status 0xC0000004
```

`0xC0000004` is `STATUS_INFO_LENGTH_MISMATCH`.

The x86 structure is `0x38` bytes in KMDF 1.11 and `0x34` in KMDF 1.9. The 1.11 version contains an additional final `WDFDRIVER Driver` field. All three size immediates used by the driver were patched `0x38 → 0x34`.

## `WDF_PNPPOWER_EVENT_CALLBACKS`

The next proven mismatch was `WDF_PNPPOWER_EVENT_CALLBACKS.Size`: `0x48` in the 1.11 build versus `0x44` for the XP/KMDF 1.9 ABI. Patching `0x48 → 0x44` was the PnP breakthrough that allowed the parent device to start and enumerate its USB/HID child.

## Result

These were the two ABI mismatches proven by runtime behavior. Other WDF structures were not blindly patched. The final driver keeps this conservative approach.
