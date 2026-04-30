#pragma once

#include <argp.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char* input_filename;
    int func_number;
    uint64_t iter_count;
} args_t;

extern struct argp argp;
