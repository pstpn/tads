#ifndef ___MY_MEAS___
#define ___MY_MEAS___

#include "my_types.h"


unsigned long long microseconds_now(void);
int get_measures(measurement_table table[MEAS_COUNT]);

#endif // ___MY_MEAS___