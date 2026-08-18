# Elite Series 2 GIP initialization notes

After the KMDF/PnP problems were solved, the 2014 Xbox One driver still did not fully initialize an Elite Series 2. Linux `xpad` behavior was used as an external reference and the working sequence was reproduced conservatively inside the old driver.

Relevant commands:

- `GIP_CMD_POWER = 0x05`
- `GIP_CMD_FIRMWARE = 0x0C`
- `GIP_CMD_INPUT = 0x20`

The two key modern initialization packets used by the validated build are:

```text
05 20 <seq> 0F 06
4D 10 <seq> 02 07 00
```

The first is the Xbox One S / Elite 2 initialization sequence. The second enables the Elite 2 additional-input path used for features including paddles.

The validated implementation preserves Microsoft's original power, LED and configuration sequence and wraps the existing POWER_ON call so that the two additional packets are sent immediately afterward. Sequence numbers reuse/increment the driver's existing context byte and packets are sent through the driver's original asynchronous GIP send routine.

For the tested Elite 2 firmware family (`bcdDevice 0x0517`, treated as the 5.11-style layout), paddle state is received in firmware command `0x0C`, byte 18 low nibble. The final implementation stores that nibble and merges it into the next normal HID input report instead of forcing an immediate report from the firmware callback.
