#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pprocessor.h"

int main(int argc, char *argv[]) {

	amounts *a;
	char **strs;

	if (!(a = file_to_strings(argv[1], &strs))) {
		fprintf(stderr, "file_to_strings error : %d", errno);
		return EXIT_FAILURE;
	}
	for (int i = 0; i < a -> strsize; i++) 
		printf("%s\n", *(strs + i));
	for (int i = 0; i < a -> nmallocd; i++)
		free(*(strs + i));
	free(a);
	free(strs);
	return 0;

}