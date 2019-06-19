#ifndef altinput_key_listener
#define altinput_key_listener

#include "listener.hpp"
#include "keys.hpp"
#include "logger.hpp"

class KeyListener : Listener {
	public:
	void on (Keys key, AltLogger* logger) {
		std::string text = "A key was pressed: "+ std::to_string(key);
		logger->verbose((char*)text.c_str());
	}
};

#endif