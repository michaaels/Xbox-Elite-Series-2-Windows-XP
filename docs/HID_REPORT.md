# HID report extension for Elite Series 2 paddles

The original driver submits a fixed 14-byte virtual HID input report. The final implementation deliberately preserves that report length instead of replacing the descriptor with a larger custom report.

## Original layout

The report builder maps:

- bytes 0-1: X
- bytes 2-3: Y
- bytes 4-5: Rx
- bytes 6-7: Ry
- bytes 8-9: Z
- byte 10: buttons 1-8
- byte 11: buttons 9-10 + hat + padding
- bytes 12-13: padding in the original layout

## Paddle extension

The final descriptor reuses the original final padding area:

- byte 12 low nibble: buttons 11-14
- byte 12 high nibble: padding
- byte 13: padding

The descriptor remains exactly 120 bytes and the runtime report remains exactly 14 bytes. This avoided the Code 10 regression observed in an earlier attempt that replaced the descriptor/report model more aggressively.

For the tested Elite 2 firmware layout, paddle state arrives through GIP firmware command `0x0C`; byte 18 bits 0-3 represent the four paddles. The handler stores the nibble in driver context. The normal input-report path then merges it into report byte 12, so the paddles are emitted in sync with ordinary HID input.

This exposes the four rear paddles independently as HID buttons 11-14 while preserving the standard 10 controller buttons.
