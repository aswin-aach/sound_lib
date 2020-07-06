#include <stdlib.h>
#include <stdio.h>
#include "soundlib.h"

void print_array(Array a)
{
    for(long i = 0; i < a.length; i++) {
        printf("%d ", ((sample_type *) a.elements)[i]);
    }
    printf("\n");
}

int main()
{
    sample_type elements[] = {1, 2, 3, 4, 5, 6};
    long size = 6;
    Array sample_array;
    sample_array.elements = elements;
    sample_array.length = size;
    printf("original = ");
    print_array(sample_array);
    Array snipped = snip(sample_array, 1, 4);
    printf("snipped = ");
    print_array(snipped);
    Array looped = loop(snipped, 10);
    printf("looped = ");
    print_array(looped);
    Array other_snip = snip(sample_array, 5, 5);
    printf("other snip = ");
    print_array(other_snip);
    Array looped2 = loop(other_snip, 15);
    printf("other looped = ");
    print_array(looped2);
    Array sum = add(looped, looped2, 0);
    printf("sum = ");
    print_array(sum);
    free(snipped.elements);
    free(looped.elements);
    free(other_snip.elements);
    free(looped2.elements);
    return 0;
}
