#pragma once

#include "hash_table.h"
#include "read_file_types.h"

uint32_t naive_hash_1(elem_t elem);
uint32_t first_char_hash_2(elem_t elem);
uint32_t len_hash_3(elem_t elem);
uint32_t control_summ_4(elem_t elem);
uint32_t rol_hash_5(elem_t elem);
uint32_t crc_hash_6(elem_t elem);
