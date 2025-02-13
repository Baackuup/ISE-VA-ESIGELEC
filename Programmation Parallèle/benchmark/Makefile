# Copyright (C) 2024 Romain Rossi \
ESIGELEC - Parallel Programming \
Adapted by Mauricio Kugler \
Laboratory 1 - Benchmarks

CC := g++
CCFLAGS := -Wall -Wextra #-ggdb
PROJECT := benchmark

$(PROJECT): main.cpp benchmarked.h perftimer.h
	$(CC) $(FLAGS) $< -o $@

clean :
	rm -f $(PROJECT)