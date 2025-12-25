#include <glad\glad.h>


#include "client/core/shader.h"

#include "core/function.h"
#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"
#include "core/io.h"

enum {
    Shader_Broken_VBO, Shader_Broken_EBO, Shader_Broken_WindowCloesed,

    Shader_FileIsNotFound = 1, Shader_BufferIsNotValid
};

struct Shader__ {
	unsigned int Program;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	float* vertex_buffer;
	unsigned int* order_buffer;
	
	unsigned int vertex_count;
	unsigned int order_count; // length of EBO.
};


static int shader_resources(GLuint* program, const char* vert, const char* frag) {
	string fragmentSource, vertexSource;
	
	value_if (value_file_read(&vertexSource, vert, true)) { } else return false;
    value_if (value_file_read(&fragmentSource, frag, true)) {} else return false;

	GLuint vertex, fragment;	

	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	*program = glCreateProgram();

	
	glShaderSource(vertex, 1, &vertexSource, null);
	glCompileShader(vertex);

	glShaderSource(fragment, 1, &fragmentSource, null);	
	glCompileShader(fragment);
	
	
	glAttachShader(*program, vertex);
	glAttachShader(*program, fragment);
	glLinkProgram(*program);
		
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	value_heap_release(vertexSource);
	value_heap_release(fragmentSource);

	return true;
}


static void shader_broken(Shader shader, int level) {
    string formated;

    if (level > Shader_Broken_EBO) value_heap_release(shader->order_buffer);

    if (level > Shader_Broken_VBO) value_heap_release(shader->vertex_buffer);

	value_string_format(&formated, "shader was destroy with level %d", level);
    value_print_log(formated);
    value_heap_release(formated);
	
    value_heap_release(shader);
}

int shader_create(Shader* turnback, const char* vert, const char* frag) {
	Shader shader;
	int errorcode;

	if (value_error_state(errorcode, value_heap_calloc(&shader, sizeof(struct Shader__), 1))) {
        
    } else return errorcode;
	

	if (shader_resources(&shader->Program, vert, frag)) { } else return Shader_FileIsNotFound;

    *turnback = shader;

	return Value_Error_Fine;
}

int shader_setup_buffer(Shader shader) {
    value_if (value_heap_calloc(&shader->vertex_buffer, sizeof(float), shader->vertex_count)) {} else {
        shader_broken(shader, Shader_Broken_VBO);
        return Shader_BufferIsNotValid;
    }

    value_if (value_heap_calloc(&shader->order_buffer, sizeof(unsigned int), shader->order_count)) {} else {
        shader_broken(shader, Shader_Broken_EBO);
        return Shader_BufferIsNotValid;
    }

    return Value_Error_Fine;
}

void shader_setup_bind(Shader shader) {
	glGenVertexArrays(1, &shader->VAO);
	glGenBuffers(1, &shader->VBO);
	glGenBuffers(1, &shader->EBO);

	glBindVertexArray(shader->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, shader->VBO);
	glBufferData(GL_ARRAY_BUFFER, shader->vertex_count * sizeof(float), shader->vertex_buffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shader->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shader->order_count * sizeof(unsigned int), shader->order_buffer, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), null);
	glEnableVertexAttribArray(0);
		
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void shader_unbind(Shader shader) {
    glDeleteVertexArrays(1, &shader->VAO);
	glDeleteBuffers(1, &shader->VBO);
	glDeleteBuffers(1, &shader->EBO);

	glDeleteProgram(shader->Program);
}

void shader_destroy(Shader shader) {
    shader_broken(shader, Shader_Broken_WindowCloesed);
}

float* shader_get_vertex_buffer(Shader shader) {
    return shader->vertex_buffer;
}

unsigned int* shader_get_order_buffer(Shader shader) {
    return shader->order_buffer;
}

unsigned int* shader_get_vertex_count(Shader shader) {
    return &shader->vertex_count;
}

unsigned int* shader_get_order_count(Shader shader) {
    return &shader->order_count;
}

unsigned int shader_get_globj(Shader shader, unsigned int index) {
    switch(index) {
        case 1: return shader->VBO;
        case 2: return shader->EBO;
        case 3: return shader->Program;
        default: return shader->VAO;
    }
}



int shader_error_check(int errorcode) {
	switch (errorcode) {
		case Shader_BufferIsNotValid: {
			value_print_log("shader: buffer is not valid");
		} return Value_Error_Memory;

		case Shader_FileIsNotFound: {
			value_print_log("shader: shader source file is not found");
		} return Value_Error_IO;
			
	
		default: return Value_Error_Fine;
	}
}
