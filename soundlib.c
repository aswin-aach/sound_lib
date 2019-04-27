#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soundlib.h"
Array create_array(long element_count, size_t element_size) {
	Array array;
	if (element_count < 1) {
		fprintf(stderr, "Failed to create array with %ld elements.\n", element_count);
		return array;
	}
	array.elements = malloc(element_count * element_size);
	array.length = element_count;
	return array;
}

Array read_file(char* file_path) {
	Array buffer;
	FILE* file_pointer = fopen(file_path, "rb");
	if(file_pointer == NULL) {
		fprintf(stderr, "Failed to open \"%s\".\n", file_path);
		return buffer;
	}
	fseek(file_pointer, 0, SEEK_END);
	long file_length = ftell(file_pointer);
	rewind(file_pointer);
	size_t sample_size = sizeof(sample_type);
	long sample_count = file_length / sample_size;
	buffer = create_array(sample_count, sample_size);
	fread(buffer.elements, sample_size, sample_count, file_pointer);
	fclose(file_pointer);
	return buffer;
}

Array read_tracked_file(char* file_path, int track_count) {
	Array track_array;
	Array interleaved_buffer = read_file(file_path);
	if (interleaved_buffer.elements == NULL) {
		fprintf(stderr, "Unable to process \"%s\".\n", file_path);
		return track_array;
	}
	long buffer_length = interleaved_buffer.length;
	long sample_count = buffer_length / track_count;
	size_t sample_size = sizeof(sample_type);
	track_array = create_array(track_count, sizeof(Array));
	Array* track = track_array.elements;
	for (int i = 0; i < track_count; i++) {
		track[i].elements = malloc(sample_count * sample_size);
		track[i].length = sample_count;
	}
	sample_type* sample = interleaved_buffer.elements;
	for (long i = 0; i < buffer_length; i++) {
		sample_type* current_track_sample = track[i % track_count].elements;
		current_track_sample[i / track_count] = sample[i];
	}
	free(interleaved_buffer.elements);
	return track_array;
}

static int is_invalid(Array array) {
	if (array.elements == NULL || array.length < 1) {
		fprintf(stderr, "Invalid array.\n");
		return 1;
	}
	return 0;
}

Array get_track(Array track_array, int track_index) {
	if (is_invalid(track_array)) {
		fprintf(stderr, "Invalid track array.\n");
		return track_array;
	}
	if (track_index < 0 || track_index > (track_array.length - 1)) {
		fprintf(stderr, "Invalid track index.\n");
		return track_array;
	}
	Array* track = track_array.elements;
	return track[track_index];
}

Array snip(Array sample_array, long start_index, long end_index) {
	if (is_invalid(sample_array) || start_index < 0 || end_index > sample_array.length - 1 || start_index > end_index) {
		fprintf(stderr, "Invalid input to snip().\n");
		return sample_array;
	}
	sample_type* source_sample = sample_array.elements;
	long new_length = end_index - start_index + 1;
	size_t sample_size = sizeof(sample_type);
	Array snipped_sample_array = create_array(new_length, sample_size);
	sample_type* snipped_sample = snipped_sample_array.elements;
	memcpy(snipped_sample, source_sample + start_index, new_length * sample_size);
	return snipped_sample_array;
}

Array loop(Array sample_array, long duration) {
	if (is_invalid(sample_array) || duration < 1) {
		fprintf(stderr, "Invalid input to loop().\n");
		return sample_array;
	}
	sample_type* sample = sample_array.elements;
	long length = sample_array.length;
	size_t sample_size = sizeof(sample_type);
	Array looped_sample_array = create_array(duration, sample_size);
	sample_type* looped_sample = looped_sample_array.elements;
	for (long i = 0; i < duration; i++) {
		looped_sample[i] = sample[i % length];
	}
	return looped_sample_array;
}

Array add(Array source, Array target, long offset) {
	if (is_invalid(source) || is_invalid(target) || target.length - offset < source.length) {
		fprintf(stderr, "Invalid input to add().\n");
		return source;
	}
	sample_type* source_sample = source.elements;
	sample_type* target_sample = target.elements;
	long source_length = source.length;
	long target_length = target.length;
	for (long i = 0; i < source_length; i++) {
		target_sample[i + offset] = target_sample[i + offset] + source_sample[i];
	}
	return target;
}

Array reverse(Array source) {
	if(is_invalid(source)) {
		fprintf(stderr, "Invalid input to reverse().\n");
		return source;
	}
	long length = source.length;
	Array target = create_array(length, sizeof(sample_type));
	sample_type* source_sample = source.elements;
	sample_type* target_sample = target.elements;
	while(length--) {
		*(target_sample++) = *(source_sample + length);
	}		
	return target;
}
