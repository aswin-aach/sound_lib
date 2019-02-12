#include "smpop.h"
#include<stdlib.h>
#include<stdio.h>

int main() {
	int elements[] = {1, 2, 3, 4, 5, 6};
	long size = 6;
	Array* sample_array = (Array*) malloc(sizeof(Array));
	sample_array->elements = elements;
	sample_array->length = size;
	Array* snipped = snip_samples(sample_array, 1, 4);
	Array* looped = loop_samples(snipped, 10);
	Array* other_snip = snip_samples(sample_array, 5, 5);
	Array* looped2 = loop_samples(other_snip, 15);
	Array* sum = add_samples(looped, looped2);
	for (long i = 0; i < sum->length; i++) {
		printf("%d ", ((int*) sum->elements)[i]);
	}
	printf("\n");
	return 0;
}
