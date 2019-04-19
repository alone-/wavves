/*

    base_gen.h

    Fill buffers with basic waveforms.

*/

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

void buffer_wave(double *buf, int length, wave_params *params);
double get_wave_sample(int pos, int sample_rate, wave_params *params);

