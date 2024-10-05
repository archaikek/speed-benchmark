#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef _RANDOM_UTILS
	#include "random_utils.h"
#endif
#include <cstdlib>

typedef struct mergesort_args_t
{
	int *begin, *end;
};
typedef struct mergesort_hybrid_args_t
{
	int *begin, *end, cutoff;
};

typedef struct prep_mergesort_args_t
{
	int size;
	std::mt19937_64 &rng;
};
typedef struct prep_mergesort_hybrid_args_t
{
	int size;
	std::mt19937_64 &rng;
};

void bubblesort(int *tab, const int size, int *buffer);

//void _mergesort(int *tab, const int size, int *buffer);
void mergesort(int *begin, int *end);
void mergesort_handle(void *args);

mergesort_args_t *prep_mergesort_args(const int size, std::mt19937_64 &rng);
void *prep_mergesort_args_handle(void *args);
void cleanup_mergesort_args(mergesort_args_t *args);
void cleanup_mergesort_args_handle(void *args);


//void _mergesort_hybrid(int *tab, const int size, int *buffer, const int cutoff);
void mergesort_hybrid(int *begin, int *end, const int cutoff);
void mergesort_hybrid_handle(void *args);

int *random_int_table(const int size, std::mt19937_64 &rng);