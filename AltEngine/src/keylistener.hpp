#ifndef altinput_key_listener
#define altinput_key_listener

#include "listener.hpp"
#include "keys.hpp"
#include "logger.hpp"

class KeyListener : Listener {
	public:
	void on (Keys key) {
		logger->verbose((char*)"A key was pressed:");
		logger->verbose((char*)std::to_string(key).c_str());
	}
	KeyListener(AltLogger* loggerInstance) {
		logger = loggerInstance;
	}
	AltLogger* logger;
};

#endif