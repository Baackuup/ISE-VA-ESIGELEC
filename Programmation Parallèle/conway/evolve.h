/*
Copyright (C) 2024 Romain Rossi
ESIGELEC - Parallel Programming
Adapted by Mauricio Kugler
Laboratories 2 & 3 - Threads & CUDA
*/

#ifndef __EVOLVE_H__
#define __EVOLVE_H__

#include "world.h"

unsigned char count_alive_neighbours(world_t *w, int x, int y)
{
	// The world geometry is a torus with no boundaries
	// while it is not possible to get a cell out of the defined world size,
	// right neigbours of a cell on the rightmost border is column0 and left neighbour on cell in column0 is the rightmost column
	// the same for top/bottom cells
	unsigned char n=0;
	size_t nx, ny;

	for (int j=y-1; j<=y+1; j++) {
		for (int i=x-1; i<=x+1; i++) {
			if (i==x && j==y) {
				continue; // the cell itself doesn't count
			}

			// Check X coordinate and wrap around the boundary
			if ( i < 0 ) {
				nx = w->size-1;
			} else if ( i >= w->size ) {
				nx = 0;
			} else {
				nx = i;
			}

			// Check the Y coordinate and wrap around the boundary
			if ( j < 0 ) {
				ny = w->size-1;
			} else if ( j>= w->size ) {
				ny = 0;
			} else {
				ny = j;
			}

			if (get_cell(w,nx,ny) != 0) {
				n++;
			}
		}
	}

	return n;
}

void world_evolve( world_t *prev, world_t *next)
{
	if (prev && next && (next->size == prev->size)) {
		for (size_t y=0; y<prev->size; y++) {			//parallelize!
			for (size_t x=0; x<prev->size; x++) {		//parallelize!
				unsigned char n = count_alive_neighbours(prev, x, y);

				if (get_cell(prev,x,y) != 0 ) { //alive
					if (n==2 || n==3) {
						set_cell(next,x,y,1);
					} else {
						set_cell(next,x,y,0);
					}
				} else { //dead
					if (n==3) {
						set_cell(next,x,y,1);
					} else {
						set_cell(next,x,y,0);
					}
				}
			}
		}
	}

	next->generation = prev->generation + 1;
}

#endif // __EVOLVE_H__
