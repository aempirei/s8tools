#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <s8-basic-function.h>
int main(int argc, char **argv) {
	const int x = argc == 2 ? ordinal(argv[1]) : 0;
	int ch;
	while((ch = getchar()) != EOF)
		putchar(binary_add(ch,x));
	exit(EXIT_SUCCESS);
}
