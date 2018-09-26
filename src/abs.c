#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch;
	while((ch = getchar()) != EOF)
		putchar(abs((char)ch));
	return 0;
}
