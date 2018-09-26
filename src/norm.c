#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FATALF(...) { fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE); }
#define FATAL(x) { perror(x); exit(EXIT_FAILURE); }

int main(int argc, char **argv) {

	struct stat s1;
	struct stat s2;

	FILE *f1;
	FILE *f2;

	int c1;
	int c2;

	long sum1 = 0;
	long sum2 = 0;

	long sum12 = 0;

	double x = 0;

	if(argc != 3)
		FATALF("\nusage: %s file1 file2\n\n", *argv);

	if((f1 = fopen(argv[1], "r")) == NULL)
		FATAL("failed to open file1");

	if((f2 = fopen(argv[2], "r")) == NULL)
		FATAL("failed to open file2");

	if(fstat(fileno(f1), &s1) == -1)
		FATAL("failed to stat file1");

	if(fstat(fileno(f2), &s2) == -1)
		FATAL("failed to stat file2");

	if(s1.st_size != s2.st_size)
		FATALF("error: inputs of unequal size\n");

	while(--s1.st_size && --s2.st_size) {

		c1 = (char)fgetc(f1);
		c2 = (char)fgetc(f2);

		sum12 += c1 * c2;
		sum1 += c1 * c1;
		sum2 += c2 * c2;
	}

	x = sum12 / (sqrt(sum1) * sqrt(sum2));

	printf("%f\n", x);

	return 0;
}
