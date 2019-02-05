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
#include <s8-inline-helpers.h>

int main(int argc, char **argv) {
	const size_t N = argc > 2 ? argc - 2 : 1;
	char f[N];
	char x[N];
	int d = 1;

       	*f = argc == 2 ? strtol(argv[1], NULL, 0) : 1;

	if(argc > 2 && !s8_bank_defun(f, &d, argv+1, N+1)) {
		fprintf(stderr, "s8_bank_defun(..., %d): %s\n", (int)N+1, "failed");
		exit(EXIT_FAILURE);
	}

	while(s8_bank_serial_next(x, N, stdin))
		putchar(clip(s8_bank_apply(f, x, d, N)));

	exit(EXIT_SUCCESS);
}
