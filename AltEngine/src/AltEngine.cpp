#include <iostream>
#include "baseapi.hpp"
#include "keylistener.hpp"
#include "keys.hpp"

int main() {
	// Let's create a test listener
	KeyListener* listener = new KeyListener();
	// Now, let's create a rendering instance (for testing)
	BaseAPI* api = new BaseAPI(300, 300, true, (char*)"AltEngine test");
	// Let's now register our listener
	api->dispatcher->add(listener);
	// Let's emit a key just to test if eveything is working
	api->dispatcher->emit(Keys::UP_ARROW);
	
	api->logger->log((char*)"Hi log!");
	api->logger->error((char*)"Get out, error!");
	api->logger->verbose((char*)"Welcome, verbose!");
	api->logger->warning((char*)"Be careful, warning!");
	
	std::cin.get();
	delete api;
	delete listener;
}