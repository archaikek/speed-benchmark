#include "../headers/mergesort.h"

void bubblesort(int *tab, const int size, int *buffer)
{
	buffer[0] = tab[0];
	for (int i = 1; i < size; ++i)
	{
		for (int j = i; j >= 0; --j)
		{
			if (tab[i] < buffer[j - 1])
			{
				buffer[j] = buffer[j - 1];
			}
			else
			{
				buffer[j] = tab[i];
				break;
			}
		}
	}
	for (int i = 0; i < size; ++i)
	{
		tab[i] = buffer[i];
	}
}

void _mergesort(int *tab, const int size, int *buffer)
{
	if (size == 1) return;

	const int half = size / 2;
	int *mid = tab + half;
	_mergesort(tab, half, buffer);
	_mergesort(mid, size - half, buffer);

	int left = 0, right = 0;
	for (int i = 0; i < size; ++i)
	{
		if ((left < half && tab[left] < mid[right]) || right >= size - half)
		{
			buffer[i] = tab[left++];
		}
		else
		{
			buffer[i] = mid[right++];
		}
	}
	for (int i = 0; i < size; ++i)
	{
		tab[i] = buffer[i];
	}
}
void mergesort(int *begin, int *end)
{
	const int size = end - begin;
	int *buffer = (int *)malloc(size * sizeof(int));

	_mergesort(begin, size, buffer);

	free(buffer);
}
void mergesort_handle(void *args)
{
	mergesort_args_t *_args = (mergesort_args_t *)args;
	mergesort(_args->begin, _args->end);
}

mergesort_args_t *prep_mergesort_args(const int size, std::mt19937_64 &rng)
{
	mergesort_args_t *args = (mergesort_args_t *)malloc(sizeof(mergesort_args_t));
	args->begin = random_int_table(size, rng);
	args->end = args->begin + size;
	return args;
}
void *prep_mergesort_args_handle(void *args)
{
	prep_mergesort_args_t *_args = (prep_mergesort_args_t *)args;
	return (void *)prep_mergesort_args(_args->size, _args->rng);
}
void cleanup_mergesort_args(mergesort_args_t *args)
{
	free(args->begin);
}
void cleanup_mergesort_args_handle(void *args)
{
	cleanup_mergesort_args((mergesort_args_t *)args);
	free(args);
}


void _mergesort_hybrid(int *tab, const int size, int *buffer, const int cutoff)
{
	if (size <= cutoff)
	{
		bubblesort(tab, size, buffer);
		return;
	}

	const int half = size / 2;
	int *mid = tab + half;
	_mergesort_hybrid(tab, half, buffer, cutoff);
	_mergesort_hybrid(mid, size - half, buffer, cutoff);

	int left = 0, right = 0;
	for (int i = 0; i < size; ++i)
	{
		if ((left < half && tab[left] < mid[right]) || right >= size - half)
		{
			buffer[i] = tab[left++];
		}
		else
		{
			buffer[i] = mid[right++];
		}
	}
	for (int i = 0; i < size; ++i)
	{
		tab[i] = buffer[i];
	}
}
void mergesort_hybrid(int *begin, int *end, const int cutoff)
{
	const int size = end - begin;
	int *buffer = (int *)malloc(size * sizeof(int));

	_mergesort_hybrid(begin, size, buffer, cutoff);

	free(buffer);
}
void mergesort_hybrid_handle(void *args)
{
	mergesort_hybrid_args_t *_args = (mergesort_hybrid_args_t *)args;
	mergesort_hybrid(_args->begin, _args->end, _args->cutoff);
}

int *random_int_table(const int size, std::mt19937_64 &rng)
{
	int *tab = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		tab[i] = i;
	}
	for (int i = 0; i < size; ++i)
	{
		int target = uid32(i, size - 1)(rng);
		std::swap(tab[i], tab[target]);
	}
	return tab;
}