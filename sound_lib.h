#ifndef sound_lib_h
#define sound_lib_h

#define PAGE_SIZE 8192



page * get_new_page();

void shrink(int* s, long n_i, long n_f);




void print_sample_array(int * array, long length);





#endif
