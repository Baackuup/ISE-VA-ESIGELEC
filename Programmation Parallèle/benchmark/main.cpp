/*
Copyright (C) 2024 Romain Rossi
ESIGELEC - Parallel Programming
Adapted by Mauricio Kugler
Laboratory 1 - Benchmarks
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>

#include "perftimer.h"
#include "benchmark.h"

//run the full benchmark once for a given datasize
static void run_once(int32_t *data, ssize_t data_size, std::ostream &s)
{
	perftimer t;
    
	//initialization
	t.start();
		init_rand(data,(int32_t)data_size);
	t.stop();
	
	//print init time
	s << data_size << "," << t.duration_ns();

	//run the benchmarked function
	t.start();		
		/////////////////////////////////////////////////////////
		//Call benchmark functions here!
		int32_t max = find_max_array(data,(int32_t)data_size);
		/////////////////////////////////////////////////////////
		std::cerr << "Datasize " << data_size << " / Max : " << max << std::endl;
	t.stop();
	
	//print run time
	s << "," << t.duration_ns() << std::endl;
}

int main()
{
	const int32_t data_size_max = 5000;					//max number of data cells
	const int32_t data_size_step = data_size_max / 100;	//step between benchmarks (e.g. 100 steps)

	//data array
	int32_t *data = new int32_t[data_size_max];

	//create output file with benchmarks results
	std::fstream fs;
	fs.open("out.csv", std::fstream::out);
	
	//write columns headers
	fs << "data_size" << "," << "init time (ns)" << "," << "runtime (ns)" << std::endl;

	//perform multiple benchmarks with different data sizes
	for(ssize_t data_size = 1; data_size < data_size_max ; data_size += data_size_step) {
		run_once(data, data_size, fs);
	}

	//cleanup
	fs.close();
	delete[] data;
}
