#define Value_Print_FUNCTION

#include <stdio.h>

#include "core/value.h"
#include "core/function.h"

void value_print_log_setup() {
    remove("log/previous.log");

    rename("log/latest.log", "log/previous.log");
}

int value_print_log(const string text) {	
	FILE* log_file; 

    log_file = fopen("log/latest.log", "a");

	if (log_file) { } else {
		return Value_Error_IO;
	} 

	fprintf(log_file, "%s \n", text);
    fclose(log_file);

	return Value_Error_Fine;
}
