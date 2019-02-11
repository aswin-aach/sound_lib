#include "sound_lib.h"
#include<stdlib.h>
#include<stdio.h>



void shrink(int* s, long n_i, long n_f)
{
    int r_s = n_i / n_f;

    for (int i = 0; i < n_i; i++)
    {
        if (i < n_f)
        {
            *(s + i) = *(s + (r_s * i));
        }
        else
        {
            *(s + i) = 0;
        }
    }
}








void print_sample_array(int * array, long length)
{
	for(long i = 0; i<length; i++)
	{
		printf("%d",i);
	}
}	





