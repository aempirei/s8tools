#ifndef S8_ASSIGNMENT_OPERATOR
#error "Inclusion of <s8-basic-function.h> requires the definition of S8_ASSIGNMENT_OPERATOR macro."
#else
#ifndef _S8_BASIC_OPERATOR_H
#define _S8_BASIC_OPERATOR_H

static int parallel_mode(int argc, char **argv) {

	const size_t N = argc - 1;
	FILE *fs[N];
	char x[N];

	if(s8_io_open_all(fs, argv+1, N, "r") == -1) {
		perror("s8_io_open_all()");
		return EXIT_FAILURE;
	}
	
	while(s8_bank_parallel_next(x, N, fs)) {

		int y = x[0];

		for(size_t k = 1; k < N; k++)
			y S8_ASSIGNMENT_OPERATOR x[k];

		putchar(y);
	}

	if(s8_io_close_all(fs, argv+1, N, "r") == -1) {
		perror("s8_io_close_all()");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

static int serial_mode(int argc, char **argv) {

	const size_t N = (argc == 1) ? 2 : atoi(argv[1]);
	char x[N];

	while(s8_bank_serial_next(x, N, stdin)) {

		int y = x[0];

		for(size_t k = 1; k < N; k++)
			y S8_ASSIGNMENT_OPERATOR x[k];

		putchar(y);
	}

	return EXIT_SUCCESS;
}
#endif
#endif
