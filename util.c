#include "util.h"

void array_list_Init(size_t elementSize, size_t initialElements, struct array_list* list)
{
    if(initialElements > 0) 
        list->array = malloc(elementSize * initialElements);
    
    list->size = initialElements;
    list->elementSize = elementSize;
    list->currentItem = 0;
}

void array_list_Push(struct array_list * const list, const void* const item)
{
    if(list->currentItem >= list->size) {
        list->size++;

        if(list->size == 1) {
            list->array = malloc(list->elementSize * list->size);
        } else {
            list->array = realloc(list->array, list->elementSize * list->size);
        }
    }

    memcpy(list->array + (list->elementSize * list->currentItem), item, list->elementSize);
    list->currentItem++;
}

void array_list_Free(struct array_list* const list)
{
    free(list->array);
    list->size = 0;
    list->currentItem = 0;
}