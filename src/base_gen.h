/*

    base_gen.h

    Fill buffers with basic waveforms, or get a single sample.

*/

#ifndef BASE_GEN_H
#define BASE_GEN_H

typedef struct wave_params {
    float width;
    float left_slope;
    float right_slope;
} wave_params;


typedef enum wave_t {
    WAVE_SQR,
    WAVE_SAW1,
    WAVE_SAW2,
    WAVE_TRI,
    WAVE_SIN,
    WAVE_MTN
} wave_t;

// TODO: overload buffer_wave to take wave_t and set appropriate params based on type
// TODO: give buffer_wave and get_wave_sample more specific names to avoid conflicts
void buffer_wave(double *buf, int length, wave_params *params);
double get_wave_sample(int pos, int sample_rate, wave_params *params);

#endif
