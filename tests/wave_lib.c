#include<math.h>

void create_sine(int * wave, long s_rate, float freq, long n_s){
    for(int i = 0; i < n_s; i++) {
        *(wave + i) = sin(2 * M_PI * freq * (float) i / s_rate);
        printf("%d", *(wave + i));
    }
}
