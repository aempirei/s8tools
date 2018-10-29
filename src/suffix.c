#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int ch;
	while((ch = getchar()) != EOF)
		putchar(ch);
	for(int k = 1; k < argc; k++)
		putchar((char)atoi(argv[k]));
	exit(EXIT_SUCCESS);
}
