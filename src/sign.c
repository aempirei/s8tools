#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int sign(int x) {
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}

int main() {
	int ch;
	while((ch = getchar()) != EOF)
		putchar(sign((char)ch));
	return 0;
}
