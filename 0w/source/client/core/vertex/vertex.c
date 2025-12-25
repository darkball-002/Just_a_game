#include "client/core/vertex/vertex.h"

#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"

typedef struct Vertex__ *Vertex;

struct Vertex__ {
    float* vertices;
    unsigned int* indices;
    unsigned int* vertex_index;
    unsigned int vertex_unused;
};

int vertex_create(Vertex* turnback, float* vertices_buffer, unsigned int* indices_buffer, unsigned int vertex_count) {
    Vertex vertex;
    int errorcode;


    if (value_error_state(errorcode, value_heap_calloc(&vertex, sizeof(struct Vertex__), 1))) {
        vertex->vertices = vertices_buffer;
        vertex->indices = indices_buffer;
    } else return errorcode;
    

    if (value_error_state(errorcode, value_heap_calloc(&vertex->vertex_index, sizeof(unsigned int), vertex_count))) {
        vertex->vertex_unused = vertex_count;

        for (int i = 0; i < vertex_count; ++i) {
            vertex->vertex_index[i] = vertex_count + i;
        }
    } else {
        value_heap_redirect(&vertex, null);

        return errorcode;
    }

    *turnback = vertex;

    return errorcode;
}

// 0, 1, 2, 2, 1, 3
void vertex_combine_square(Vertex vertex, offset_t indeices_begin, offset_t vert_0, offset_t vert_1, offset_t vert_2, offset_t vert_3) {
    value_triple_set_ary(unsigned int, unsigned int, &vertex->indices[indeices_begin + vertex_buffer_size_index(0)], vertex->vertex_index, vert_0, vert_1, vert_2);
    value_triple_set_ary(unsigned int, unsigned int, &vertex->indices[indeices_begin + vertex_buffer_size_index(1)], vertex->vertex_index, vert_2, vert_1, vert_3);
}

int vertex_create_square(Vertex vertex, offset_t vertices_begin, double x, double y, double z, double west, double east, double up, double down) {
    if (vertex->vertex_unused < 4) return false;
    
    west = x + west, east = x - east, up = y + up, down = y - down;

    value_triple_set(float, &vertex->vertices[vertices_begin + vertex_buffer_size_vertex(0)], west, down, z);
    value_triple_set(float, &vertex->vertices[vertices_begin + vertex_buffer_size_vertex(1)], west, up  , z);
    value_triple_set(float, &vertex->vertices[vertices_begin + vertex_buffer_size_vertex(2)], east, down, z);
    value_triple_set(float, &vertex->vertices[vertices_begin + vertex_buffer_size_vertex(3)], east, up  , z);
}





void vertex_destroy(Vertex* vertex) {
    if (vertex && *vertex) {
        value_heap_redirect(&(*vertex)->vertex_index, null);
        value_heap_redirect(vertex, null);
    }
}
