/*

   lfo.c

*/

#include "lfo.h"

void update_lfo(lfo *l) {
    l->mod += l->inc;

    if (l->mod > l->thresh) {
        l->mod = l->thresh;
        l->inc *= -1;
    }
    else if (l->mod < -l->thresh) {
        l->mod = -l->thresh;
        l->inc *= -1;
    }
}

void init_lfo(lfo *l, double offset, double inc, double thresh) {
    l->mod = offset;
    l->inc = inc;
    l->thresh = thresh;
}

