#include "hash_table.h"
#include "list.h"

static list_t* hash_table[TABLE_SIZE] = {NULL};

static const uint32_t MAX_NAME_LEN = 100;

void hash_table_dump(const char* output_filename) {
    if (!output_filename) {
        fprintf(stderr,
            RED "No input filename for hashtable dump\n" RESET);
        return;
    }
    
    uint32_t file_counter = 0;
    uint32_t i = 0;

    // for (uint32_t i = 0; i < TABLE_SIZE; i++) {
    //     if (hash_table[i] != NULL) {
    //         char bucket_filename[MAX_NAME_LEN];
    //         snprintf(bucket_filename, MAX_NAME_LEN,
    //                  "%s_bucket%u", output_filename, i);
    //
    //         list_dump(hash_table[i], bucket_filename, &file_counter);
    //     } else {
    //         printf("Bucket [%u]: (empty)\n", i);
    //     }
    // }

    char bucket_filename[MAX_NAME_LEN];
    snprintf(bucket_filename, MAX_NAME_LEN,
             "%s_bucket%u", output_filename, i);

    list_dump(hash_table[i], bucket_filename, &file_counter);

    printf(GREEN 
        "\n=== Dump complete. Created %d dump files ===\n" RESET, 
        file_counter);
}

uint32_t hash_table_insert(elem_t elem) {
    int ind = HASH_FUN(elem)

    static uint32_t bucket_counter = 0;

    if (!hash_table[ind]) {
        hash_table[ind] = list_create();
        bucket_counter++;
    }

    list_push_back(hash_table[ind], &elem);

    return bucket_counter;
}

int hash_fun_1(elem_t elem) {
    return 0;
}

int hash_fun_2(elem_t elem) {
    int hash = elem.string[0];
    return hash;
}

int hash_fun_3(elem_t elem) {
    int hash = elem.len;
    return hash;
}

int hash_fun_4(elem_t elem) {
    int hash = 0;
    for (uint32_t i = 0; i < elem.len; i++) {
        hash += elem.string[i];
    }

    return hash;            
}   

int hash_fun_5(elem_t elem) {
    int hash = 0;
    for (uint32_t i = 0; i < elem.len; i++) {
        hash = (hash << 1) ^ elem.string[i];
    }

    return hash;
}

int hash_fun_6(elem_t elem) {
    int hash = 0;
    return hash;
}
