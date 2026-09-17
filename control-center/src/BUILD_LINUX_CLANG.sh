#!/bin/sh
set -eu
clang --target=i686-pc-windows-msvc -c XboxElite2ControlCenter.cpp -o XboxElite2ControlCenter.obj -O2 -fno-exceptions -fno-rtti -fno-stack-protector -fno-builtin
clang --target=i686-pc-windows-msvc -c imports_gui.s -o imports_gui.obj
lld-link /out:XboxElite2ControlCenter.exe /subsystem:windows,5.01 /machine:x86 /entry:mainCRTStartup /nodefaultlib /fixed /dynamicbase:no /nxcompat:no /safeseh:no XboxElite2ControlCenter.obj imports_gui.obj
rm -f XboxElite2ControlCenter.obj imports_gui.obj
