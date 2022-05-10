#pragma once

#define IL2C_LOCAL_ALLOCATOR_INIT(varName) \
    LocalMemoryPool varName = il2c_getLocalMemoryPool();
#define IL2C_LOCAL_ALLOC(allocator, size) \
    il2c_local_alloc(&allocator, size)
#define IL2C_LOCAL_ALLOCATOR_FREE(allocator) \
    il2c_local_free(&allocator);

typedef struct {
    /* current memory usage */
    int current_pos;
    void *buf;
} LocalMemoryPool;

typedef struct {
    /* buffer index in startint to use local memory. */
    int begin;
    LocalMemoryPool* pool;
} LocalHeapAllocator;

/* get pool from current thread/task. */
LocalMemoryPool* il2c_getLocalMemoryPool();

inline LocalHeapAllocator il2c_local_heap_allocator_init() {
    LocalMemoryPool* pool = il2c_getLocalMemoryPool();
    return { pool->current_pos, pool };
}

/* return allignmented pointer. */
inline void* il2c_local_alloc(LocalHeapAllocator* allocator, size_t size) {
    LocalMemoryPool* pool = allocator->pool;
    const int align_mask = 2 * sizeof(size_t) - 1;
    size_t alloc_size = (size + sizeof(size_t) + align_mask) & ~align_mask;
    size_t begin_pos = (pool->current_pos + 1) & ~align_mask;
    pool->current_pos = begin_pos + alloc_size;
    return ((char*)pool->buf)[begin_pos];
}

inline void il2c_local_free(LocalHeapAllocator* allocator) {
    allocator->pool->current_pos = allocator->begin;
}
