#ifndef altinput_listener
#define altinput_listener

#include "keys.hpp"
#include "logger.hpp"

class Listener {
	void on (Keys key) {
		logger->verbose((char*)"A key was pressed.");
		logger->verbose((char*)key);
	}
	AltLogger* logger;
	Listener (AltLogger* log) {
		logger = log;
	}
};

#endif