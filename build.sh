#!/bin/bash

CFLAGS="-I. -Iinclude -Iinclude/list -Iinclude/hash_table -Wall -g"
SRC="src/main.cpp src/list/list.cpp src/hash_table/hash_table.cpp"
OUT_DIR="compiled"
XCUTABLE="program"

if [ $# -eq 1 ]; then
    CFLAGS+=" $1"
fi

mkdir -p $OUT_DIR
g++ -o $OUT_DIR/$XCUTABLE $SRC $CFLAGS
# ./$OUT_DIR/$XCUTABLE
