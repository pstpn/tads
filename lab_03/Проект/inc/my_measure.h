#ifndef ___MY_MEAS___
#define ___MY_MEAS___

#include "my_types.h"


unsigned long long milliseconds_now(void);
void get_measures(measurement_table table[], car_info cars[], help_table inds[], int count);

#endif // ___MY_MEAS___