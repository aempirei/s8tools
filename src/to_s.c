#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <s8.h>
int main(int argc, char **argv) {
	const char *fmt = argc > 1 ? argv[1] : "s";
	const char *p = fmt;
	int ch;

	for(const char *q = fmt; *q; q++) {
		if(strchr("su+", *q) == NULL) {
			fprintf(stderr, "unexpected character '%c' in format string \"%s\"\n", *q, fmt);
			exit(EXIT_FAILURE);
		}
	}

	while((ch = getchar()) != EOF) {
		if(*p == '+')
			printf("%c", (char)ch < 0 ? '-' : (char)ch > 0 ? '+' : '0');
		else
			printf("%d", *p == 's' ? (char)ch : ch);
		putchar(*++p ? ' ' : '\n');
		if(*p == '\0')
			p = fmt;
	}
	return 0;
}
