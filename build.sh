#!/bin/bash

CFLAGS="-I. -Iinclude -Iinclude/list -Iinclude/hash_table -Iinclude/read_file \
        -Wall -g -msse4.2 -march=native"
SRC="src/main.cpp src/list/list.cpp src/hash_table/hash_table.cpp \
     src/read_file/read_file.cpp src/hash_table/hash_funcs.cpp \
     src/hash_table/parse_args.cpp"
OUT_DIR="compiled"
XCUTABLE="program"
DOT_DIR="dot_files"
PNG_DIR="photo_dumps"
LEN_DIR="buscket_len"

mkdir -p $DOT_DIR $PNG_DIR $LEN_DIR

mkdir -p $OUT_DIR
g++ -o $OUT_DIR/$XCUTABLE $SRC $CFLAGS
# ./$OUT_DIR/$XCUTABLE
