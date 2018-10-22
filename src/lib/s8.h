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
FILE *s8_io_open(const char *, const char *);
int s8_io_close(FILE *, const char *, const char *);
int s8_io_close_all(FILE *[], char *[], size_t, const char *);
int s8_io_open_all(FILE *[], char *[], size_t, const char *);

#ifdef S8_ASSIGNMENT_OPERATOR
#include <s8-basic-function.h>
#endif

#endif
