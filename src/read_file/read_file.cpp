#include "read_file.h"

elem_t* buffer_to_tokens(char* buffer, uint32_t buffer_size, 
                         uint32_t* count) {
    *count = 0;
    for (uint32_t i = 0; i < buffer_size; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\0' || buffer[i] == ' ') {
            (*count)++;
        }
    }

    elem_t* tokens = (elem_t*)calloc(*count, sizeof(elem_t));
    if (!tokens) {
        fprintf(stderr, RED "Error with tokens allocation\n" RESET);
        return NULL;
    }
 
    int token_idx = 0;
    char* line_start = (char*)buffer;

    for (uint32_t i = 0; i < buffer_size; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\0' || buffer[i] == ' ') {
            buffer[i] = '\0';

            tokens[token_idx].string = line_start;
            tokens[token_idx].len = &buffer[i] - line_start;

            token_idx++;
            line_start = &buffer[i + 1];
        }
    }
 
    return tokens;
}

char* read_file(FILE* in_file, uint32_t* buffer_size) {
    int fd = fileno(in_file);
    struct stat input_info;
    fstat(fd, &input_info);

    if (!input_info.st_size) {
        fprintf(stderr, RED "Empty expression\n" RESET);
        return NULL;
    }

    char* buff = (char*)calloc((uint32_t)input_info.st_size + 1, sizeof(char));

    uint32_t bytes_read = fread(buff, sizeof(buff[0]),
                               (uint32_t)input_info.st_size, in_file);

    buff[bytes_read] = '\0';

    *buffer_size = bytes_read;

    return buff;
}
