#include <iostream>
#include "logger.hpp"

int main() {
	AltLogger* altLogger = new AltLogger(true);
	altLogger->log("Hi log!");
	altLogger->error("Get out, error!");
	altLogger->verbose("Welcome, verbose!");
	altLogger->warning("Be careful, warning!");
	
	std::cin.get();
}
