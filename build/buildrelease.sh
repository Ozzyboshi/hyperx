#!/bin/bash
rm -f CMakeCache.txt
cmake .. -DCMAKE_TOOLCHAIN_FILE=/root/AmigaCMakeCrossToolchains/m68k.cmake -DM68K_TOOLCHAIN_PATH=/opt/amiga -DM68K_CPU=68000 -DM68K_FPU=soft -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/
make clean
make
