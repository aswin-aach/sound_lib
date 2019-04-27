#include<stdio.h>
#include<stdlib.h>
#include"../soundlib.h"

void printarray(Array array) {
	sample_type* samples = array.elements;
	long length = array.length;
	for(long i = 0; i < length; i++){
		fprintf(stdout, "\n%d", samples[i]);
	}
}	
int equals(Array arr1, Array arr2){
	long length = arr1.length;
	if(length != arr2.length){
		return 0; // unequal
	}
	sample_type* arr1_elements = arr1.elements;
	sample_type* arr2_elements = arr2.elements;
	while(length--){
		if(arr1_elements[length] != arr2_elements[length]){
			return 0; // unequal
		}
	}
	return 1; // equal
}	
void test_simple(){
	Array testarray;
	sample_type samples[] = {1,2,3,4,5};
	testarray.elements = samples; 
	testarray.length = 5;
	Array reversed = reverse(testarray);
	Array rereversed = reverse(reversed);
	if(!equals(testarray, rereversed)){
		fprintf(stderr, "Simple TC failed\n");
	}
	else{
		fprintf(stdout, "Simple TC passed\n");
	}
	free(reversed.elements);
	free(rereversed.elements);
}
void test_from_file(){
	Array source = read_file("forward");
	Array reversed = reverse(source);
	fwrite(reversed.elements, sizeof(sample_type), reversed.length, stdout);
	free(source.elements);
	free(reversed.elements);
}
int main()
{
	//test_simple();
	//pipe output to a file, see if it's the reverse of "forward"
	test_from_file(); 
	return 0;
}


