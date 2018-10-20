#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

int main(int argc, char **argv) {
	int ch;
	int rot;
	if(argc != 2) {
		fprintf(stderr, "%s failed\n", basename(argv[0]));
		exit(EXIT_FAILURE);
	}
	rot = atoi(argv[1]);
	while((ch = getchar()) != EOF)
		putchar(ch + rot);
	exit(EXIT_SUCCESS);
}
