#pragma once

#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include "color.h"

typedef struct {
            void*    value;
            uint32_t next ;
            uint32_t prev ;
            } node_t;

typedef struct {
            int      free;
            node_t*  contents;
            uint32_t size;
            uint32_t capacity;
            } list_t;

list_t* list_create();
void list_destroy(list_t* cnucok);
void list_insert_after(list_t* cnucok, uint32_t ind, 
                       void* value);
void* list_erase(list_t* cnucok, uint32_t ind);
void list_push_front(list_t* cnucok, void* value);
void list_push_back(list_t* cnucok, void* value);
void* list_pop_front(list_t* cnucok);
void* list_pop_back(list_t* cnucok);
void get_free(list_t* cnucok);
void list_dump(list_t* cnucok, const char* filename,
               uint32_t* file_number);
