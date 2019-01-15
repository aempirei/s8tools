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
#include <s8.h>

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

bool debug;

long loop_num;
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
OPSIG(ruz) { return y ? y : x; }

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
	OPENTRY(ruz, '?'),
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

void print_code(code_t *code, FILE *fp) {
	for(size_t n = 0; code[n].instruction_ptr != NULL; n++) {
		const char *N = code[n].instruction_ptr->name;
		char R = code[n].reg;
		char F = code[n].instruction_ptr->symbol;
		long O = code[n].operand;
		if(code[n].is_immediate)
			fprintf(fp,"[%02lx] %3s %c, %-5ld ;  %c := %c %c %ld\n", n, N, R, O, R, R, F, O);
		else
			fprintf(fp,"[%02lx] %3s %c, %-5c ;  %c := %c %c %c\n", n, N, R, (char)O, R, R, F, (char)O);
	}
}

void print_register_names(FILE *fp) {
	for(char r = 'A'; r <= 'Z'; r++) fprintf(fp,"%5c ", r);
	fputc('\n',fp);
}

void print_register_values(FILE *fp) {
	for(char r = 'A'; r <= 'Z'; r++) fprintf(fp, "%5ld ", R(r));
	fputc('\n',fp);
}

void run_code(code_t *code, char *x, size_t N, FILE *fp) {

	REG(N) = N;
	int c = fgetc(fp);
	REG(Z) = feof(fp) ? 1 : 0;
	ungetc(c,fp);
	REG(Q) = loop_num++;

	for(size_t n = 0; n < N; n++)
		R('A' + n) = x[n];

	for(code_t *cp = code; cp->instruction_ptr != NULL; cp++)
		R(cp->reg) = (cp->instruction_ptr->op)(R(cp->reg), cp->is_immediate ? cp->operand : R(cp->operand));

	if(debug)
		print_register_values(stderr);

	if(REG(O) != 0)
		putchar(REG(P));
}

int main(int argc, char *argv[]) {

	const size_t N = argc > 1 ? strtoul(argv[1], NULL, 0) : 1;
	char x[N];

	code_t *code = parse_code(argc > 2 ? argv[2] : "");

	debug = argc > 3;

	memset(register_file, 0, sizeof(register_file));

	if(debug) {
		fputs("PROGRAM CODE DISASSEMBLY\n",stderr);
		print_code(code,stderr);

		fputs("REGISTER FILE STATE\n",stderr);
		print_register_names(stderr);
	}

	loop_num = 0;

	while(s8_bank_serial_next(x, N, stdin))
		run_code(code, x, N, stdin);

	if(debug)
		print_register_names(stderr);

	free(code);

	exit(EXIT_SUCCESS);
}
