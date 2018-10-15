#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch;
	bool x;
	printf("bool size = %d\n", sizeof(x));
	while((ch = getchar()) != EOF)
		printf("%d\n", (char)ch);
	return 0;
}
