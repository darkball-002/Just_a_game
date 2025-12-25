#include <complex.h>
#define Shader_CLASS

#include "core/value.h"

#define shader_vertex_file(name) "assets/shader/" #name ".vert"
#define shader_fragment_file(name) "assets/shader/" #name ".frag"

typedef struct Shader__ *Shader;

enum {
    VAO, VBO, EBO, ShaderProgram
};

int shader_create(Shader* shader, const char* vert, const char* frag);

int shader_setup_buffer(Shader shader);

void shader_setup_bind(Shader shader); 

void shader_unbind(Shader shader);
    
void shader_destroy(Shader shader);


float* shader_get_vertex_buffer(Shader shader);

unsigned int* shader_get_order_buffer(Shader shader); 

unsigned int* shader_get_vertex_count(Shader shader);

unsigned int* shader_get_order_count(Shader shader);

unsigned int shader_get_globj(Shader shader, unsigned int index); 


int shader_error_check(int errorcode);
