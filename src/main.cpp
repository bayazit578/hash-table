#include <cstdlib>
#include <stdio.h>
#include <stdint.h>

#include "list.h"
#include "hash_table.h"
#include "read_file.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "No input file");
        return EXIT_FAILURE;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error with fopen");
        return EXIT_FAILURE;
    }

    uint32_t buffer_size = 0;
    char* buffer = read_file(input, &buffer_size);
    
    uint32_t token_count = 0;
    elem_t* tokens = buffer_to_tokens(buffer, buffer_size, &token_count);

    for (uint32_t i = 0; i < token_count; i++) {
        hash_table_insert(tokens[i]);
    }

    hash_table_dump("hash_table");
    return EXIT_SUCCESS;
}
