#ifndef altevent_dispatcher
#define altevent_dispatcher

#include "listener.hpp"
#include <vector>

class Dispatcher {
	public:
	void add (Listener* listener) {
		listeners.push_back(listener);
	}
	void emit () {
		for (Listener* listener : listeners) {
		  listener->on();
		}
	}
	std::vector<Listener*> listeners;
};

#endif