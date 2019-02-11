#ifndef smpop_h
#define smpop_h

#include "rawio.h"

/*
	Takes an integer array and returns a new snipped integer array from
	start_index to end_index.
*/
Array* snip_samples(Array* sample_array, long start_index, long end_index);

/*
	Takes an integer array and returns a new looped integer array that repeats
	the original elements in order for as many integers as duration.
*/
Array* loop_samples(Array* sample_array, long duration);

/*
	Takes two integer arrays and returns a new integer array whose elements are
	the sums of the respective elements of the input arrays.
*/
Array* add_samples(Array* source_sample_array, Array* target_sample_array);

#endif
