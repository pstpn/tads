#ifndef ___MY_MEAS___
#define ___MY_MEAS___

#include "my_types.h"


unsigned long long milliseconds_now(void);
int get_measures(measurement_table table[MEAS_LEN]);

#endif // ___MY_MEAS___