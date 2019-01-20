#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch, x = 0;
	while((ch = getchar()) != EOF) {
		if(ch != 0)
			x = ch;
		putchar(x);
	}
	exit(EXIT_SUCCESS);
}
