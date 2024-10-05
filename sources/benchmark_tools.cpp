#include "../headers/benchmark_tools.h"

double measure_single(void (*function_handle)(void *), void *args, const test_precision_t precision)
{
	time_point start = std::chrono::steady_clock::now();

	function_handle(args);

	time_point finish = std::chrono::steady_clock::now();
	switch (precision)
	{
	case MILLI: return std::chrono::duration<double, std::milli>(finish - start).count();
	case MICRO: return std::chrono::duration<double, std::micro>(finish - start).count();
	case NANO:  return std::chrono::duration<double, std::nano>(finish - start).count();

	default: return std::chrono::duration<double, std::milli>(finish - start).count();
	}
}

double measure(void (*function_handle)(void *), void *(*prep_args_handle)(void *), void (*cleanup_handle)(void *),
	void *prep_args, const test_precision_t precision, const int test_count)
{
	double total = 0;
	for (int i = 0; i < test_count; ++i)
	{
		void *args = prep_args_handle(prep_args);
		total += measure_single(function_handle, args, precision);
		cleanup_handle(args);
	}
	return total / (double)test_count;
}