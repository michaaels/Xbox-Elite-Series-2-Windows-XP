# Xbox Elite Series 2 en Windows XP SP3 (x86)

Proyecto no oficial de ingeniería inversa para añadir compatibilidad USB por cable del **Xbox Elite Wireless Controller Series 2** (`VID_045E`, `PID_0B00`) en **Windows XP SP3 de 32 bits**.

Se partió del driver x86 de Xbox One de Microsoft de 2014 (`xb1usb.sys` 6.2.11059.0). El trabajo consistió en retargetear KMDF 1.11 a KMDF 1.9, corregir incompatibilidades ABI, implementar la inicialización GIP requerida por el Elite Series 2, exponer los cuatro paddles y añadir un bridge XInput con vibración real.

## Validado

- Windows XP SP3 x86
- USB `045E:0B00`
- revisión/bcdDevice probada `0x0517`
- sticks izquierdo y derecho
- D-Pad
- botones 1-10
- paddles 11-14
- LT/RT mediante bridge XInput
- vibración izquierda/derecha/ambos
- GTA III y GTA Vice City mediante GInput

## Punto técnico clave

El driver original usa KMDF 1.11, mientras que XP usa KMDF 1.9. Cambiar la versión no fue suficiente: hubo que corregir dos tamaños de estructuras ABI comprobados en ejecución:

```text
WDF_IO_QUEUE_CONFIG.Size          0x38 -> 0x34
WDF_PNPPOWER_EVENT_CALLBACKS.Size 0x48 -> 0x44
```

Después se añadieron los paquetes GIP modernos necesarios para inicializar el Elite Series 2 y se extendió de forma conservadora el reporte HID de 14 bytes para exponer los cuatro paddles.

## Reproducción

El repositorio no necesita redistribuir el `xb1usb.sys` original de Microsoft. Usa `patcher/patch_xb1usb.py` con la versión exacta soportada. El script verifica el SHA-256 de entrada, aplica el manifiesto de 34 rangos y verifica el SHA-256 final.

Consulta `docs/` para el historial completo de pruebas, ABI KMDF, GIP, HID, XInput y validación.
