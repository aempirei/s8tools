#ifndef _S8_H
#define _S8_H

int s8_bank_init(char *, int, FILE *);
int s8_bank_shift(char *, int, FILE *);

const char *s8_context_basename();
const char *s8_context_filename(char *, size_t, const char *);
FILE *s8_open(const char *, const char *);
int s8_close(FILE *, const char *, const char *);

#endif
