#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

int main() {
	size_t n = 0;
	int ch;
	while((ch = getchar()) != EOF) {
		if(ch)
			putchar(n);
		n++;
	}
	exit(EXIT_SUCCESS);
}
