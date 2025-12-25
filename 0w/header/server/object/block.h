#if defined __glad_h_

#define Block_CLASS

#include "core/value.h"

typedef struct Block__ {
    float* vertices;
    unsigned int* indices;
} Block;

enum {
    Block_Vertices = 24, Block_Indices = 36
};

void block_create(
    Block* block, float* vertices_ary, unsigned int* indices_ary, unsigned int vertices_index, double x, double y, double z, 
    double west, double east, double south, double north, double up, double down
);

void block_bufferSizeNeed(unsigned int* dest_vertices, unsigned int* dest_indices, unsigned int block_count);

unsigned int block_getSize(int isIndices, unsigned int block_count);

#endif
