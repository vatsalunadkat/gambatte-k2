#!/bin/bash
# Name: GambatteK2 v0.3
# Author: CrazyElectron1
# DontUseFBInk
# Last-opened: 1753623671

timestamp=$(date +%s)
sed -i "s/^# Last-opened:.*/# Last-opened: $timestamp/" "$0" &

ARCH="armel"
# Check if the Kindle is ARMHF or ARMEL
if [ -f /lib/ld-linux-armhf.so.3 ]; then
    ARCH="armhf"
fi

cd /mnt/us/extensions/gambatte-k2
/mnt/us/extensions/gambatte-k2/gambatte-k2-$ARCH
