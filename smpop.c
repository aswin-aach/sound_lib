#include "smpop.h"
#include <stdio.h>
#include <stdlib.h>

static int is_valid(Array* sample_array) {
	if (sample_array == NULL) {
		return 0;
	}
	int* sample = (int*) sample_array->elements;
	long length = sample_array->length;
	if (sample == NULL || length == 0) {
		return 0;
	}
	return 1;
}

Array* snip_samples(Array* sample_array, long start_index, long end_index) {
	if (!is_valid(sample_array) || start_index < 0 ||
		end_index > sample_array->length - 1 || start_index > end_index) {
		fprintf(stderr, "Invalid input to snip_samples().\n");
		exit(-1);
	}
	int* sample = (int*) sample_array->elements;
	long new_length = end_index - start_index + 1;
	Array* snipped_sample_array = (Array*) malloc(sizeof(Array));
	snipped_sample_array->elements = malloc(new_length * sizeof(int));
	snipped_sample_array->length = new_length;
	for (long i = 0; i < new_length; i++) {
		((int*) snipped_sample_array->elements)[i] = sample[start_index + i];
	}
	return snipped_sample_array;
}

Array* loop_samples(Array* sample_array, long duration) {
	if (!is_valid(sample_array) || duration < 1) {
		fprintf(stderr, "Invalid input to loop_samples().\n");
		exit(-1);
	}
	int* sample = (int*) sample_array->elements;
	long length = sample_array->length;
	Array* looped_sample_array = (Array*) malloc(sizeof(Array));
	looped_sample_array->elements = malloc(duration * sizeof(int));
	looped_sample_array->length = duration;
	for (long i = 0; i < duration; i++) {
		((int*) looped_sample_array->elements)[i] = sample[i % length];
	}
	return looped_sample_array;
}

Array* add_samples(Array* source_sample_array, Array* target_sample_array) {
	if (!is_valid(source_sample_array) || !is_valid(target_sample_array) ||
		target_sample_array->length < source_sample_array->length) {
		fprintf(stderr, "Invalid input to add_samples().\n");
		exit(-1);
	}
	int* source_sample = (int*) source_sample_array->elements;
	int* target_sample = (int*) target_sample_array->elements;
	long source_length = source_sample_array->length;
	long new_length = target_sample_array->length;
	Array* summed_sample_array = (Array*) malloc(sizeof(Array));
	summed_sample_array->elements = malloc(new_length * sizeof(int));
	summed_sample_array->length = new_length;
	for (long i = 0; i < new_length; i++) {
		if (i > source_length - 1) {
			((int*) summed_sample_array->elements)[i] = target_sample[i];
		}
		else {
			((int*) summed_sample_array->elements)[i] = target_sample[i] +
				source_sample[i];
		}
	}
	return summed_sample_array;
}

