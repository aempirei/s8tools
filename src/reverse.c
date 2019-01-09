#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	size_t sz = 1 << 16;
	size_t done = 0;
	char *s;
	int ch;
	if((s = malloc(sz)) == NULL) {
		perror("malloc()");
		return -1;
	}
	while((ch = getchar()) != EOF) {
		s[done++] = ch;
		if(done == sz) {
			sz <<= 1;
			s = realloc(s, sz);
			if(s == NULL) {
				perror("realloc()");
				exit(EXIT_FAILURE);
			}
		}
	}
	while(done--)
		putchar(s[done]);
	free(s);
	return 0;
}
