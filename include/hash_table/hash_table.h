#pragma once

#include <cinttypes>
#include <stdio.h>
#include <string.h>
#include <hashtable.h>
#include <nmmintrin.h>

#include "hash_funcs.h"
#include "list.h"
#include "read_file_types.h"

typedef int (*hash_func_t) (elem_t elem); 

typedef struct {
    hash_func_t func;
    uint32_t bucket_counter;
} hash_info_t;

extern const uint32_t TABLE_SIZE;

void hash_table_dump(const char* output_filename, uint32_t hash_number);
void hash_table_dump_buckets(FILE* list_len_out, uint32_t hash_number);
bool hash_table_search(elem_t elem, uint32_t hash_number);
uint32_t hash_table_insert(elem_t elem, uint32_t hash_number);
