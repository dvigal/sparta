#! /bin/bash

make clean && make && qemu-system-i386 -fda kernel.img -monitor stdio #-s -S & #-d in_asm,pcall,cpu #-D qemu.log

