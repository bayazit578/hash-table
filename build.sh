#!/bin/bash

CFLAGS="-I. -Iinclude -Iinclude/list -Iinclude/hash_table -Iinclude/read_file \
        -Wall -g -msse4.2 -march=native -fno-omit-frame-pointer -mavx2 -mavx \
        -fPIE"
SRC="src/main.cpp src/list/list.cpp src/hash_table/hash_table.cpp \
     src/read_file/read_file.cpp src/hash_table/hash_funcs.cpp \
     src/hash_table/parse_args.cpp"
OUT_DIR="compiled"
XCUTABLE="program"
DOT_DIR="dot_files"
PNG_DIR="photo_dumps"
LEN_DIR="output"

CFLAGS+=" $1 $2"

mkdir -p $DOT_DIR $PNG_DIR $LEN_DIR

mkdir -p $OUT_DIR

echo $CFLAGS
nasm -g -f elf64 -l compiled/my_strcmp.lst src/hash_table/my_strcmp.asm \
     -o compiled/my_strcmp.o
g++ -o $OUT_DIR/$XCUTABLE compiled/my_strcmp.o $SRC $CFLAGS
