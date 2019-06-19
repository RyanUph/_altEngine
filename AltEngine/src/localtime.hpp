#include <time.h>
#include <ctime>

#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
 
#ifndef localtime_s
#define localtime_s(tstruct, now) (localtime_r(now, tstruct))
#endif