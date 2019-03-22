#include<stdlib.h>
#include<stdio.h>
#include "../soundlib.h"

int main() {
	int elements[] = {1, 2, 3, 4, 5, 6};
	long size = 6;
	Array sample_array;
	sample_array.elements = elements;
	sample_array.length = size;
	Array snipped = snip(sample_array, 1, 4);
	Array looped = loop(snipped, 10);
	Array other_snip = snip(sample_array, 5, 5);
	Array looped2 = loop(other_snip, 15);
	Array sum = add(looped, looped2, 0);
	for (long i = 0; i < sum.length; i++) {
		printf("%d ", ((int*) sum.elements)[i]);
	}
	printf("\n");
	return 0;
}
