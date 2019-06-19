#include <time.h>
#include <ctime>
#include <iostream>

#ifndef localtime_s
#define localtime_s(tstruct, now) (localtime_r(now, tstruct))
#endif