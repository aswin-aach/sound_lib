#include <stdio.h>
#include <stdlib.h>
#include "soundlib.h"

int main()
{
	char * filepath = "tests/samples/soundclip";
	Array samples = read_file(filepath);
	if ( samples.elements == NULL ) {
		fprintf(stderr,"Error with reading file");
		return 1;
	}
	fwrite(samples.elements,sizeof(sample_type),samples.length,stdout);
	free(samples.elements);
	return 0;
}
