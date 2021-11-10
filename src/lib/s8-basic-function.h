#ifndef _S8_BASIC_FUNCTION_H
#define _S8_BASIC_FUNCTION_H 1

#include <stdbool.h>

typedef bool binary_relation_t(int, int);
typedef int binary_function_t(int, int);
typedef int bank_function_t(const char *, size_t);

extern binary_relation_t cmp_eq;
extern binary_relation_t cmp_ne;
extern binary_relation_t cmp_lt;
extern binary_relation_t cmp_gt;
extern binary_relation_t cmp_le;
extern binary_relation_t cmp_ge;

extern binary_function_t binary_add;
extern binary_function_t binary_sub;
extern binary_function_t binary_mul;
extern binary_function_t binary_or;
extern binary_function_t binary_xor;
extern binary_function_t binary_and;
extern binary_function_t binary_min;
extern binary_function_t binary_max;
extern binary_function_t binary_avg;

extern binary_function_t *binary_add_final;
extern binary_function_t *binary_sub_final;
extern binary_function_t *binary_mul_final;
extern binary_function_t *binary_or_final;
extern binary_function_t *binary_xor_final;
extern binary_function_t *binary_and_final;
extern binary_function_t *binary_min_final;
extern binary_function_t *binary_max_final;
extern binary_function_t *binary_avg_final;

extern bank_function_t bank_fold;

extern int bank_function(int, char **, bank_function_t *);
extern int fold_function(int, char **, binary_function_t *, binary_function_t *);

extern int ordinal(const char *);

#endif
