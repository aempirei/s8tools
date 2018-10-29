#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int ch;
	for(int k = 1; k < argc; k++)
		putchar((char)atoi(argv[k]));
	while((ch = getchar()) != EOF)
		putchar(ch);
	exit(EXIT_SUCCESS);
}
