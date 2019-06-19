#ifndef altinput_key_dispatcher
#define altinput_key_dispatcher

#import "keys.hpp"
#import "dispatcher.hpp"
#import "keylistener.hpp"
#import "logger.hpp"
#import <vector>

class KeyDispatcher : Dispatcher {
	public:
	void add (KeyListener* listener) {
		listeners.push_back(listener);
	}
	void emit (Keys key) {
		for (KeyListener* listener : listeners) {
		  listener->on(key, logger); // Let's just broadcast the message to all registered listeners
		}
	}
	KeyDispatcher (AltLogger* log) {
		logger = log;
	}
	AltLogger* logger;
	std::vector<KeyListener*> listeners;
};
#endif