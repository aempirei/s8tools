#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>
#include <s8.h>
#include <s8-basic-function.h>

#define BINARY_FUNCTION(N,O) int binary_##N(int a, int b) { return a O b; }

BINARY_FUNCTION(add, +)
BINARY_FUNCTION(mul, *)
BINARY_FUNCTION(or, |)
BINARY_FUNCTION(xor, ^)
BINARY_FUNCTION(and, &)
BINARY_FUNCTION(min, < b ? a :)
BINARY_FUNCTION(max, > b ? a :)

#undef BINARY_FUNCTION

#define BINARY_RELATION(N,R) bool cmp_##N(int a, int b) { return a R b ? 1 : 0; }

BINARY_RELATION(eq, ==)
BINARY_RELATION(ne, !=)
BINARY_RELATION(le, <=)
BINARY_RELATION(ge, >=)
BINARY_RELATION(lt, <)
BINARY_RELATION(gt, >)

#undef BINARY_RELATION

static int fold(const char *, size_t, binary_function_t *);

static binary_function_t *fold_fp;

bool bind_to_fold(binary_function_t *f) {
	fold_fp = f;
	return f != NULL;
}

int bank_fold(const char *x, size_t N) {
	return fold(x, N, fold_fp);
}

int ordinal(const char *s) {
	return (*s == ':') ? s[1] : strtol(s, NULL, 0);
}

static int fold(const char *x, size_t N, binary_function_t *fp) {
	switch(N) {
		case 0:
			return 0;
		case 1:
			return x[0];
		default:
			return (*fp)(x[0], fold(x + 1, N - 1, fp));
	}
}

int fold_function(int argc, char **argv, binary_function_t *binary_fp) {
	bind_to_fold(binary_fp);
	return bank_function(argc, argv, bank_fold);
}

int bank_function(int argc, char **argv, bank_function_t *bank_fp) {

        const size_t N = (argc == 1) ? 2 : atoi(argv[1]) > 0 ? atoi(argv[1]) : 2;
        char x[N];
        char typesige[N+1];
        char typesiga[256];
        char typesigw[2] = { s8_type_signed };
        char prog[32];
        int id;

        memset(typesige, s8_type_signed, N);
        typesige[N] = '\0';

        s8_io_typesig_r(prog, sizeof(prog), &id, typesiga, sizeof(typesiga), stdin);
        s8_io_typesig_w(*argv, typesigw, stdout);

        if(getenv("S8_TYPEINFO"))
                fprintf(stderr, "%s %d %s/%s -> %s %d :%s\n", prog, id, typesiga, typesige, basename(*argv), getpid(), typesigw);

        while(s8_bank_serial_next(x, N, stdin))
		putchar((*bank_fp)(x, N));

        return EXIT_SUCCESS;
}
