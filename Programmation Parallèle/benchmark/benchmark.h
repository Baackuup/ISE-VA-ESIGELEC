/*
Copyright (C) 2024 Romain Rossi
ESIGELEC - Parallel Programming
Adapted by Mauricio Kugler
Laboratory 1 - Benchmarks
*/

#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <random>

//initialize an array of length 'n', each array element value will be set to the index
//data: pointer to the array, n: size of the array
void init_n( int32_t *data, const int32_t n )
{
	for(int32_t i = 0; i < n; i++) {
		data[i] = i;
	}
}

//initialize an array of length 'n', each array element value will be set with a random value
//data: pointer to the array, n: size of the array
void init_rand(int32_t *data, const int32_t n)
{
	srand(33);    
	for(int32_t i = 0; i < n; i++) {
		data[i] = (int32_t)round(rand()%999);
	}
}

//counts and returns the number of dividers of the argument
int count_nb_div(int32_t N)
{
	int32_t div, ctr2, nb_div = 2;
	for(div = 1; div < N; div++) {
		for(ctr2 = div; ctr2 < N; ctr2++) {
			if((div * ctr2) == N) {
				if(div == ctr2) {
					nb_div++;
				}
				else {
					nb_div += 2;
				}
			}
		}
	}
	return nb_div;
}

/////////////////////////////////////////////////
// data-processing functions to be benchmarked
/////////////////////////////////////////////////

//process the sum of all elements of the array
int sum_array(int32_t *data, const int32_t n)
{
	int c = 0;
	for(int32_t i = 0; i < n; i++) {
		c += data[i];
	}
	return c;
}

//count the occurences of a value in the array
int count_occurences_array(int32_t *data, const int32_t n, const int32_t val)
{
    int c = 0;
    for(int32_t i = 0; i < n; i++) {
        if(data[i] == val) {
            c += 1;
        }
    }
    return c;
}

//find the maximum value in an array
int32_t find_max_array(int32_t *data, const int32_t n)
{
    int32_t max = INT32_MIN;
    for(int32_t i = 0; i < n; i++) {
        if(data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

//count the number of occurencies of each array value
void frequencies_array(int32_t *data, const int32_t n)
{
    int32_t * array_copy = new int32_t[n];
    for(int32_t i=0; i<n; i++) {
        array_copy[i] = data[i];
    }
    for(int32_t i=0; i<n; i++) {
        data[i] = count_occurences_array(array_copy, n, array_copy[i]);
    }
    delete[] array_copy;
}

//find the number of divider in the array
void nbdiv_array(int32_t *data, const int32_t n)
{
    int32_t * array_copy = new int32_t[n];
    for(int32_t i=0; i<n; i++) {
        array_copy[i] = data[i];
    }
    for(int32_t i=0; i<n; i++) {
        data[i] = count_nb_div(array_copy[i]);
    }
    delete[] array_copy;
}

#endif
