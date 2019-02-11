#include "rawio.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	char * filepath = "soundclip";
	Array * samples = (Array*)malloc(sizeof(Array));
	read_file(filepath, samples);
	
	//printf("samples length after read file = %d\n",samples->length);
	
	fwrite(samples->elements,sizeof(int),samples->length,stdout);
	free(samples->elements);
	free(samples);
	return 0;
}