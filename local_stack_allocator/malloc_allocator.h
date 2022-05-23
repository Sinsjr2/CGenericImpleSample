#pragma once

#include <stdlib.h>

#define IL2C_LOCAL_ALLOCATOR_INIT(varName) \
    IL2C_LinkedAllocator varName = { NULL };
#define IL2C_LOCAL_ALLOC(allocator, varName, size) \
    il2c_local_alloc(&allocator, size)
#define IL2C_LOCAL_ALLOCATOR_FREE(allocator) \
    il2c_local_free(&allocator);

typedef struct {
    HeapBufferItem *pNext;
    /* allocated memory */
    uint8_t buf[1];
} IL2C_HeapBufferItem;

typedef struct {
    /* last allocated memory. */
    HeapBufferItem *latest;
} IL2C_LinkedAllocator;

inline void* il2c_local_alloc(IL2C_LinkedAllocator *allocator, size_t size, size_t alignment) {
    IL2C_HeapBufferItem *item =
        (IL2C_HeapBufferItem*)il2c_malloc(sizeof(IL2C_HeapBufferItem) - sizeof(uint8_t) + il2c_adjustAlignment(&IL2C_HeapBufferItem.buf, alignment));
    item->pNext = allocator->latest;
    allocator->latest = item;
    return il2c_adjustAlignment(&(item->buf[0]), alignment);
}

/* this is thread safe. */
inline void il2c_register_allocated_heap(volatile IL2C_LinkedAllocator *allocator, volatile void* pTarget) {
    do
    {
        IL2C_HeapBufferItem* pNext = allocator->latest;
        pTarget->pNext__ = pNext;
    } while(il2c_likely__(il2c_icmpxchgptr(&allocator->latest, pTarget, pNext) != pNext));
}

inline void il2c_local_free(IL2C_LinkedAllocator *allocator) {
    IL2C_HeapBufferItem *item = allocator->latest;
    while (il2c_likely__(item != NULL)) {
        IL2C_HeapBufferItem *pNext = item->pNext;
        il2c_free(item);
        item = pNext;
    }
}

/* this is thread safe */
inline void il2c_linked_free(volatile IL2C_LinkedAllocator *allocator)
{
    while (1)
    {
        IL2C_HeapBufferItem* pNext = allocator->latest;
        if (pNext == NULL)
        {
            break;
        }
        if (il2c_unlikely__(il2c_icmpxchgptr(&allocator.latest, pNext, allocator.latest) != allocator.latest))
        {
            continue;
        }
        il2c_free(pNext);
    }
}
