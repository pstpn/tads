#ifndef ___MY_MEAS___
#define ___MY_MEAS___

#include "my_types.h"


unsigned long long milliseconds_now(void);
tree_node_t *generate_tree(int count, int depth);
int get_measures(measurement_table table[MEAS_COUNT]);

#endif // ___MY_MEAS___