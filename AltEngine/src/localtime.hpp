#include <time.h>
#include <ctime>

#ifndef localtime_s
#define localtime_r(now, tstruct) (localtime_s(tstruct, now))
#endif