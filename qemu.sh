#!/bin/sh
set -e
. ./clean.sh
. ./iso.sh 
qemu-system-i386 -cdrom XeonOS.iso