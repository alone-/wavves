#include <stdio.h>

#include "src/base_gen.h"

#define HZ (600)
#define SAMPLE_RATE (44100)
#define HALF_SAMPLE_RATE (22050)
#define AUDIO_LENGTH (2)
#define NUM_SAMPLES (AUDIO_LENGTH * SAMPLE_RATE)

double get_samples(double *buf, double *wave_buf, int hz, int num_samples, wave_params *params) {
    int pos = 0;
    int sample = 0;

    double pmod = 0;
    double pinc = 0.000001;
    double pthresh = 0.01;

    double cmod = 0;
    double cinc = 0.01;
    double cthresh = 0.1;

    for (sample = 0; sample < num_samples; sample++) {
        params->right_slope = 0.5 + cmod;
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

    }
}

int main() {
    FILE *fp;
    double wave_buf[SAMPLE_RATE];
    double buf[NUM_SAMPLES];

    wave_params params;
    params.width = 0.5;
    params.left_slope = 0.0;
    params.right_slope = 1.0;

    fp = fopen("square.raw", "w");
    get_samples(&buf[0], &wave_buf[0], 200, NUM_SAMPLES, &params);
    fwrite(buf, 1, sizeof(double) * NUM_SAMPLES, fp);
    get_samples(&buf[0], &wave_buf[0], 100, NUM_SAMPLES, &params);
    fwrite(buf, 1, sizeof(double) * NUM_SAMPLES, fp);

    return 0;
}

