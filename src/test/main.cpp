#include <esl/examples/monitoring/Example01.h>

#include <iostream>
#include <string>


void printUsage() {
	std::cout << "Possible arguments:\n\n";
	std::cout << "  logging-example01\n";
}

int main(int argc, const char *argv[]) {
	std::string argument;

	if(argc == 2) {
		argument = argv[1];
	}
	else {
		std::cout << "Wrong number of arguments.\n\n";
		printUsage();
		return -1;
	}

	if(argument == "logging-example01") {
		esl::examples::monitoring::example01();
	}
	else {
		std::cout << "unknown argument \"" << argument << "\".\n\n";
		printUsage();
		return -1;
	}
	return 0;
}
