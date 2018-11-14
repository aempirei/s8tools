#ifndef _S8_H
#define _S8_H 1

#include <stdbool.h>

bool s8_bank_init(char *, size_t, FILE *);
bool s8_bank_shift(char *, size_t, FILE *);
bool s8_bank_serial_next(char *, size_t, FILE *);
bool s8_bank_parallel_next(char *, size_t, FILE *[]);
bool s8_bank_defun(char *, int *, char *[], size_t);
long int s8_bank_apply(const char *, const char *, int, size_t);

const char *s8_io_basename();
const char *s8_io_filename_r(char *, size_t, const char *);
const char *s8_io_filename(const char *);
FILE *s8_io_open(const char *, char);
bool s8_io_ready(const char *, char);
int s8_io_close(FILE *, const char *, char);
int s8_io_close_all(FILE *[], char *[], size_t, char);
int s8_io_open_all(FILE *[], char *[], size_t, char);

enum s8_type {
	s8_type_any = 'x',
	s8_type_unsigned = 'u',
	s8_type_signed = 's',
	s8_type_7bit = '7', 
	s8_type_sign = '+',
	s8_type_bool = 'b',
	s8_type_zero = '0',
};

bool s8_io_typesig_r(char *, size_t, int *, char *, size_t, FILE *);
bool s8_io_typesig_w(char *, char *, FILE *);
bool s8_io_type_append(char *, size_t, enum s8_type);
bool s8_io_castable(enum s8_type, enum s8_type);

#endif
