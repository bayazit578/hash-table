#include "parse_args.h"

#include <cstdlib>
#include <cstdio>

static struct argp_option options[] = {
    {"func", 'f', "NUM", 0, "Uses the hash function number NUM (0 - 5)"},
    {"input", 'i', "FILE", 0, "Read input from FILE"},
    {0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    args_t* args = (args_t*)state->input;

    switch (key) {
        case 'f': {
            int num = atoi(arg);
            if (num < 0 || num > 5) {
                argp_error(state, "Function number must be between 0 and 5, got %d", num);
                return ARGP_ERR_UNKNOWN;
            }
            args->func_number = num;
            break;
        }

        case 'i':
            if (state->arg_num >= 1) {
                argp_error(state, "Too many arguments");
                return ARGP_ERR_UNKNOWN;
            } 
            args->input_filename = arg;

            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return EXIT_SUCCESS;
}

struct argp argp = {options, parse_opt, 0,
                    "Hash-table realization with words from input "
                    "using selected hash func"};
