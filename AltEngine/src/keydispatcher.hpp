#ifndef altinput_key_dispatcher
#define altinput_key_dispatcher

#import "keys.hpp"
#import "dispatcher.hpp"
#import "keylistener.hpp"
#import <vector>

class KeyDispatcher : Dispatcher {
	public:
	void add (KeyListener* listener) {
		listeners.push_back(listener);
	}
	void emit (Keys key) {
		for (KeyListener* listener : listeners) {
		  listener->on(key); // Let's just broadcast the message to all registered listeners
		}
	}
	std::vector<KeyListener*> listeners;
};
#endif