#include "hash_table.h"
#include "hash_funcs.h"

hash_info_t stats[] = {
    {"naive_hash_1"     , naive_hash_1     , 0},
    {"first_char_hash_2", first_char_hash_2, 0},
    {"len_hash_3"       , len_hash_3       , 0},
    {"control_summ_4"   , control_summ_4   , 0},
    {"rol_hash_5"       , rol_hash_5       , 0},
    {"crc_hash_6"       , crc_hash_6       , 0}
};

const uint32_t TABLE_SIZE = 4000;

static list_t* hash_table[TABLE_SIZE] = {};

const uint32_t MAX_NAME_LEN = 100;

void hash_table_dump(const char* output_filename, uint32_t hash_number) {
    if (!output_filename) {
        fprintf(stderr,
            RED "No input filename for hashtable dump\n" RESET);
        return;
    }
    
    char html_filename[MAX_NAME_LEN] = {};
    snprintf(html_filename, MAX_NAME_LEN, 
            "photo_dumps/%s.html", stats[hash_number].fun_name);
    printf("%s\n", stats[hash_number].fun_name);
    FILE* html_out = fopen(html_filename, "w");
    if (!html_out) {
        fprintf(stderr, RED "Error with .html opening" RESET);
        return;
    }

    fprintf(html_out,
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <title>List Dump</title>\n"
        "    <style>\n"
        "        body { font-family: Fira Mono; max-width: 900px; "
        "margin: 20px auto; }\n"
        "        h2 { color: #333; }\n"
        "        img { max-width: 100%%; border: 1px solid #ddd; "
        "margin: 10px 0; }\n"
        "    </style>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>List Dump Report</h1>\n"
        "<img src=\"hash%u_hist.png\">\n",
        hash_number
    );

    uint32_t cell_counter = 0;
    uint32_t bucket_counter = 0;

    while(cell_counter < TABLE_SIZE) {
        if (hash_table[cell_counter]) {
            merge_list_dumps(hash_table[cell_counter], output_filename, 
                             cell_counter, bucket_counter, html_out);
            bucket_counter++;
        }

        cell_counter++;
    }

    fprintf(html_out,
        "</body>\n"
        "</html>\n"
    );

    fclose(html_out);

    stats[hash_number].bucket_counter = bucket_counter;
}

void hash_table_dump_buckets(FILE* list_len_out, uint32_t hash_number, 
                             uint32_t word_count) {
    fprintf(list_len_out, "%u\n", 
            stats[hash_number].bucket_counter);
    fprintf(list_len_out, "%.3f\n", 
            (float)stats[hash_number].bucket_counter / (float)word_count);

    for (uint32_t i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i]) {
            fprintf(list_len_out, "%u: %u\n",
                    i, hash_table[i]->size);
        } else {
            fprintf(list_len_out, "%u: 0\n", i);
        }
    }
}


bool hash_table_search_(elem_t elem, uint32_t hash_number) {
    int bucket_index = stats[hash_number].func(elem);

    list_t* list = hash_table[bucket_index];
    if (!list) {
        return false;
    }

    uint32_t list_ind = list->contents[0].next; 
    while (list_ind != 0) {
        elem_t* stored = (elem_t*)list->contents[list_ind].value;

        if (stored && strcmp(stored->string, elem.string) == 0) {
            return true;        
        }
        list_ind = list->contents[list_ind].next;
    }

    return false;
}

bool hash_table_search0(elem_t elem, uint32_t hash_number) {
    int bucket_index = stats[hash_number].func(elem);

    list_t* list = hash_table[bucket_index];
    if (!list) {
        return false;
    }

    node_t* contents = list->contents;
    uint32_t list_ind = contents[0].next; 
    while (list_ind != 0) {
        elem_t* stored = (elem_t*)contents[list_ind].value;

        if (stored && strcmp(stored->string, elem.string) == 0) {
            return true;        
        }
        list_ind = contents[list_ind].next;
    }

    return false;
}

bool hash_table_search1(elem_t elem, uint32_t hash_number) {
    int bucket_index = stats[hash_number].func(elem);

    list_t* list = hash_table[bucket_index];
    if (!list) {
        return false;
    }

    node_t* contents = list->contents;
    uint32_t list_ind = contents[0].next; 
    while (list_ind != 0) {
        elem_t* stored = (elem_t*)contents[list_ind].value;

        if (stored && strcmp_32(stored->string, elem.string) == 0) {
            return true;        
        }
        list_ind = contents[list_ind].next;
    }

    return false;
}

