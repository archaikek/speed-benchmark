#include "headers/benchmark_tools.h"
#include "headers/mergesort.h"

#define TEST_SIZE 100000000
#define CUTOFF 32
#define TEST_COUNT 20

int main()
{
	std::mt19937_64 *rng = new std::mt19937_64(2221);

	int *tab = random_int_table(TEST_SIZE, *rng);
	//mergesort(tab, tab + TEST_SIZE);
	//mergesort_hybrid(tab, tab + TEST_SIZE, CUTOFF);

	mergesort_args_t args1 = { tab, tab + TEST_SIZE };
	mergesort_hybrid_args_t args2 = { tab, tab + TEST_SIZE, CUTOFF };

	prep_mergesort_args_t prep_args1 = { TEST_SIZE, *rng };

	printf("Test started. Processing...\n");
	double time = measure(mergesort_handle, prep_mergesort_args_handle, cleanup_mergesort_args_handle, &prep_args1, MILLI, TEST_COUNT);
	printf("Test finished. Average time: %.3lf ms.\n", time);

	free(tab);
	return 0;
}