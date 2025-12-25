#include <stdlib.h>

#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"

int value_heap_calloc(pHeap_t ptr, unsigned int sizeOfElementType, unsigned int elementCount) {
    if (ptr) {} else return Value_Error_Human;

    value_as_rp(heap_t, ptr) = calloc(elementCount, sizeOfElementType);
    
    if (value_as_rp(heap_t, ptr)) {} else return Value_Error_Memory;

    return Value_Error_Fine;
}
 
// Warning this will free the memory of 'ptr'.
int value_heap_redirect(pHeap_t ptr, ptr_t redirectTo) {
    if (ptr && value_as_rp(heap_t, ptr)) {} else return Value_Error_Memory;

    free(value_as_rp(heap_t, ptr));

    value_as_rp(heap_t, ptr) = redirectTo;

    return Value_Error_Fine;
}

int value_heap_release(heap_t restrict ptr) {
    if (ptr) {} else return Value_Error_Memory;

    free(ptr);

    return Value_Error_Fine;
}
