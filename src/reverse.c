#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	const size_t sz = 1 << 20;
	char *s, *p;
	int ch;
	if((s = p = malloc(sz)) == NULL) {
		perror("malloc()");
		return -1;
	}
	while((ch = getchar()) != EOF && p < s + sz)
		*p++ = ch;
	while(p-- > s)
		putchar(*p);
	free(s);
	return 0;
}
