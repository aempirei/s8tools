#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int ch;
	for(int k = 1; k < argc; k++)
		putchar(atoi(argv[k]));
	while((ch = getchar()) != EOF)
		putchar(ch);
	exit(EXIT_SUCCESS);
}
