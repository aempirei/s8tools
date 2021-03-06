#ifndef _S8_BASIC_FUNCTION_H
#define _S8_BASIC_FUNCTION_H 1

#include <stdbool.h>

typedef bool binary_relation_t(int, int);
typedef int binary_function_t(int, int);
typedef int bank_function_t(const char *, size_t);

binary_relation_t cmp_eq;
binary_relation_t cmp_ne;
binary_relation_t cmp_lt;
binary_relation_t cmp_gt;
binary_relation_t cmp_le;
binary_relation_t cmp_ge;

binary_function_t binary_add;
binary_function_t binary_sub;
binary_function_t binary_mul;
binary_function_t binary_or;
binary_function_t binary_xor;
binary_function_t binary_and;
binary_function_t binary_min;
binary_function_t binary_max;
binary_function_t binary_avg;

binary_function_t *binary_add_final;
binary_function_t *binary_sub_final;
binary_function_t *binary_mul_final;
binary_function_t *binary_or_final;
binary_function_t *binary_xor_final;
binary_function_t *binary_and_final;
binary_function_t *binary_min_final;
binary_function_t *binary_max_final;
binary_function_t *binary_avg_final;

bank_function_t bank_fold;

int bank_function(int, char **, bank_function_t *);
int fold_function(int, char **, binary_function_t *, binary_function_t *);

int ordinal(const char *);

#endif
