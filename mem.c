#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

        FILE *f;
        char **strs, **fdummy, *dummy;
        int c, n, m, b, d;

        b = 0;
        m = d = 2;
        if ((strs = malloc(sizeof(char *) * d)) == NULL) {
                perror("malloc err");
                return EXIT_FAILURE;
        }
	printf("\nInitial toplevel array malloc is %zu bytes.\n", sizeof(char *) * d);
        for (int i = 0; i < d; i++) 
                if ((*(strs + i) = malloc(sizeof(char) * m)) == NULL) {
                        perror("malloc err");
                        return EXIT_FAILURE;
                }
	printf("\n%d lower arrays are each malloc'd %zu bytes.\n", d, sizeof(char) * m);
        if ((f = fopen(argv[1], "r")) == NULL) {
                perror("fopen err");
                return EXIT_FAILURE;
        }
        while ((c = fgetc(f)) != EOF) {
		printf("\nTLoop iteration %d.\n", b + 1);
                n = 0;
		m = 2;
                ungetc(c, f);
                if (b == d) {
                        if ((fdummy = realloc(strs, sizeof(char *) * (d *= 2))) == NULL) {
                                perror("realloc err");
                                return EXIT_FAILURE;
                        }
                        strs = fdummy;
			printf("\nTL reallocates to %zu bytes.\n", sizeof(char *) * d);
                }
                while ((c = fgetc(f)) != EOF && c != '\n') {
			printf("\nLLoop iteration %d.\n", n + 1);
                        if (n == m) {
                                if ((dummy = realloc(*(strs + b), sizeof(char) * (m *= 2))) == NULL) {
                                        perror("realloc err");
                                        return EXIT_FAILURE;
                                }
                                *(strs + b) = dummy;
                        	printf("\nLL %d reallocates to %zu bytes.\n", b, sizeof(char) * m);
			}
			printf("\nCharacter is placed into LL %d at position %d.\n", b, n);
                        *(*(strs + b) + (n++)) = c;
                }
                if (n == m) {
                        if ((dummy = realloc(*(strs + b), sizeof(char) * m + 1)) == NULL) {
                                perror("realloc err");
                                return EXIT_FAILURE;
                        }
			printf("\nLL %d reallocates to %zu bytes outside of mini loop.\n", b, sizeof(char) * m + 1);
                        *(strs + b) = dummy;
                }
		printf("\nNull byte is placed into LL %d at position %d.\n", b, n);
                *(*(strs + (b++)) + n) = '\0';
        }
	printf("\n\n");
        for (int i = 0; i < b; i++) 
                printf("%s\n", *(strs + i));
        for (int i = 0; i < d; i++)
   		free(*(strs + i));
        free(strs);
        return 0;

}
