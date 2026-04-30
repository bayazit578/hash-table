#include "hash_funcs.h"

uint32_t hash_fun_1(elem_t elem) {
    return 0;
}

uint32_t hash_fun_2(elem_t elem) {
    uint32_t hash = elem.string[0];
    return hash % TABLE_SIZE;
}

uint32_t hash_fun_3(elem_t elem) {
    uint32_t hash = elem.len;
    return hash % TABLE_SIZE;
}

uint32_t hash_fun_4(elem_t elem) {
    uint32_t hash = 0;
    for (uint32_t i = 0; i < elem.len; i++) {
        hash += elem.string[i];
    }

    return hash % TABLE_SIZE;            
}   

uint32_t hash_fun_5(elem_t elem) {
    uint32_t hash = 0;
    for (uint32_t i = 0; i < elem.len; i++) {
        hash = (hash << 1) ^ (hash >> 31) ^ elem.string[i];
    }

    return hash % TABLE_SIZE;
}

uint32_t hash_fun_6(elem_t elem) {
    uint32_t hash = 0;
    for (uint32_t i = 0; i < elem.len; i++) {
        hash = _mm_crc32_u8(hash, elem.string[i]);
    }

    return hash % TABLE_SIZE;
}
