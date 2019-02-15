#include "../soundlib.h"
#include<stdio.h>
#include<stdlib.h>

#define SAMPLE_RATE 44100

int main()
{
	char * filepath = "white_noise_fade_out";
	Array * white_noise_8 = (Array*)malloc(sizeof(Array));
	read_file(filepath, white_noise_8);
	Array* silence = (Array*)malloc(sizeof(Array));
	silence->elements = malloc(1 * sizeof(int));
	silence->length = 1;
	((int*) silence->elements)[0] = 0;
	Array* left_track = loop_samples(silence, SAMPLE_RATE);
	Array* right_track = loop_samples(silence, SAMPLE_RATE);
	
	add_samples(white_noise_8, left_track, 0);
	add_samples(white_noise_8, left_track, SAMPLE_RATE / 4);
	add_samples(white_noise_8, left_track, (SAMPLE_RATE / 4) + (SAMPLE_RATE / 8));
	add_samples(white_noise_8, left_track, (SAMPLE_RATE / 2) + (SAMPLE_RATE / 8));
	add_samples(white_noise_8, left_track, (SAMPLE_RATE / 2) + (SAMPLE_RATE / 4));
	
	add_samples(white_noise_8, right_track, SAMPLE_RATE / 8);
	add_samples(white_noise_8, right_track, SAMPLE_RATE / 2);
	add_samples(white_noise_8, right_track, ((3 * SAMPLE_RATE) / 4) + (SAMPLE_RATE / 8));
	
	Array* stereo = loop_samples(silence, 2 * SAMPLE_RATE);
	for (long i = 0; i < 2 * SAMPLE_RATE; i+=2) {
			((int*) stereo->elements)[i] = ((int*) left_track->elements)[i/2];
			((int*) stereo->elements)[i+1] = ((int*) right_track->elements)[i/2];
	}
	
	//stereo = loop_samples(stereo, 8 * SAMPLE_RATE);
	
	fwrite(stereo->elements,sizeof(int),stereo->length,stdout);
	
	return 0;
}
