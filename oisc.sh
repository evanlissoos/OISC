#!/bin/bash

COMMAND=${1:-help}
IN_FILE=${2}
OUT_FILE=${3:-out.bin}

if [ $COMMAND == "help" ]; then
	echo Possible commands are: help, init, clean, asm and sim
elif [ $COMMAND == "init" ]; then
	make -C src/simulation/
	make cleano -C src/simulation/
elif [ $COMMAND == "asm" ]; then
	if command -v python3 > /dev/null 2>&1; then
    python3 -B src/assembler/oisc_assembler.py -i $IN_FILE -o $OUT_FILE
	else
		echo Python 3 required, sorry fam
	fi
elif [ $COMMAND == "sim" ]; then
	./src/simulation/oisc
elif [ $COMMAND == "clean" ]; then
	rm src/simulation/oisc 2> /dev/null
	rm src/assembler/lib/*.pyc 2> /dev/null
	rm src/assembler/*.pyc 2> /dev/null
	rm -rf src/assembler/__pycache__ 2> /dev/null
	rm -rf src/assembler/lib/__pycache__ 2> /dev/null
	rm out.bin
fi
