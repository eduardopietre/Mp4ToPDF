// Simple header wrote by me.
// Boiler plate for testing.

#include <opencv2/core/utils/logger.hpp>
#include <iostream>
#include <chrono>


#define TESTING_TIME_EXECUTION(name, codeblock) {\
	auto _tte_start = std::chrono::high_resolution_clock::now();\
	{\
		codeblock \
	};\
	auto _tte_stop = std::chrono::high_resolution_clock::now();\
	auto _tte_duration = std::chrono::duration_cast<std::chrono::milliseconds>(_tte_stop - _tte_start).count();\
	std::cout << "TESTING_TIME_EXECUTION '" << name << "' at line " << __LINE__  << " took "<< _tte_duration << " milliseconds." << std::endl;\
}
