#include <stdio.h>

#include "base_gen.h"
#include "wave_server.h"

void write_single_sample(FILE * stream, int pos, int sample_rate, wave_params *params) {
    fprintf(stream, "%lf", get_wave_sample(pos, sample_rate, params));
}
