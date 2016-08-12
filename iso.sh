#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/XeonOS.kernel isodir/boot/XeonOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "XeonOS" {
	multiboot /boot/XeonOS.kernel
}
EOF
grub-mkrescue -o XeonOS.iso isodir