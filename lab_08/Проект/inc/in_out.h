#ifndef ___MY_IN_OUT___
#define ___MY_IN_OUT___

#include <stdio.h>


int get_size(FILE *f, int *n, int *m);
int filling_matrix(FILE *f, int **ptrs, int n, int m);
int get_in_file(FILE *f, char **word, int max_len);
void export_to_dot(FILE *f, const char *graph_name, int **graph_mtrx, int n, int m);

#endif // ___MY_IN_OUT___