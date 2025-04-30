#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pprocessor.h"

amounts *file_to_single_string(char *fname, char **buf) {

        amounts *a;
        FILE *f;
        char *str, *dummy;
        int c, n, m;

        n = 0;
        m = 2;
        str = *buf;
        if ((str = malloc(sizeof(char) * m)) == NULL || (a = malloc(sizeof(amounts))) == NULL) {
                errno = MALLOC_ERR;
                return NULL;
        }
        if ((f = fopen(fname, "r")) == NULL) {
                errno = FOPEN_ERR;
                return NULL;
        }
        while ((c = fgetc(f)) != EOF) {
                if (n == m) {
                        if ((dummy = realloc(str, sizeof(char) * (m *= 2))) == NULL) {
                                errno = REALLOC_ERR;
                                return NULL;
                        }
                        str = dummy;
                }
                *(str + (n++)) = c;
        }
        if (n == m++) {
                if ((dummy = realloc(str, sizeof(char) * m)) == NULL) {
                        errno = REALLOC_ERR;
                        return NULL;
                }
                str = dummy;
        }
        if (fclose(f) == -1) {
                errno = FCLOSE_ERR;
                return NULL;
        }
        *(str + (n--)) = '\0';
        *buf = str;
        a -> strsize = n;
        a -> nmallocd = m;
        return a;

}

amounts *file_to_strings(char *fname, char ***buf) {

        amounts *a;
        FILE *f;
        char **strs, **fdummy, *dummy;
        int c, n, m, b, d;

        b = 0;
        m = d = 2;
        strs = *buf;
        if ((strs = malloc(sizeof(char *) * d)) == NULL || (a = malloc(sizeof(amounts))) == NULL) {
                errno = MALLOC_ERR;
                return NULL;
        }
	//printf("\nInitial toplevel array malloc is %zu bytes.\n", sizeof(char *) * d);
        for (int i = 0; i < d; i++) 
                if ((*(strs + i) = malloc(sizeof(char) * m)) == NULL) {
                        errno = MALLOC_ERR;
                        return NULL;
                }
	//printf("\n%d lower arrays are each malloc'd %zu bytes.\n", d, sizeof(char) * m);
        if ((f = fopen(fname, "r")) == NULL) { 
                errno = FOPEN_ERR;
                return NULL;
        }
        while ((c = fgetc(f)) != EOF) {
		//printf("\nTLoop iteration %d.\n", b + 1);
                n = 0;
		m = 2;
                ungetc(c, f);
                if (b == d) {
                        if ((fdummy = realloc(strs, sizeof(char *) * (d *= 2))) == NULL) {
                                errno = REALLOC_ERR;
                                return NULL;
                        }
                        strs = fdummy;
                        for (int i = d / 2; i < d; i++)
                                if ((*(strs + i) = malloc(sizeof(char) * m)) == NULL) {
                                        errno = MALLOC_ERR;
                                        return NULL;
                                }
			//printf("\nTL reallocates to %zu bytes.\n", sizeof(char *) * d);
                }
                while ((c = fgetc(f)) != EOF && c != '\n') {
			//printf("\nLLoop iteration %d.\n", n + 1);
                        if (n == m) {
                                if ((dummy = realloc(*(strs + b), sizeof(char) * (m *= 2))) == NULL) {
                                        errno = REALLOC_ERR;
                                        return NULL;
                                }
                                *(strs + b) = dummy;
                        	//printf("\nLL %d reallocates to %zu bytes.\n", b, sizeof(char) * m);
			}
			//printf("\nCharacter is placed into LL %d at position %d.\n", b, n);
                        *(*(strs + b) + (n++)) = c;
                }
                if (n == m++) {
                        if ((dummy = realloc(*(strs + b), sizeof(char) * m)) == NULL) {
                                errno = REALLOC_ERR;
                                return NULL;
                        }
			//printf("\nLL %d reallocates to %zu bytes outside of mini loop.\n", b, sizeof(char) * m + 1);
                        *(strs + b) = dummy;
                }
		//printf("\nNull byte is placed into LL %d at position %d.\n", b, n);
                *(*(strs + (b++)) + n) = '\0';
        }
        if (fclose(f) == -1) {
                errno = FCLOSE_ERR;
                return NULL;
        }
        *buf = strs;
        a -> strsize = b;
        a -> nmallocd = d;
        return a;

}
