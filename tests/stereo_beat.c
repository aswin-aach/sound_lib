/*
 * Creates a track using an existing track of known length.
 * The path to the existing sample is relative to the project home directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include "soundlib.h"

#define SAMPLE_RATE 44100

int main()
{
    char *filepath = "tests/samples/NoiseBeat.raw";
    Array white_noise_8 = read_file(filepath),
          silence = create_array(1, sizeof(sample_type)),
          left_track = loop(silence, SAMPLE_RATE),
          right_track = loop(silence, SAMPLE_RATE),
          stereo;
    //left
    add(white_noise_8, left_track, 0);
    add(white_noise_8, left_track, SAMPLE_RATE / 4);
    add(white_noise_8, left_track, (SAMPLE_RATE / 4) + (SAMPLE_RATE / 8));
    add(white_noise_8, left_track, (SAMPLE_RATE / 2) + (SAMPLE_RATE / 8));
    add(white_noise_8, left_track, (SAMPLE_RATE / 2) + (SAMPLE_RATE / 4));
    //right
    add(white_noise_8, right_track, SAMPLE_RATE / 8);
    add(white_noise_8, right_track, SAMPLE_RATE / 2);
    add(white_noise_8, right_track, ((3 * SAMPLE_RATE) / 4) + (SAMPLE_RATE / 8));
    //combine
    stereo = loop(silence, 2 * SAMPLE_RATE);
    for (long i = 0; i < 2 * SAMPLE_RATE; i+=2) {
        ((sample_type *) stereo.elements)[i] = ((sample_type *) left_track.elements)[i/2];
        ((sample_type *) stereo.elements)[i+1] = ((sample_type *) right_track.elements)[i/2];
    }
    fwrite(stereo.elements, sizeof(sample_type), stereo.length, stdout);
    return 0;
}
