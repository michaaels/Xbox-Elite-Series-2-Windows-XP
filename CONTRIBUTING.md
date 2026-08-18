# Contributing

When reporting another controller/firmware revision, include:

- Windows version and x86/x64
- USB VID/PID/REV
- controller firmware/bcdDevice if known
- `joy.cpl` result
- Control Center summary/log
- whether startup vibration, XInput rumble and paddles work
- exact driver SHA-256

Do not generalize support to a new PID/firmware from a single successful enumeration. A new combination should be considered validated only after normal input, paddles and rumble have all been tested.
