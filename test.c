#include <stdio.h>
#include <stdlib.h>

#include "src/base_gen.h"
#include "src/lfo.h"

#define SAMPLE_RATE (44100)
#define HALF_SAMPLE_RATE (22050)
#define AUDIO_LENGTH (1)
#define NUM_SAMPLES (AUDIO_LENGTH * SAMPLE_RATE)

double get_samples(double *buf, int hz, int num_samples, wave_params *params) {
    int pos = 0;
    int sample = 0;

    for (sample = 0; sample < num_samples; sample++) {
        buf[sample] = get_wave_sample(pos, SAMPLE_RATE, params) * 0.75;

        pos += hz;

        if (pos >= SAMPLE_RATE)
            pos -= SAMPLE_RATE;
    }
}

int main() {
    FILE *fp;
    double *buf = malloc(sizeof(double) * NUM_SAMPLES);

    wave_params params;
    params.width = 0.5;
    params.left_slope = 0.0;
    params.right_slope = 1.0;

    fp = fopen("square.raw", "w");
    get_samples(&buf[0], 200, NUM_SAMPLES, &params);

    fwrite(buf, 1, sizeof(double) * NUM_SAMPLES, fp);

    free(buf);
    return 0;
}

