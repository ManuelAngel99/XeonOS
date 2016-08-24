#!/bin/bash
set -e
. ./clean.sh
. ./iso.sh 
bochs -f bochsconfig.cfg -q

