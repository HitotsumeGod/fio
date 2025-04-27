#include <stdio.h>

int main(void) {

	FILE *f = fopen("zero", "w");
	for (long l = 0L; l < 100000000L; l++)
		fputc('0', f);
	return fclose(f);

}
