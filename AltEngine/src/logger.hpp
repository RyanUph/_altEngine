#ifndef altengine_logger
#define altengine_logger

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

class AltLogger {
  public:
	bool verboseEnabled;
	const std::string getDate() {
		std::time_t now = std::time(0);
		struct tm tstruct;
		char buf[80];
		localtime_s(&tstruct, &now);

		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}

	void log(char* message) {
		std::cout << "[LOG] [" << getDate() << "] " << message << std::endl;
	}
	void warning(char* message) {
		std::cout << "[WARNING] [" << getDate() << "] " << message << std::endl;
	}
	void error(char* message) {
		std::cout << "[ERROR] [" << getDate() << "] " << message << std::endl;
	}
	void verbose(char* message) {
		if (verboseEnabled) {
			std::cout << "[VERBOSE] [" << getDate() << "] " << message << std::endl;
		}
	}

	AltLogger(bool enableVerbose = false) {
		verboseEnabled = enableVerbose;
	}
};

#endif