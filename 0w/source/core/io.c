#include <stdalign.h>
#include <stdarg.h>
#include <stdio.h>

#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"
#include "core/function.h"
#include "core/io.h"

enum {
    Param_1,
    Fopen, Fseek, Ftell,
    Buffer, Content
};

static void value_failed(FILE* ptr, const char* comefrom, int why) {
    char* formated;

    if (ptr) fclose(ptr);

    switch(why) {
        case Param_1: {
            value_string_format(&formated, "[%s] param[1] is not vaild", comefrom);
        } break;

        case Fopen: {
            value_string_format(&formated, "[%s] cannot open the file, did it exist?", comefrom);
        } break;
        
        case Fseek: {
            value_string_format(&formated, "[%s] cannot get end of the file", comefrom);
        } break;

        case Ftell: {
            value_string_format(&formated, "[%s] cannot get size of the file", comefrom);
        } break;

        case Buffer: {
            value_string_format(&formated, "[%s] cannot make buffer for file contents", comefrom);          
        } break;

        case Content: {
            value_string_format(&formated, "[%s] cannot get content of the file", comefrom);          
        } break;
    }

    value_print_log(formated);
}

int value_file_read(pstring ptr, const char* filepath, int binary_mode) {
	if (filepath) { } else {
        value_failed(null, "value_file_read", Param_1); 

        return Value_Error_Human;
    }

	FILE* input = fopen(filepath, binary_mode ? "rb" : "r");
	string content;
	long size;
	int errorcode;
	
	if (input) { } else { 
        value_failed(input, "value_file_read", Fopen);

        return Value_Error_IO;
    }
	
	value_if (fseek(input, 0, SEEK_END)) { } else {
        value_failed(input, "value_file_read", Fseek);

        return Value_Error_IO;
    }

	if ((size = ftell(input)) > 0) { rewind(input); } else {
        value_failed(input, "value_file_read", Ftell);

        return Value_Error_IO;
    }
	
	if (value_error_state(errorcode, value_heap_calloc(&content, sizeof(char), size + 1))) { } else {
        value_failed(input, "value_file_read", Buffer);

        return Value_Error_IO;
    }

	if (fread(content, sizeof(char), size, input) == size) { } else {
		value_heap_release(content);
        value_failed(input, "value_file_read", Content);	

        return Value_Error_IO;
	}

	*ptr = content;
	
    fclose(input);
    return Value_Error_Fine;
}

