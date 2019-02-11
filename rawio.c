#include "rawio.h"
#include<stdio.h>
#include<stdlib.h>

void read_file(char * path, Array * buf)
{
	FILE *file_pointer;
	long filelen;
	file_pointer = fopen(path,"rb");
	long bufsize = 0;
	
	if(file_pointer == NULL)
	{
		printf( "%s file failed to open.\n",path ) ; 
		buf = NULL;
		return;
	}

	//FILE *fileptr;
	//char *buffer;
	//long filelen;

	//fileptr = fopen("myfile.txt", "rb");  // Open the file in binary mode
	fseek(file_pointer, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(file_pointer);             // Get the current byte offset in the file
	rewind(file_pointer);                      // Jump back to the beginning of the file
	
	buf->elements = malloc(filelen); // 
	fread(buf->elements, sizeof(int), filelen/sizeof(int), file_pointer); // Read in the entire file
	buf->length = filelen/sizeof(int);
	//fclose(fileptr); // Close the file
	//free_page_list(head);
	fclose(file_pointer);
}