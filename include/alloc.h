// allocator

#pragma once

#include "vtable/alloc.h"

typedef struct Allocator {
    void* ctx;
    const AllocatorVTable* vtable;
} Allocator;

Allocator* allocator_system();

static inline void* alloc_alloc(Allocator* a, Size size) {
    return a->vtable->alloc(a->ctx, size);
}

static inline void* alloc_realloc(Allocator* a, void* ptr, Size new_size) {
    if (a->vtable->realloc) {
        return a->vtable->realloc(a->ctx, ptr, new_size);
    } else {
        return NULL;
    }
}

static inline void alloc_free(Allocator* a, void* ptr) {
    a->vtable->free(a->ctx, ptr);
}

static inline void alloc_reset(Allocator* a) {
    if (a->vtable->reset) { a->vtable->reset(a->ctx); }
}

static inline void alloc_destroy(Allocator* a) {
    if (a->vtable->destroy) { a->vtable->destroy(a->ctx); }
}
