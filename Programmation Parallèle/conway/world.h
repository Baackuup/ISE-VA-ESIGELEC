/*
Copyright (C) 2024 Romain Rossi
ESIGELEC - Parallel Programming
Adapted by Mauricio Kugler
Laboratories 2 & 3 - Threads & CUDA
*/

#ifndef __WORLD_H__
#define __WORLD_H__
/*
	Conway's Game Of Life world model implementation

	This files implements the Game Of Life world data structure and associated functions. 
	It defines a fixed and finite dimension square world, with square cells and warping on the boundaries (aka "Torus world").
*/
#include <stdlib.h>
#include <stdio.h>

// Type definition for a world cell data type (must be 1 byte size)
typedef unsigned char cell_t;

// Game of life world data structure and type definition
typedef struct
{
	size_t generation;
	size_t size;
	cell_t data[];
} world_t;

// Functions to operate on worlds structures

/* Create a new world data structure and return a pointer to it
	world_size : size of the created world (it will be a torus of world_size*world_size cell counts)
*/
world_t * world_create( size_t world_size )
{
	world_t * new_world = NULL;
	new_world = (world_t *) malloc ( sizeof(world_t) + (world_size * world_size * sizeof(cell_t)) );
	new_world->generation = 0;
	new_world->size = world_size;
	return new_world;
}

/* Free world's memory
*/
void world_delete( world_t * w )
{
	if ( w != NULL ) {
		free( w );
	}
}

/* Get the value of a cell
*/
cell_t get_cell(world_t *w, size_t x, size_t y)
{
	cell_t val = 0;
	if ( (w!=NULL) && (x < w->size) && (y < w->size ) ) {
		val = w->data[x + y*w->size];
	}
	return val;
}

/* Set the value of a cell
*/
void set_cell(world_t *w, size_t x, size_t y, cell_t new_val)
{
	if ( (w!=NULL) && (x < w->size) && (y < w->size ) ) {
		w->data[x + y*w->size] = new_val;
	}
}

/* Add a glider seed to the world
*/
void add_glider(world_t *w, size_t x, size_t y)
{
	set_cell(w,x+2,y+1,1);
	set_cell(w,x+3,y+2,1);
	set_cell(w,x+3,y+3,1);
	set_cell(w,x+2,y+3,1);
	set_cell(w,x+1,y+3,1);
}

/* Clear all cells
*/
void world_clear(world_t *w)
{
	if ( (w!=NULL) && (w->size > 0 ) ) {
		for (size_t y=0; y<w->size; y++) {
			for (size_t x=0; x<w->size; x++) {
				set_cell(w,x,y,0);
			}
		}
	}
}

/* Swap the two worlds for next generation
*/
void swap_worlds( world_t **world_a, world_t **world_b )
{
	world_t *w;
	w = *world_b;
	*world_b = *world_a;
	*world_a = w;
}

#endif // __WORLD_H__
