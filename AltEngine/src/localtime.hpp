#include <time.h>
#include <ctime>
#include <iostream>

#pragma warning(disable : 4996)
#ifndef localtime_s
#define localtime_s(tstruct, now) (localtime_r(now, tstruct))
#endif