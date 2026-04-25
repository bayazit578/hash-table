#include <cstdlib>
#include <stdio.h>
#include <stdint.h>

#include "list.h"
#include "hash_table.h"

int main() {
    hash_table_insert({"gay", 3});
    hash_table_dump("hash_table");
    return EXIT_SUCCESS;
}
