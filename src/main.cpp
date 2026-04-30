#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <argp.h>

#include "list.h"
#include "hash_table.h"
#include "read_file.h"
#include "parse_args.h"


#if defined NDEBUG
    #define DEBUG_OUTPUT(...)
#else 
    #define DEBUG_OUTPUT(...) __VA_ARGS__
#endif

int main(int argc, char* argv[]) {
    args_t args = {};
    argp_parse(&argp, argc, argv, 0, 0, &args);

    FILE* input = fopen(args.input_filename, "r");
    if (!input) {
        fprintf(stderr, RED "Error with input file opening\n" RESET);
        return EXIT_FAILURE;
    }

    char output_filename[MAX_NAME_LEN] = {};
    snprintf(output_filename, MAX_NAME_LEN, "output/hash_out%u", 
             args.func_number);

    FILE* list_len_out = fopen(output_filename, "w");
    if (!list_len_out) {
        fprintf(stderr, RED "Error with output file opening\n" RESET);
        return EXIT_FAILURE;
    }

    uint32_t buffer_size = 0;
    char* buffer = read_file(input, &buffer_size);
    
    uint32_t token_count = 0;
    elem_t* tokens = buffer_to_tokens(buffer, buffer_size, &token_count);

    uint32_t word_count = 0;
    for (uint32_t i = 0; i < token_count; i++) {
        if (!hash_table_search0(tokens[i], args.func_number)) {
            word_count++;
            hash_table_insert(tokens[i], args.func_number);
        }
    }

    DEBUG_OUTPUT(
        hash_table_dump_buckets(list_len_out, args.func_number, 
                                word_count);
    )

    bool found = true;

    for (uint32_t i = 0; i < args.iter_count; i++) {
        elem_t elem = tokens[i % token_count];
        found &= hash_table_search3(elem, args.func_number);
    }
    
    printf("%u\n", found);

    DEBUG_OUTPUT(
        hash_table_dump("hash_table", args.func_number);
    )
   
    return found;
}
