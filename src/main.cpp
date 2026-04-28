#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <argp.h>

#include "list.h"
#include "hash_table.h"
#include "read_file.h"
#include "parse_args.h"

const uint32_t ITER_COUNT = 1000;

int main(int argc, char* argv[]) {
    args_t args = {};
    argp_parse(&argp, argc, argv, 0, 0, &args);

    FILE* input = fopen(args.input_filename, "r");
    if (!input) {
        fprintf(stderr, RED "Error with input file opening\n" RESET);
        return EXIT_FAILURE;
    }

    FILE* list_len_out = fopen("busket_len", "w");
    if (!list_len_out) {
        fprintf(stderr, RED "Error with output file opening\n" RESET);
        return EXIT_FAILURE;
    }

    uint32_t buffer_size = 0;
    char* buffer = read_file(input, &buffer_size);
    
    uint32_t token_count = 0;
    elem_t* tokens = buffer_to_tokens(buffer, buffer_size, &token_count);
    
    for (uint32_t i = 0; i < token_count; i++) {
        hash_table_insert(tokens[i], args.func_number);
    }

    hash_table_dump_buckets(list_len_out, args.func_number);

    for (uint32_t i = 0; i < ITER_COUNT; i++) {
        elem_t elem = tokens[i % token_count];
        hash_table_search(elem, args.func_number);
    }

    hash_table_dump("hash_table", args.func_number);
    return EXIT_SUCCESS;
}
