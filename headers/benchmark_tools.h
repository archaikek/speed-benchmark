#pragma once
#ifndef _RANDOM_UTILS
	#include "random_utils.h"
#endif

enum test_precision_t
{
	MILLI, MICRO, NANO
};

double measure_single(void (*function_handle)(void *), void *args, const test_precision_t precision);


/*
* This function is meant to run a function a given number of times, preferably with new input data each time
* so as not to test it once on random data and then multiple times on solved data.
* 
*	function_handle - a generic handle for a void function; this should unwrap the arguments from the void* and pass
* them to the actual function to be tested
*	prep_args_handle - a generic handle for a function returning input data for the function to be tested, packed
* into a void*; the void* and all its contents should be created inside this function
*	cleanup_handle - a generic handle for a void function; this should unwrap the arguments from the void* and free
* them, then free the void* itself
*	prep_args - parameters for the input data preparation function; to be unpacked inside the prep_args_handle function
*	precision - precision of the time measurement
*	test_count - number of test to run the measurement for; average of those results will be returned
*/
double measure(void (*function_handle)(void *), void *(*prep_args_handle)(void *), void (*cleanup_handle)(void *), 
	void *prep_args, const test_precision_t precision, const int test_count);