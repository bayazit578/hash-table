#pragma once

#include <cinttypes>
#include <stdio.h>
#include <string.h>
#include <hashtable.h>
#include "list.h"

#if defined HASH1
    #define HASH_FUN(...) hash_fun_1(__VA_ARGS__);
#elif defined HASH2
    #define HASH_FUN(...) hash_fun_2(__VA_ARGS__);
#elif defined HASH3
    #define HASH_FUN(...) hash_fun_3(__VA_ARGS__);
#elif defined HASH4
    #define HASH_FUN(...) hash_fun_4(__VA_ARGS__);
#elif defined HASH5
    #define HASH_FUN(...) hash_fun_5(__VA_ARGS__);
#elif defined HASH6
    #define HASH_FUN(...) hash_fun_6(__VA_ARGS__);
#else
    #define HASH_FUN(...)                               \
        -1;                                              \
        fprintf(stderr,                                   \
                RED "No selected mode for hash fun" RESET);
#endif

const uint32_t TABLE_SIZE = 1000;

typedef struct {
    const char* string;
    uint32_t len;
} elem_t;

void hash_table_dump(const char* base_filename);
uint32_t hash_table_insert(elem_t elem);
int hash_fun_1(elem_t elem);
int hash_fun_2(elem_t elem);
int hash_fun_3(elem_t elem);
int hash_fun_4(elem_t elem);
int hash_fun_5(elem_t elem);
int hash_fun_6(elem_t elem);
