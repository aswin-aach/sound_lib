#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 32000

void create_sine(int * wave, long s_rate, float freq, long n_s){
    for(int i = 0; i < n_s; i++) {
        *(wave + i) = AMPLITUDE * sin(2 * M_PI * freq * (float) i / s_rate);
        printf("%d", *(wave + i));
    }
}

int main()
{
    long n_s = 3 * SAMPLE_RATE;
    float f = 440 * 3;
    int* wave = (int*) malloc(sizeof(int) * n_s);
    create_sine(wave, (long) SAMPLE_RATE, f, n_s);
    free(wave);
    return 0;
}
