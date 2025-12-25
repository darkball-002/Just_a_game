#ifndef Value_function_FUNCTION

typedef char **pstring; 
typedef char *string;

void value_print_log_setup();

int value_file_read(pstring ptr, const char* filepath, int binary_mode);

int value_print_log(string formated);

int value_string_format(pstring ptr, const char* format, ...);

#endif
