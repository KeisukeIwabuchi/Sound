#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "wave.h"

int main(void)
{
    MONO_PCM pcm;
    int n;
    double a, f0;

    pcm.fs = 8000;
    pcm.bits = 16;
    pcm.length = pcm.fs * 1;
    pcm.s = calloc(pcm.length, sizeof(double));

    a = 0.5;
    f0 = 1000;
    for (n = 0; n < pcm.length; n++) {
        pcm.s[n] = a * sin(2.0 * M_PI * f0 * n / pcm.fs);
    }

    for (n = 0; n < pcm.fs * 0.01; n++) {
        pcm.s[n] *= (double)n / (pcm.fs * 0.01);
        pcm.s[pcm.length - n - 1] *= (double)n / (pcm.fs * 0.01);
    }

    mono_wave_write(&pcm, "ex1.wav");

    free(pcm.s);

    return 0;
}