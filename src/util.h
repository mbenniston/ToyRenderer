#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct array_list {
    void* array;
    size_t size; //number of elements that can be held
    size_t elementSize; //the size in bytes per element
    size_t currentItem; //index of, starts at zero
};

void array_list_Init(size_t elementSize, size_t initialElements, struct array_list* list);
void array_list_Push(struct array_list * const list, const void* const item);
// void array_list_Pop(struct array_list * const list, void* const item);
void array_list_Free(struct array_list* const list);

inline bool array_list_Empty(struct array_list* const list) { 
    return list->size == 0; 
}

#endif