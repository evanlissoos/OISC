#!bin/bash

COMMAND=${1:-help}
IN_FILE=${2}
OUT_FILE=${3:-out.bin}

if [ $COMMAND == "help" ]; then
  echo Possible commands are: help, init, asm and sim
elif [ $COMMAND == "init" ]; then
  make -C src/simulation/
  make cleano -C src/simulation/
elif [ $COMMAND == "asm" ]; then
  python src/assembler/oisc_assembler.py -i $IN_FILE -o $OUT_FILE
elif [ $COMMAND == "sim" ]; then
  ./src/simulation/oisc
fi
