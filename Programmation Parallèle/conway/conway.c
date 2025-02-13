/*
Copyright (C) 2024 Romain Rossi
ESIGELEC - Parallel Programming
Adapted by Mauricio Kugler
Laboratories 2 & 3 - Threads & CUDA
*/

#include <stdio.h>
#include <unistd.h>

#include "world.h"
#include "evolve.h"
#include "plot.h"

int main(int argc, char **argv)
{
	// Read input arguments
	int W = (argc > 1) ? atoi(argv[1]) : 64;		// world size (square)
	int C = (argc > 2) ? atoi(argv[2]) : 1000;		// number of generations
	char *filename = (argc > 3) ? argv[3] : NULL;	// dump file

	// Create world variables
	world_t *world_a, *world_b;
	world_a = world_create(W);
	world_b = world_create(W);
	world_clear(world_a);

	// Add world seed
	add_glider(world_a, 0, 0);

	// Evolve world over generations
	for (int i = 0; i < C; i++) {
		if(W <= MAX_ASCII) {
			clrscr();
			world_show_ascii(world_a);
			usleep(50000);
		}

		world_evolve(world_a, world_b);
		swap_worlds(&world_a, &world_b);
	}

	// Dump world image
	if(filename != NULL) {
		dump_world_image(world_a,filename);
	}

	// Release memory
	world_delete( world_a );
	world_delete( world_b );
}
