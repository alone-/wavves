/*

   lfo.h

*/

#ifndef LFO_H_
#define LFO_H_

typedef struct lfo {
    double mod;
    double inc;
    double thresh;
} lfo;


void update_lfo(lfo *l);
void init_lfo(lfo *l, double offset, double inc, double thresh);

#endif

