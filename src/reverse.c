#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	char *s, *p;
	int ch;
	if((s = p = malloc(1 << 20)) == NULL) {
		perror("malloc()");
		return -1;
	}
	while((ch = getchar()) != EOF && p != (s + sizeof(s)))
		*p++ = ch;
	while(p-- > s)
		putchar(*p);
	return 0;
}
