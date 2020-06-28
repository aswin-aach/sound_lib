/* 
 * Creates a track with a sine wave of a certain frequency and writes to stdout. 
 * Pipe the output to some file in order to play
 */

#include <stdio.h>
#include <stdlib.h>
#include "soundlib.h"

#define SAMPLING_RATE 44100

Array create_sine(double amplitude_ratio, float freq, long number_of_samples);
long write_raw(Array array);

int main(void)
{
	Array sine_220 = create_sine(0.75, 220.0, SAMPLING_RATE * 10l);
	//Array sine_15b = create_sine(0.5, 15.0, SAMPLING_RATE * 10l);
	
	write_raw(sine_220);
	free(sine_220.elements);
	//free(sine_15b.elements);
	return 0;
}

Array create_sine(double amplitude_ratio, float freq, long number_of_samples){	
	sample_type  amplitude = amplitude_ratio * sample_upper_limit();
	Array sine_wave = sin_wave(amplitude, freq, number_of_samples, SAMPLING_RATE);

	return sine_wave;
}

long write_raw(Array array){
  return fwrite(array.elements, array.length,  sizeof(sample_type), stdout) / sizeof(sample_type);
}
		
