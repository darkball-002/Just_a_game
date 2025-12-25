#include <stdio.h>
#include <stdarg.h>

#include "core/value.h"
#include "core/extra.h"
#include "core/heap.h"
#include "core/function.h"


int value_string_format(pstring ptr, const char* format, ...) {	
	if (ptr && format) {} else return Value_Error_Human;
 
	va_list forSize, toReturn;
	size_t size;
	int errorcode;

	va_start(forSize, format);
	va_copy(toReturn, forSize);

	size = vsnprintf(null, 0, format, forSize) + 1;

	value_if (value_heap_calloc(ptr, sizeof(char), size)) {
		vsnprintf(*ptr, size, format, toReturn);
	}

	va_end(forSize);
	va_end(toReturn);

	return errorcode;
}


