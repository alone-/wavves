
#ifndef WAVE_SERVER_H
#define WAVE_SERVER_H

#include <stdio.h>

typedef struct wave_params wave_params;

void write_single_sample(FILE * stream, int pos, int sample_rate, wave_params *params);

#endif

