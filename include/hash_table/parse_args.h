#pragma once

#include <argp.h>
#include <string.h>

typedef struct {
    char* input_filename;
    int func_number;
} args_t;

extern struct argp argp;
