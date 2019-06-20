#ifndef altinput_key_dispatcher
#define altinput_key_dispatcher

#include "keys.hpp"
#include "dispatcher.hpp"
#include "keylistener.hpp"
#include "logger.hpp"
#include <vector>

class KeyDispatcher : Dispatcher {
	public:
	void add (KeyListener* listener) {
		listeners.push_back(listener);
	}
	int emit (Keys key) {
		for (KeyListener* listener : listeners) {
		  listener->on(key, logger); // Let's just broadcast the message to all registered listeners
		}
		return key;
	}
	KeyDispatcher (AltLogger* log) {
		logger = log;
	}
	AltLogger* logger;
	std::vector<KeyListener*> listeners;
};
#endif