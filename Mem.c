#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	
	FILE *f;
	char *fbuf;
	int c;
	long fsize, n;

	if ((f = fopen(argv[1], "r")) == NULL) {
		perror("fopen err");
		return EXIT_FAILURE;
	}
	if (fseek(f, 0, SEEK_END) == -1) {
		perror("fseek err");
		return EXIT_FAILURE;
	}
	if ((fsize = ftell(f)) == -1) {
		perror("ftell err");
		return EXIT_FAILURE;
	}
	rewind(f);
	if ((fbuf = malloc(sizeof(char) * fsize)) == NULL) {
		perror("malloc err");
		return EXIT_FAILURE;
	}
	n = 0L;
	while ((c = fgetc(f)) != EOF) 
		*(fbuf + (n++)) = c;
	if (fclose(f) == -1) {
		perror("fclose err");
		exit(EXIT_FAILURE);
	}	
	for (int i = 0; i < n; i++)
		printf("%c", *(fbuf + i));
	free(fbuf);
	return 0;	

}
