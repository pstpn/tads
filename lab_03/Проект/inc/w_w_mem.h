#ifndef ___MY_W_W_MEM___
#define ___MY_W_W_MEM___

#include "my_types.h"


int allocate_spec_matrix(spar_mtrx_t *mtrx, int n, int count_nonzero);
int **allocate_matrix(int n, int m);
void free_matrix(int **data, int n);
void free_spec_matrix(spar_mtrx_t *mtrx);

#endif // ___MY_W_W_MEM___