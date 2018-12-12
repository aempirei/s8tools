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
#define OPENTRY_END			{ '\0', NULL }

typedef long op_t(long, long);

typedef struct {
	char symbol;
	op_t *op;
} instruction_t;

typedef struct {
	const instruction_t *instruction_ptr;
	char reg;
	bool is_immediate;
	long operand;
} code_t;

long register_file[26];

OPCODE(add, +)
OPCODE(mul, *)
OPCODE(and, &)
OPCODE(xor, ^)
OPCODE(or, |)

const instruction_t instruction_set[] = {
	OPENTRY(add, '+'),
	OPENTRY(mul, '*'),
	OPENTRY(and, '&'),
	OPENTRY(xor, '^'),
	OPENTRY(or, '|'),
	OPENTRY_END
};

const instruction_t *lookup_instruction(char symbol) {
	for(size_t n = 0; instruction_set[n].op != NULL; n++)
		if(symbol == instruction_set[n].symbol)
			return instruction_set + n;
	return NULL;
}

size_t count_instructions(const char *s) {
	size_t n = 0;
	while(*s)
		if(ispunct(*s++))
			n++;
	return n;
}

code_t *parse_code(const char *s) {

	size_t num_instructions = count_instructions(s);
	size_t ip = 0;
	code_t *code = malloc(num_instructions * sizeof(code_t));
	const char *p = s;

	while(*p) {
		code[ip].instruction_ptr = lookup_instruction(*p++);
		if(!*p) goto failure;
		code[ip].reg = toupper(*p++);
		if(!*p) goto failure;
		if((code[ip].is_immediate = !isalpha(*p))) {
			char *q;
			code[ip].operand = strtol(p, &q, 0);
			p = q;
		} else {
			code[ip].operand = toupper(*p++);
		}
	}

	return code;
failure:
	free(code);
	return NULL;
}

void run_code(code_t *code, int ch) {
	REG(X) = ch;
	for(code_t *cp = code; cp->instruction_ptr != NULL; cp++)
		R(cp->reg) = (cp->instruction_ptr->op)(R(cp->reg), cp->is_immediate ? cp->operand : R(cp->operand));
}

int main(int argc, char *argv[]) {

	int ch;

	code_t *code = argc == 2 ? parse_code(argv[1]) : NULL;

	memset(register_file, 0, sizeof(register_file));

	while((ch = getchar()) != EOF)
		run_code(code, ch);

	putchar(REG(Y));

	free(code);

	exit(EXIT_SUCCESS);
}
