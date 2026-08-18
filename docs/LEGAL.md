# Legal / redistribution notes

This is an unofficial reverse-engineering and compatibility project. It is not affiliated with, sponsored by or endorsed by Microsoft.

The repository should not be interpreted as relicensing Microsoft's driver binaries or third-party mods.

## Microsoft driver

The reproducible workflow identifies the exact supported original `xb1usb.sys` by size and SHA-256 and applies a deterministic byte patch to a copy supplied by the user. The public repository therefore does not need to distribute Microsoft's original SYS.

Original supported SHA-256:

```text
bd4cb415a34022ac01e5b8f4915735be421958e8534258c86f9805652736c73f
```

Validated patched output SHA-256:

```text
1fe18559ae33e46694669556177cdacf1b39f104fa9760d5563696dffd4fa649
```

## KMDF co-installer

`WdfCoInstaller01009.dll` is a Microsoft component and is not relicensed by this project. Obtain it from an appropriate Microsoft/WDK source or an existing lawful installation.

## Third-party game mods

GInput, Chimera and similar projects retain their own licenses and distribution terms. They are referenced for interoperability and should not be bundled without checking those terms.
