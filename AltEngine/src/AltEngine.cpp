#include <iostream>
#include "logger.hpp"
#include "keydispatcher.hpp"
#include "keylistener.hpp"
#include "keys.hpp"

int main() {
	AltLogger* altLogger = new AltLogger(true);
	
	// Let's create a test listener
	KeyListener* listener = new KeyListener(altLogger);
	// Now, let's create a event dispatcher
	KeyDispatcher* dispatcher = new KeyDispatcher();
	// and register our listener...
	dispatcher->add(listener);
	// Now, let's test it!
	dispatcher->emit(Keys::UP_ARROW);
	
	altLogger->log((char*)"Hi log!");
	altLogger->error((char*)"Get out, error!");
	altLogger->verbose((char*)"Welcome, verbose!");
	altLogger->warning((char*)"Be careful, warning!");
	
	std::cin.get();
	delete altLogger;
}