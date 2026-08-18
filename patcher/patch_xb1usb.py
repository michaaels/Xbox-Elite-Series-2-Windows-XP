#!/usr/bin/env python3
"""Reproduce the validated XP-compatible kernel from a user-supplied original xb1usb.sys.

This repository intentionally does not redistribute Microsoft's original xb1usb.sys.
"""
from pathlib import Path
import argparse, hashlib, json

HERE = Path(__file__).resolve().parent
MANIFEST = HERE / "patch_manifest.json"

def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("input", help="Original Microsoft xb1usb.sys (x86, 6.2.11059.0)")
    ap.add_argument("-o", "--output", default="xboxelite2xp.sys")
    args = ap.parse_args()

    m = json.loads(MANIFEST.read_text(encoding="utf-8"))
    src = bytearray(Path(args.input).read_bytes())
    if len(src) != m["input"]["size"]:
        raise SystemExit(f"ERROR: input size {len(src)} != expected {m['input']['size']}")
    got = sha256(src)
    if got != m["input"]["sha256"]:
        raise SystemExit(f"ERROR: wrong input SHA256\n got: {got}\nwant: {m['input']['sha256']}")

    for p in m["patches"]:
        off = p["offset"]
        old = bytes.fromhex(p["original"])
        new = bytes.fromhex(p["patched"])
        if bytes(src[off:off+len(old)]) != old:
            raise SystemExit(f"ERROR: bytes at 0x{off:X} do not match manifest")
        src[off:off+len(old)] = new

    out = bytes(src)
    got_out = sha256(out)
    if got_out != m["output"]["sha256"]:
        raise SystemExit(f"ERROR: output verification failed\n got: {got_out}\nwant: {m['output']['sha256']}")
    Path(args.output).write_bytes(out)
    print("OK")
    print("Output :", args.output)
    print("SHA256 :", got_out)

if __name__ == "__main__":
    main()
