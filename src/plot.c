#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch = 0;
	int n = 0;
	printf("<path d=\"M %d %d ", n++, ch);
	while((ch = getchar()) != EOF) {
		ch = (char)ch;
		printf("L %d %d ", n++, ch);
	}
	printf("\" />\n");
	return 0;
}
