#ifndef ___MY_IN_OUT___
#define ___MY_IN_OUT___

#include <stdio.h>

#include "my_types.h"


int get_size(FILE *f, int *n, int *m);
void read_spec_matrix(int **p_mtrx, spar_mtrx_t *mtrx, int n, int m);
int read_matrix(FILE *f, int **p_mtrx, int n, int m, int *count_nonzero);
int coord_read_matrix(FILE *f, int **p_mtrx, int n, int m, int *count_nonzero);
void print_matrix(int **p_mtrx, int n, int m);
void draw_line(int len);
void print_spec_matrix(spar_mtrx_t *mtrx, int n);
void print_measures(measurement_table table[], int count);

#endif // ___MY_IN_OUT___