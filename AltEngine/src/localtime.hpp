#include <time.h>
#include <ctime>

#pragma warning(disable : 4996)
#ifndef localtime_s
#define localtime_r(now, tstruct) (localtime_s(tstruct, now))
#endif