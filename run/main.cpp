#define CATCH_CONFIG_RUNNER
#include "../utility/catch.hpp"

#include "initialize.h"

int main(int argc, char* argv[]) {

	time_t timer_start, timer_end;

#ifndef OFEC_UNIT_TEST
	OFEC::set_global_parameters(argc, argv);
#endif // !OFEC_UNIT_TEST

	OFEC::register_problem();
	OFEC::register_algorithm();
	time(&timer_start);

#ifdef OFEC_UNIT_TEST
	int result = Catch::Session().run(argc, argv);
#else
	OFEC::run();
#endif // OFEC_UNIT_TEST

	time(&timer_end);
	std::cout << "Time used: " << difftime(timer_end, timer_start) << " seconds" << std::endl;

	return 0;
}