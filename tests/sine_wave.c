#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "soundlib.h"

#define SAMPLING_RATE 44100

Array create_sine(double amplitude_ratio, float freq, long number_of_samples);
long write_raw(Array array);

int main(void)
{
	Array sine_440 = create_sine(0.5, 440.0, SAMPLING_RATE * 10l);
	Array sine_430 = create_sine(0.5, 430.0, SAMPLING_RATE * 10l);
	
	printf("%d bytes were printed", write_raw(add(sine_440, sine_430, 0)));
	free(sine_440.elements);
	free(sine_430.elements);
	return 0;
}

Array create_sine(double amplitude_ratio, float freq, long number_of_samples){
	Array sine_wave = create_array(number_of_samples, sizeof(sample_type));
	long index;
	double amplitude = amplitude_ratio * ((1 << (8 * sizeof(sample_type))) - 1);
	sample_type *elements = sine_wave.elements;
	
	for(index = 0; index < sine_wave.length; ++index){
		*(elements + index) = amplitude * sin((2 * M_PI * freq * index ) / SAMPLING_RATE);
	}
	return sine_wave;
}

long write_raw(Array array){
	return fwrite(array.elements, array.length,  sizeof(sample_type), stdout) / sizeof(sample_type);
}
		
