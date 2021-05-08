// Simple header wrote by me.
// Boiler plate for testing.

#include <opencv2/core/utils/logger.hpp>
#include <iostream>
#include <chrono>


#define TESTING_TIME_NOW() (std::chrono::high_resolution_clock::now())
#define TESTING_TIME_MILLISECONDS_DIFFERENCE(t1, t2) (std::chrono::duration_cast<std::chrono::milliseconds>((t2) - (t1)).count())


#define TESTING_TIME_EXECUTION(name, codeblock) {\
	auto _tte_start = TESTING_TIME_NOW();\
	{\
		codeblock \
	};\
	auto _tte_stop = TESTING_TIME_NOW();\
	auto _tte_duration = TESTING_TIME_MILLISECONDS_DIFFERENCE(_tte_start, _tte_stop);\
	std::cout << "TESTING_TIME_EXECUTION '" << name << "' at line " << __LINE__  << \
	" took "<< _tte_duration << " milliseconds." << std::endl;\
}


#define TESTING_MULTIPLE_TIME_EXECUTION(name, repeat, codeblock) {\
	auto _tte_start = TESTING_TIME_NOW();\
	for (int _tte_i = 0; _tte_i < repeat; _tte_i++) {\
		codeblock \
	};\
	auto _tte_stop = TESTING_TIME_NOW();\
	auto _tte_duration = TESTING_TIME_MILLISECONDS_DIFFERENCE(_tte_start, _tte_stop) / repeat;\
	std::cout << "TESTING_MULTIPLE_TIME_EXECUTION '" << name << "' at line " << __LINE__  << " average time of "<< _tte_duration << " milliseconds." << std::endl;\
}
