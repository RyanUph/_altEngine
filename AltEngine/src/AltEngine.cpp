#include <iostream>
#include "logger.hpp"

int main() {
	AltLogger* altLogger = new AltLogger(true);
	altLogger->log((char*)"Hi log!");
	altLogger->error((char*)"Get out, error!");
	altLogger->verbose((char*)"Welcome, verbose!");
	altLogger->warning((char*)"Be careful, warning!");
	
	std::cin.get();
	delete altLogger;
}