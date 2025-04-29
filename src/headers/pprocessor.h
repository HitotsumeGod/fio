#ifndef __PPROCESSOR_H__
#define __PPROCESSOR_H__

#include <stddef.h>

#define MALLOC_ERR -2
#define REALLOC_ERR -3
#define FOPEN_ERR -4
#define FCLOSE_ERR -5

typedef struct {
	size_t strsize;
	size_t nmallocd;
} amounts;

extern amounts *console_to_single_string(char *filename, char **ptr_to_strbuf);
extern amounts *console_to_strings(char *filename, char ***ptr_to_strbuf);
extern amounts *file_to_single_string(char *filename, char **ptr_to_strbuf);
extern amounts *file_to_strings(char *filename, char ***ptr_to_strbuf);

#endif //__PPROCESSOR_H__