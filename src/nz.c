#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch;
	while((ch = getchar()) != EOF)
		putchar(ch != 0 ? 1 : 0);
	return 0;
}
