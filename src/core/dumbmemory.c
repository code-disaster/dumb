#include <stdlib.h>

#include "dumb.h"

static DUMBMEMORY_SYSTEM the_dms = {
    malloc, calloc, realloc, free
};

void register_dumbmemory_system(const DUMBMEMORY_SYSTEM *dms) {
    the_dms.malloc = (dms && dms->malloc) ? dms->malloc : malloc;
    the_dms.calloc = (dms && dms->calloc) ? dms->calloc : calloc;
    the_dms.realloc = (dms && dms->realloc) ? dms->realloc : realloc;
    the_dms.free = (dms && dms->free) ? dms->free : free;
}

void* dumb_malloc(size_t size) {
    return the_dms.malloc(size);
}

void *dumb_calloc(size_t num, size_t size) {
    return the_dms.calloc(num, size);
}

void *dumb_realloc(void *ptr, size_t size) {
    return the_dms.realloc(ptr, size);
}

void dumb_free(void *ptr) {
    the_dms.free(ptr);
}
