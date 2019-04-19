#include <stdio.h>
#include <stdlib.h>

#include "src/base_gen.h"
#include "src/lfo.h"

#define SAMPLE_RATE (44100)
#define HALF_SAMPLE_RATE (22050)
#define AUDIO_LENGTH (5)
#define NUM_SAMPLES (AUDIO_LENGTH * SAMPLE_RATE)

double get_samples(double *buf, int hz, int num_samples, wave_params *params) {
    int pos = 0;
    int sample = 0;

    lfo pitch_lfo;
    init_lfo(&pitch_lfo, 0, 0.00005, 0.01);

    lfo width_lfo;
    init_lfo(&width_lfo, 0, 0.00001, 0.1);

    lfo left_lfo;
    init_lfo(&left_lfo, 0, 0.00001, 0.005);

    lfo right_lfo;
    init_lfo(&right_lfo, 0.01, 0.00001, 0.004);

    for (sample = 0; sample < num_samples; sample++) {
        params->width = 0.5 + width_lfo.mod;
        params->left_slope = 0.5 + left_lfo.mod;
        params->right_slope = 0.5 + right_lfo.mod;
        buf[sample] = get_wave_sample(pos, SAMPLE_RATE, params) * 0.75;

        pos += hz + (hz * pitch_lfo.mod);

        if (pos >= SAMPLE_RATE)
            pos -= SAMPLE_RATE;

        update_lfo(&pitch_lfo);
        update_lfo(&width_lfo);
        update_lfo(&right_lfo);
        update_lfo(&left_lfo);
    }
}

int main() {
    FILE *fp;
    double *buf = malloc(sizeof(double) * NUM_SAMPLES);
    double *buf2 = malloc(sizeof(double) * NUM_SAMPLES);
    double *out = malloc(sizeof(double) * NUM_SAMPLES);

    wave_params params;
    params.width = 0.5;
    params.left_slope = 0.0;
    params.right_slope = 1.0;

    fp = fopen("square.raw", "w");
    get_samples(&buf[0], 500, NUM_SAMPLES, &params);
    get_samples(&buf2[0], 505, NUM_SAMPLES, &params);

    for (int i = 0; i < NUM_SAMPLES; i++)
        //out[i] = (buf[i] + buf2[i]) / 2;
        out[i] = (buf[i] * buf2[i]);

    fwrite(out, 1, sizeof(double) * NUM_SAMPLES, fp);

    free(buf);
    return 0;
}

