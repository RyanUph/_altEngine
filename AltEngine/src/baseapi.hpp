#ifndef altrender_base_api
#define altrender_base_api

#include <iostream>
#include "logger.hpp"
#include "keydispatcher.hpp"

class BaseAPI {
	public:
	AltLogger* logger;
	int width = 0;
	int height = 0;
	char* titlename = (char*)"AltEngine";
	KeyDispatcher* dispatcher;
	
	BaseAPI (int width, int height, bool verbose, char* title) {
		if (!verbose) {
			verbose = false;
		}
		logger = new AltLogger(verbose);
		dispatcher = new KeyDispatcher(logger);
		titlename = title;
	}
};

#endif