# Game compatibility

## Confirmed

### GTA III / GTA Vice City

Confirmed with GInput installed in each game folder. The tested chain is:

```text
GTA III / Vice City → GInput → XInput bridge → TEST2M/v1.0 kernel → Elite Series 2
```

Normal gameplay and vibration were confirmed.

## Halo: Combat Evolved PC / Custom Edition

Halo's original controller UI is DirectInput-oriented and may show generic labels such as `Button 1` and `Axis`. That does not mean the driver mapping is wrong. Game/mod-specific controller-label support is required to display human-readable names or Xbox-style prompts.

## Generic XInput deployment

For a compatible game, keep the bridge local to the game directory:

```text
<GameFolder>\xinput1_3.dll
<GameFolder>\xinput9_1_0.dll
<GameFolder>\XInputBridgeXP.ini
```

Do not install the bridge in System32.

The Control Center can select an arbitrary game EXE, install the bridge into that EXE's directory and write a per-game paddle mapping.
