#include <glad/glad.h>

#include "server/object/block.h"

#include "core/value.h"
#include "core/extra.h"

/** 
 * WARNING: need 24 memory space of `float` in your `vertices buffer` and 36 memory space of `unsigned int`(just sizeof(int)) in your `indices buffer`
 * @param vertices `vertice buffer`
 * @param indices the object start position in `indices buffer`
 * @param vertices_index the index of the object indices start position in `vertice buffer`
 * @param xyz block position
*/
void block_create(
    Block* block, float* pVtx, unsigned int* pIdx, unsigned int vertex_index, double x, double y, double z, 
    double west, double east, double south, double north, double up, double down
) {
    unsigned int i[8] = { 0 };

    west = x + west, east = x - east, south = z + south, north = z - north, up = y + up, down = y - down;
    
    block->vertices = &pVtx[0];
    block->indices = &pIdx[0];

    for (char j = 0; j < 8; ++j) i[j] = (vertex_index + j);

    value_triple_set(float, &block->vertices[0 ], west, down, south);
    value_triple_set(float, &block->vertices[3 ], west, up  , south);
    value_triple_set(float, &block->vertices[6 ], east, down, south);
    value_triple_set(float, &block->vertices[9 ], east, up  , south);
    value_triple_set(float, &block->vertices[12], west, down, north);
    value_triple_set(float, &block->vertices[15], west, up  , north);
    value_triple_set(float, &block->vertices[18], east, down, north);
    value_triple_set(float, &block->vertices[21], east, up  , north);

    // south face have(0, 1, 2, 3)
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[0 ], i, 0, 1, 2);
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[3 ], i, 2, 1, 3);

    // north face have(4, 5, 6, 7)
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[6 ], i, 7, 5, 6);
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[9 ], i, 6, 5, 4);


    // west face have(0, 1, 4, 5)
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[12], i, 1, 0, 5);
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[15], i, 5, 0, 4);

    // east face have(2, 3, 6, 7)
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[18], i, 2, 3, 6);
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[21], i, 6, 3, 7);

    
    // upper face have(1, 3, 5, 7)
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[24], i, 1, 5, 3);
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[27], i, 3, 5, 7);

    // lower face have(0, 2, 4, 6)
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[30], i, 2, 6, 0);
    value_triple_set_ary(unsigned int, unsigned int, &block->indices[33], i, 0, 6, 4);
}


/** 
 * WARNING: it's add not set.
*/
void block_bufferSizeNeed(unsigned int* dest_vertices, unsigned int* dest_indices, unsigned int block_count) {
    *dest_vertices += Block_Vertices * block_count;
    *dest_indices +=  Block_Indices * block_count;
}

unsigned int block_getSize(int isIndices, unsigned int block_count) {
    return isIndices ? Block_Indices * block_count : Block_Vertices * block_count;
}
