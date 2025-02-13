/*
Copyright (C) 2024 Romain Rossi
ESIGELEC - Parallel Programming
Adapted by Mauricio Kugler
Laboratory 1 - Benchmarks
*/

#ifndef _PERFTIMER_H_
#define _PERFTIMER_H_

// #if defined(_MSC_VER)
// #include <BaseTsd.h>
// typedef SSIZE_T ssize_t;
// #endif

#include <iostream>
#include <chrono>
#include <string>

using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::time_point;

//simple precise timer
class perftimer
{
private:
	std::chrono::time_point< high_resolution_clock, duration<double, typename high_resolution_clock::period> > _t_start, _t_end;

public:
	void start(void)
	{
		_t_start = high_resolution_clock::now();
	}

	void stop(void)
	{
		_t_end = high_resolution_clock::now();
	}

	void print_time(std::string message)
	{
		typedef duration<double, typename high_resolution_clock::period> Cycle;
		//get clock ticks
		auto ticks_per_iter = Cycle( _t_end - _t_start );
		std::cout << ticks_per_iter.count() << " ticks <=> ";
		//convert to real time units
		std::cout << duration_ns() << " ns\n";
	}

	ssize_t duration_ns()
	{
		typedef duration<double, typename high_resolution_clock::period> Cycle;
		typedef duration<unsigned long long, std::nano> nanoseconds;
		//get clock ticks
		auto ticks_per_iter = Cycle( _t_end - _t_start );
		//convert to real time units
		return std::chrono::duration_cast<nanoseconds>( ticks_per_iter ).count();
	}
};

#endif
