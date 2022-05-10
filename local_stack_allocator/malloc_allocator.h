#pragma once

#include <stdlib.h>

#define IL2C_LOCAL_ALLOCATOR_INIT(varName) \
    IL2C_LinkedAllocator varName = { NULL };
#define IL2C_LOCAL_ALLOC(allocator, varName, size) \
    il2c_local_alloc(&allocator, size)
#define IL2C_LOCAL_ALLOCATOR_FREE(allocator) \
    il2c_local_free(&allocator);

typedef struct {
    HeapBufferItem *prev;
    /* allocated memory */
    char buf[];
} IL2C_HeapBufferItem;

typedef struct {
    /* last allocated memory. */
    HeapBufferItem *latest;
} IL2C_LinkedAllocator;

inline void* il2c_local_alloc(IL2C_LinkedAllocator *allocator, size_t size) {
    IL2C_HeapBufferItem *item =
        (IL2C_HeapBufferItem*)malloc(sizeof(IL2C_HeapBufferItem) + size);
    item->prev = allocator->latest;
    allocator->latest = item;
    return &(item->buf[0]);
}

inline void il2c_local_free(IL2C_LinkedAllocator *allocator) {
    IL2C_HeapBufferItem *item = allocator->latest;
    while (item != NULL) {
        IL2C_HeapBufferItem *prev = item->prev;
        free(item);
        item = prev;
    }
}
