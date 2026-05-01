#!/bin/bash

XCUTABLE="compiled/program"
OUT_DIR="output"
PY_INPUT="$OUT_DIR/hash_out$1"
PY_OUT_DIR="photo_dumps"
PY_OUTPUT="$PY_OUT_DIR/hash$1_hist.png"

./build.sh -O3
./$XCUTABLE -i input_file.txt -f $1 -x $2
python plots_hash.py $PY_INPUT $PY_OUTPUT
