#ifndef altrender_base_api
#define altrender_base_api

#import <iostream>
#import "logger.hpp"
#import "keydispatcher.hpp"

class BaseAPI {
	public:
	AltLogger* logger;
	int width = 0;
	int height = 0;
	KeyDispatcher* dispatcher;
	
	BaseAPI (int width, int height, bool verbose) {
		if (!verbose) {
			verbose = false;
		}
		logger = new AltLogger(verbose);
		dispatcher = new KeyDispatcher(logger);
	}
};

#endif