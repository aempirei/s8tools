#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	char s[65536];
	char *p = s;
	int ch;
	while((ch = getchar()) != EOF && p != (s + sizeof(s)))
		*p++ = ch;
	while(p-- > s)
		putchar(*p);
	return 0;
}
