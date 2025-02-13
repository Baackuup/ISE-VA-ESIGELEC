# Copyright (C) 2024 Romain Rossi \
ESIGELEC - Parallel Programming \
Adapted by Mauricio Kugler \
Laboratories 2 & 3 - Threads & CUDA

CC := g++
CCFLAGS := -Wall -Wextra #-ggdb
CFLAGS  := -g --std=c++11 `pkg-config --cflags opencv4`
LDFLAGS := `pkg-config --libs opencv4`
PROJECT := conway

$(PROJECT): conway.c evolve.h world.h
	$(CC) $(FLAGS) $< $(CFLAGS) $(LDFLAGS) -o $@

clean :
	rm -f $(PROJECT)