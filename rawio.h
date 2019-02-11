#ifndef raw_io_h
#define raw_io_h


typedef struct Array 
{
	void * elements;
	long length;
	
} Array;

void read_file(char * path, Array * buf); 


#endif 