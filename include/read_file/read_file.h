#pragma once

#include <cstdint>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include "color.h"

#include "read_file_types.h"

elem_t* buffer_to_tokens(char* buffer, uint32_t buffer_size,
                         uint32_t* token_count);
char* read_file(FILE* in_file, uint32_t* buffer_size);
void destroy_tokens(elem_t* tokens, uint32_t token_count);
