#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <s8-inline-helpers.h>

int main() {
	int ch;
	while((ch = getchar()) != EOF)
		putchar(sign((char)ch));
	return 0;
}
