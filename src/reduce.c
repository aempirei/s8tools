#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

#define REGCNUM(C)	(toupper(C)-'A')
#define REGSNUM(S)	REGCNUM(*(S))
#define REGNUM(X)	REGSNUM(#X)
#define REG(X)		register_file[REGNUM(X)]
#define R(X)		register_file[REGCNUM(X)]

#define OPCODE(NAME, INFIX_SYM)		long NAME##_instruction(long x, long y) { return ( x INFIX_SYM y ); }
#define OPENTRY(NAME, INFIX_CHR)	{ INFIX_CHR, NAME##_instruction }

typedef long op_t(long, long);

typedef struct {
	char symbol;
	op_t *op;
} instruction_t;

typedef struct {
	instruction_t *instruction_ptr;
	char reg;
	bool is_indirect;
	long operand;
} code_t;

long register_file[26];

OPCODE(add, *)
OPCODE(mul, *)
OPCODE(and, &)
OPCODE(xor, ^)
OPCODE(or, |)

instruction_t instruction_set[] = {
	OPENTRY(add, '+'),
	OPENTRY(mul, '*'),
	OPENTRY(and, '&'),
	OPENTRY(xor, '^'),
	OPENTRY(or, '|'),
};

code_t *parse_code(const char *s) {
	code_t *code = NULL;
	const char *p = s;

	while(*p) {
		p++;
	}

	return code;
}

void run_code(code_t *code, int ch) {
	REG(X) = ch;
	for(code_t *cp = code; cp->instruction_ptr != NULL; cp++)
		R(cp->reg) = (cp->instruction_ptr->op)(R(cp->reg), cp->is_indirect ? R(cp->operand) : cp->operand);
}

int main(int argc, char *argv[]) {

	int ch;

	code_t *code = argc == 2 ? parse_code(argv[1]) : NULL;

	memset(register_file, 0, sizeof(register_file));

	while((ch = getchar()) != EOF)
		run_code(code, ch);

	putchar(REG(Y));

	exit(EXIT_SUCCESS);
}
