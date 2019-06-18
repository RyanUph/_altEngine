#ifndef altengine_logger
#define altengine_logger

#include <iostream>
std::string getDate();

class AltLogger {
  public:
	bool verboseEnabled;
	char* getDate() {
		time_t now = time(0);
		return ctime(&now);
	}

	void log(char* message) {
		std::cout << "[LOG] [" << getDate() << "] " << message;
	}
	void warning(char* message) {
		std::cout << "[WARNING] [" << getDate() << "] " << message;
	}
	void error(char* message) {
		std::cout << "[ERROR] [" << getDate() << "] " << message;
	}
	void verbose(char* message) {
		if (verboseEnabled) {
			std::cout << "[VERBOSE] [" << getDate() << "] " << message;
		}
	}

	AltLogger(bool enableVerbose = false) {
		verboseEnabled = enableVerbose;
	}
};

#endif