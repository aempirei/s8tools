#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <s8.h>
#include <s8-basic-function.h>
#ifdef CMP
int main(int argc, char **argv) {
	const char x = argc == 2 ? ordinal(argv[1]) : 0;
	int ch;
	while((ch = getchar()) != EOF)
		putchar(CMP((char)ch, x));
	exit(EXIT_SUCCESS);
}
#else
#error "CMP macro must be defined and have type <binary_relation_t *>"
#endif
