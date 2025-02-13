/*
Copyright (C) 2024 Romain Rossi
ESIGELEC - Parallel Programming
Adapted by Mauricio Kugler
Laboratories 2 & 3 - Threads & CUDA
*/

#ifndef __PLOT_H__
#define __PLOT_H__

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "world.h"

// Macro to clear screen
#define clrscr() printf("\033[H\033[J")

// Maximal ASCII world size
const unsigned int MAX_ASCII = 64;

/* Shows current world in ASCII
*/
void world_show_ascii(world_t *w)
{
	if ( (w!=NULL) && (w->size > 0 ) ) {
		printf("\nGeneration %ld\n", w->generation);
		for (size_t y=0; y<w->size; y++) {
			for (size_t x=0; x<w->size; x++) {
				if( get_cell(w,x,y) == 0 ) {
					putchar('.');
				} else {
					putchar('X');
				}
			}
			putchar('\n');
		}
	}
	fflush(stdout);
}

/* Save world as an image file
*/
void dump_world_image(world_t *w, char *filename)
{
	cv::Mat image( w->size, w->size, CV_8UC3 );

	for ( int i=0; i < w->size; i++) {
		for ( int j=0; j < w->size; j++ ) {
			int cell = get_cell(w, i, j);
			unsigned char val = (cell == 0) ? 0 : 255;
			image.at<cv::Vec3b>(j,i)[0] = val; //B
			image.at<cv::Vec3b>(j,i)[1] = val; //G
			image.at<cv::Vec3b>(j,i)[2] = val; //R
		}
	}

	cv::imwrite(filename,image);
}

#endif // __PLOT_H__