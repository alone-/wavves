#include <stdio.h>
#include <stdlib.h>

#include "base_gen.h"

int buffers_filled = 0;

double *square_buffer;
double *saw1_buffer;
double *saw2_buffer;
double *tri_buffer;
double *sin_buffer;
double *mtn_buffer;

void constrain_params(wave_params *params) {
    if (params->width > 1.0)
        params->width = 1.0;
    else if (params->width < 0.0)
        params->width = 0.0;

    if (params->left_slope > 1.0)
        params->left_slope = 1.0;
    else if (params->left_slope < 0.0)
        params->left_slope = 0.0;

    if (params->right_slope > 1.0)
        params->right_slope = 1.0;
    else if (params->right_slope < 0.0)
        params->right_slope = 0.0;
}

void buffer_wave(double *buf, int length, wave_params *params) {
    int half = length * params->width;
    int ls_start = half * params->left_slope;
    int rs_start = length - ((length - half) * params->right_slope);
    int i;

    for(i = 0; i < half; i++) {
        if (i > ls_start)
            buf[i] = -1 + (2 * ((double)(i - ls_start) / (double)(half - ls_start)));
        else
            buf[i] = -1;
    }
    for(i = half; i < length; i++) {
        if (i > rs_start)
            buf[i] = 1 - (2 * ((double)(i - rs_start) / (double)(length - rs_start)));
        else
            buf[i] = 1;
    }
}

double get_wave_sample(int pos, int sample_rate, wave_params *params) {
    constrain_params(params);

    pos = pos % sample_rate;
    
    // calculate wave shape params
    int half = sample_rate * params->width;
    int ls_start = half * params->left_slope;
    int rs_start = sample_rate - ((sample_rate - half) * params->right_slope);
    double sample = 0;

    if(pos < half) {
        if (pos > ls_start)
            sample =  -1 + (2 * ((double)(pos - ls_start) / (double)(half - ls_start)));
        else
            sample = -1;
    }
    else {
        if (pos > rs_start)
            sample = 1 - (2 * ((double)(pos - rs_start) / (double)(sample_rate - rs_start)));
        else
            sample = 1;
    }

    return sample;
}
