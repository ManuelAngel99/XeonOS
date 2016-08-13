#!/bin/sh

LIBRARIES="math stdio stdlib string"

for LIBRARY in LIBRARIES; do
	cd LIBRARY
	echo ls *.c
done