bool hash_table_search2(elem_t elem, uint32_t hash_number) {
    int bucket_index = stats[hash_number].func(elem);

    list_t* list = hash_table[bucket_index];
    if (!list) {
        return false;
    }

    node_t* contents = list->contents;
    uint32_t list_ind = contents[0].next;
    while (list_ind != 0) {
        elem_t* stored = (elem_t*)contents[list_ind].value;

        if (stored && my_strcmp(stored->string, elem.string) == 0) {
            return true;        
        }
        list_ind = contents[list_ind].next;
    }

    return false;
}

bool hash_table_search3(elem_t elem, uint32_t hash_number) {
    int bucket_index = stats[hash_number].func(elem);
    list_t* list = hash_table[bucket_index];
    if (!list) return false;

    node_t* contents = list->contents;
    const char* search_str = elem.string;
    uint32_t list_ind = contents[0].next;
    bool result;
    
    asm volatile(
        ".intel_syntax noprefix\n\t"
        
        "push       rbx\n\t"
        "push       r12\n\t"
        "push       r13\n\t"
        
        "mov        rbx, %[search]\n\t"
        "mov        r12, %[cont]\n\t"
        "mov        r13d, %[ind]\n\t"
        "xor        %[res], %[res]\n\t"
        
        "mov        rdi, rbx\n\t"
        
        "test       r13d, r13d\n\t"
        "jz         1f\n\t"
        
        ".align 32\n\t"
        "3:\n\t"
        
        "mov        rax, r13\n\t"
        "shl        rax, 4\n\t"
        "mov        rax, [r12 + rax]\n\t"
        "test       rax, rax\n\t"
        "jz         4f\n\t"
        
        "mov        rsi, [rax]\n\t"
        
        "call       my_strcmp\n\t"
        "test       eax, eax\n\t"
        "je         2f\n\t"
        
        "4:\n\t"
        "mov        rax, r13\n\t"
        "shl        rax, 4\n\t"
        "mov        r13d, [r12 + rax + 8]\n\t"
        "test       r13d, r13d\n\t"
        "jnz        3b\n\t"
        
        "1:\n\t"
        "vzeroupper\n\t"
        "pop        r13\n\t"
        "pop        r12\n\t"
        "pop        rbx\n\t"
        "jmp        7f\n\t"
        
        "2:\n\t"
        "mov        %[res], 1\n\t"
        "vzeroupper\n\t"
        "pop        r13\n\t"
        "pop        r12\n\t"
        "pop        rbx\n\t"
        
        "7:\n\t"
        ".att_syntax prefix\n\t"
        
        : [res] "=r" (result)
        : [search] "r" (search_str),
          [cont] "r" (contents),
          [ind] "r" (list_ind)
        : "rax", "rbx", "r12", "r13",
          "rdi", "rsi", "rcx", "rdx",
          "ymm0", "ymm1", "ymm2", "ymm3",
          "cc", "memory"
    );
    
    return result;
}

void hash_table_insert(elem_t elem, uint32_t hash_number) {
    int ind = stats[hash_number].func(elem);

    if (!hash_table[ind]) {
        hash_table[ind] = list_create();
        stats[hash_number].bucket_counter++;
    }

    elem_t* alloced_elem = (elem_t*)calloc(1, sizeof(elem_t));
    *alloced_elem = elem;
    list_push_front(hash_table[ind], alloced_elem);
}

int strcmp_32(const char* a, const char* b) {
    __m256i va = _mm256_loadu_si256((const __m256i*)a);
    __m256i vb = _mm256_loadu_si256((const __m256i*)b);
    
    __m256i zero = _mm256_setzero_si256();
    __m256i null_a = _mm256_cmpeq_epi8(va, zero);
    __m256i null_b = _mm256_cmpeq_epi8(vb, zero);
    
    __m256i cmp = _mm256_cmpeq_epi8(va, vb);
    
    int32_t mask_eq = _mm256_movemask_epi8(cmp);
    int32_t mask_null_a = _mm256_movemask_epi8(null_a);
    int32_t mask_null_b = _mm256_movemask_epi8(null_b);
    
    int32_t first_null = ffs(mask_null_a | mask_null_b);
    
    if (first_null == 0) {
        return (mask_eq == -1) ? 0 : 1;
    }
    
    int32_t check_mask = (1 << first_null) - 1;
    return ((mask_eq & check_mask) == check_mask) ? 0 : 1;
}
