#ifndef _S8_H
#define _S8_H 1

#include <stdbool.h>

bool s8_bank_init(char *, int, FILE *);
bool s8_bank_shift(char *, int, FILE *);

const char *s8_io_basename();
const char *s8_io_filename_r(char *, size_t, const char *);
const char *s8_io_filename(const char *);
FILE *s8_io_open(const char *, const char *);
int s8_io_close(FILE *, const char *, const char *);
int s8_io_close_all(FILE **, char **, size_t, const char *);
int s8_io_open_all(FILE **, char **, size_t, const char *);

#endif
