

#include "core/value.h"

// the memory offset of the array, use on ary[memory_offset];
typedef unsigned int offset_t;

/** 
 * WARNING: it's add not set.
*/
HeaderFunction void vertex_buffer_size_all(unsigned int* dest_vertices, unsigned int* dest_indices, unsigned int count) {
    *dest_vertices += 3 * count;
    *dest_indices += count;
}

HeaderFunction unsigned int vertex_buffer_size_index(unsigned int count) {
    return count;
}

HeaderFunction unsigned int vertex_buffer_size_vertex(unsigned int count) {
    return count * 3;
}