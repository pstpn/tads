#ifndef ___MY_TYPES___
#define ___MY_TYPES___


typedef struct
{
    int *a;
    int *ja;
    int *ia;
    int count;
} spar_mtrx_t;


typedef struct measure
{
    long long unsigned time;
    int mem;
    int fill;
    int n;
    int m;
    char mtrx_type;
} measurement_table;

#endif // ___MY_TYPES___