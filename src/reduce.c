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

#define OPSIG(NAME)			long NAME##_instruction(long x, long y)
#define OPCODE(NAME, INFIX_SYM)		OPSIG(NAME) { return ( x INFIX_SYM y ); }
#define OPENTRY(NAME, INFIX_CHR)	{ INFIX_CHR, #NAME, NAME##_instruction }
#define OPENTRY_END			{ '\0', NULL, NULL }

typedef long op_t(long, long);

typedef struct instruction {
	char symbol;
	const char *name;
	op_t *op;
} instruction_t;

typedef struct code {
	const instruction_t *instruction_ptr;
	char reg;
	bool is_immediate;
	long operand;
} code_t;

long register_file[26];

OPCODE(add, +)
OPCODE(sub, -)
OPCODE(mul, *)
OPCODE(div, /)
OPCODE(mod, %)
OPCODE(and, &)
OPCODE(xor, ^)
OPCODE(or, |)
OPCODE(mov, =)
OPSIG(min) { return x < y ? x : y; }
OPSIG(max) { return x > y ? x : y; }

const instruction_t instruction_set[] = {
	OPENTRY(add, '+'),
	OPENTRY(sub, '-'),
	OPENTRY(mul, '*'),
	OPENTRY(div, '/'),
	OPENTRY(mod, '%'),
	OPENTRY(and, '&'),
	OPENTRY(xor, '^'),
	OPENTRY(or, '|'),
	OPENTRY(mov, '='),
	OPENTRY(min, '<'),
	OPENTRY(max, '>'),
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

	size_t num_ops = count_instructions(s);
	code_t *code = malloc((num_ops + 1) * sizeof(code_t));
	memset(code, 0, (num_ops + 1) * sizeof(code_t));

	for(code_t *cp = code; *s; cp++) {
		cp->instruction_ptr = lookup_instruction(*s++);
		if(!*s) goto failure;
		cp->reg = toupper(*s++);
		if(!*s) goto failure;
		if((cp->is_immediate = !isalpha(*s))) {
			char *t;
			cp->operand = strtol(s, &t, 0);
			s = t;
		} else {
			cp->operand = toupper(*s++);
		}
	}

	return code;
failure:
	free(code);
	return NULL;
}

void print_code(code_t *code) {
	for(size_t n = 0; code[n].instruction_ptr != NULL; n++) {
		const char *N = code[n].instruction_ptr->name;
		char R = code[n].reg;
		char F = code[n].instruction_ptr->symbol;
		long O = code[n].operand;
		if(code[n].is_immediate)
			printf("[%02lx] %3s %c, %-5ld ;  %c := %c %c %ld\n", n, N, R, O, R, R, F, O);
		else
			printf("[%02lx] %3s %c, %-5c ;  %c := %c %c %c\n", n, N, R, (char)O, R, R, F, (char)O);
	}
}

void run_code(code_t *code, int ch) {

	REG(X) = ch;

	for(char r = 'A'; r <= 'Z'; r++)
		printf("%4lx ", R(r));
	putchar('\n');

	for(code_t *cp = code; cp->instruction_ptr != NULL; cp++)
		R(cp->reg) = (cp->instruction_ptr->op)(R(cp->reg), cp->is_immediate ? cp->operand : R(cp->operand));
}

int main(int argc, char *argv[]) {

	int ch;

	code_t *code = parse_code(argc == 1 ? "" : argv[1]);

	memset(register_file, 0, sizeof(register_file));

	puts("PROGRAM CODE DISASSEMBLY");
	print_code(code);

	puts("REGISTER FILE STATE");
	for(char r = 'A'; r <= 'Z'; r++)
		printf("%4c ", r);
	putchar('\n');

	while((ch = getchar()) != EOF)
		run_code(code, ch);

	putchar('\n');
	for(char r = 'A'; r <= 'Z'; r++)
		printf("%4c ", r);
	putchar('\n');
	for(char r = 'A'; r <= 'Z'; r++)
		printf("%4lx ", R(r));
	putchar('\n');



	putchar(REG(Y));

	free(code);

	exit(EXIT_SUCCESS);
}
