#ifndef soundlib_h
#define soundlib_h

/*
	Holds a generic array with length for processing samples of custom sizes.
*/
typedef struct Array {
	void* elements;
	long length;
} Array;

/*
	Reads a file containing raw samples into an array.
*/
void read_file(char* path, Array* buffer);

/*
	Takes an array and returns a new snipped array from start_index to
	end_index.
*/
Array* snip_samples(Array* sample_array, long start_index, long end_index);

/*
	Takes an array and returns a new looped array that repeats the original
	elements in order for the given duration.
*/
Array* loop_samples(Array* sample_array, long duration);

/*
	Takes two arrays and returns a new array whose elements are the sums of the
	respective elements of the input arrays.
*/
Array* add_samples(Array* source_sample_array, Array* target_sample_array);

#endif
