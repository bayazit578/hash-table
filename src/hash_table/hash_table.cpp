#include "hash_table.h"

hash_info_t stats[] = {
    {hash_fun_1, 0},
    {hash_fun_2, 0},
    {hash_fun_3, 0},
    {hash_fun_4, 0},
    {hash_fun_5, 0},
    {hash_fun_6, 0}
};

const uint32_t TABLE_SIZE = 4000;

static list_t* hash_table[TABLE_SIZE] = {};

static const uint32_t MAX_NAME_LEN = 100;

void hash_table_dump(const char* output_filename, uint32_t hash_number) {
    if (!output_filename) {
        fprintf(stderr,
            RED "No input filename for hashtable dump\n" RESET);
        return;
    }
    
    char html_filename[MAX_NAME_LEN] = {};
    snprintf(html_filename, MAX_NAME_LEN, 
            "%s.html", output_filename);
    FILE* html_out = fopen(html_filename, "w");

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
    // printf(GREEN "Dump complete. Created %u dump files\n" RESET, 
    //        bucket_counter);
}

void hash_table_dump_buckets(FILE* list_len_out, uint32_t hash_number) {
    fprintf(list_len_out, "Created %u buckets\n", 
            stats[hash_number].bucket_counter);
    for (uint32_t i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i]) {
            fprintf(list_len_out, "%u: %u buckets\n",
                    i, hash_table[i]->size);
        } else {
            fprintf(list_len_out, "%u: 0 buckets\n", i);
        }
    }
}

bool hash_table_search(elem_t elem, uint32_t hash_number) {
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

uint32_t hash_table_insert(elem_t elem, uint32_t hash_number) {
    int ind = stats[hash_number].func(elem);

    static uint32_t bucket_counter = 0;

    if (!hash_table[ind]) {
        hash_table[ind] = list_create();
        bucket_counter++;
    }

    elem_t* alloced_elem = (elem_t*)calloc(1, sizeof(elem_t));
    *alloced_elem = elem;
    list_push_front(hash_table[ind], alloced_elem);

    return bucket_counter;
}
