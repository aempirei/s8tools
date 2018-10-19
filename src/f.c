#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <s8.h>

static inline int clip(long int x) {
	return x < CHAR_MIN ? CHAR_MIN : x > CHAR_MAX ? CHAR_MAX : x;
}

int main(int argc, char **argv) {
	size_t N = argc > 2 ? argc - 2 : 1;
	char f[N];
	char x[N];
	int d = 1;

       	*f = argc == 2 ? atoi(argv[1]) : 1;

	if(argc > 2 && !s8_bank_defun(f, &d, argv+1, N+1)) {
		fprintf(stderr, "s8_bank_defun(..., %d): %s\n", (int)N+1, "failed");
		exit(EXIT_FAILURE);
	}

	while(s8_bank_next(x, N, stdin))
		putchar(clip(s8_bank_apply(f, x, d, N)));

	exit(EXIT_SUCCESS);
}