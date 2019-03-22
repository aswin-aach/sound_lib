#ifndef soundlib_h
#define soundlib_h

/*
Holds a generic array and its length. Mainly used for processing raw sample data.
*/
typedef struct Array {
	void* elements;
	long length;
} Array;

/*
The data type used for representing samples throughout.
*/
typedef int sample_type;

/*
Returns an empty array with element_count elements.
*/
Array create_array(long element_count, size_t element_size);

/*
Reads a file containing raw samples from its path and returns an array of samples.
*/
Array read_file(char* file_path);

/*
Reads a file containing track_count interleaved tracks of raw samples and returns an array of tracks, each of which is an array of samples.
*/
Array read_tracked_file(char* file_path, int track_count);

/*
Returns the sample array at track_index in an array of tracks.
*/
Array get_track(Array track_array, int track_index);

/*
Takes an array and returns a new snipped array from start_index to end_index.
*/
Array snip(Array sample_array, long start_index, long end_index);

/*
Takes an array and returns a new looped array that repeats for the given duration.
*/
Array loop(Array sample_array, long duration);

/*

*/
Array add(Array source, Array target, long offset);

#endif
