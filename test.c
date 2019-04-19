#include <stdio.h>
#include <stdlib.h>

#include "src/base_gen.h"

#define SAMPLE_RATE (44100)
#define HALF_SAMPLE_RATE (22050)
#define AUDIO_LENGTH (60)
#define NUM_SAMPLES (AUDIO_LENGTH * SAMPLE_RATE)

double get_samples(double *buf, int hz, int num_samples, wave_params *params) {
    int pos = 0;
    int sample = 0;

    double pmod = 0;
    double pinc = 0.0000005;
    double pthresh = 0.05;

    double cmod = 0;
    double cinc = 0.000001;
    double cthresh = 0.45;

    double lmod = 0;
    double linc = 0.00008;
    double lthresh = 0.45;

    double rmod = 0;
    double rinc = 0.00003;
    double rthresh = 0.45;

    for (sample = 0; sample < num_samples; sample++) {
        params->width = 0.5 + cmod;
        params->left_slope = 0.5 + lmod;
        params->right_slope = 0.5 + rmod;
        buf[sample] = get_wave_sample(pos, SAMPLE_RATE, params) * 0.75;

        pos += hz + (hz * pmod);
        //pos += hz;

        if (pos >= SAMPLE_RATE)
            pos -= SAMPLE_RATE;


        //pitch mod
        pmod += pinc;
        if (pmod > pthresh || pmod < -pthresh)
            pinc *= -1;

        //center mod
        cmod += cinc;
        if (cmod > cthresh || cmod < -cthresh)
            cinc *= -1;

        rmod += rinc;
        if (rmod > rthresh || rmod < -rthresh)
            rinc *= -1;

        lmod += linc;
        if (lmod > lthresh || lmod < -lthresh)
            linc *= -1;

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
    get_samples(&buf[0], 50, NUM_SAMPLES, &params);
    get_samples(&buf2[0], 55, NUM_SAMPLES, &params);

    for (int i = 0; i < NUM_SAMPLES; i++)
        out[i] = (buf[i] + buf2[i]) / 2;

    fwrite(out, 1, sizeof(double) * NUM_SAMPLES, fp);

    free(buf);
    return 0;
}

