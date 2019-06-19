#ifndef altinput_key_dispatcher
#define altinput_key_dispatcher

#import <memory>
#import <vector>
#import "keys.hpp"
#import "listener.hpp"

class KeyDispatcher {
	public:
	void add (Listener* listener) {
		listeners.add(listener)
	}
	void emit (Keys key) {
		for (Listener* listener : listeners) {
		  listener->on(key) // Let's just broadcast the message to all registered listeners
		}
	}
	private:
	Listener*[] listeners;
};
#endif