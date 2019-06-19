#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <ctime>

#ifndef localtime_s
#define localtime_s(tstruct, now) (localtime_r(now, tstruct))
#endif