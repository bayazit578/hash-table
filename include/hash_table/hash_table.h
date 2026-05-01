#pragma once

#include <cinttypes>
#include <stdio.h>
#include <string.h>
#include <hashtable.h>
#include <nmmintrin.h>
#include <immintrin.h>

#include "hash_funcs.h"
#include "list.h"
#include "read_file_types.h"

extern "C" int my_strcmp(const char* s1, const char* s2);

typedef uint32_t (*hash_func_t) (elem_t elem); 

typedef struct {
    const char* fun_name;
    hash_func_t func;
    uint32_t bucket_counter;
} hash_info_t;

extern const uint32_t TABLE_SIZE;
extern const uint32_t MAX_NAME_LEN;

void hash_table_dump(const char* output_filename, uint32_t hash_number);
void hash_table_dump_buckets(FILE* list_len_out, uint32_t hash_number, uint32_t word_count);
bool hash_table_search_(elem_t elem, uint32_t hash_number);
bool hash_table_search0(elem_t elem, uint32_t hash_number);
bool hash_table_search1(elem_t elem, uint32_t hash_number);
bool hash_table_search2(elem_t elem, uint32_t hash_number);
bool hash_table_search3(elem_t elem, uint32_t hash_number);
void hash_table_insert(elem_t elem, uint32_t hash_number);
int strcmp_32(const char* a, const char* b);
