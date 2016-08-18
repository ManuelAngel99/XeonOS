#!/bin/sh
set -e
. ./clean.sh
. ./iso.sh 
(killall VirtualBox && sleep 1) || true
VirtualBox --startvm 'XeonOS' &