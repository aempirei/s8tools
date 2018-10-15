#include <stdio.h>
#include <s8.h>
int main() {
	int ch;
	while((ch = getchar()) != EOF)
		printf("%d\n", (char)ch);
	return 0;
}
