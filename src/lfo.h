/*

   lfo.h

*/


typedef struct lfo {
    double mod;
    double inc;
    double thresh;
} lfo;


void update_lfo(lfo *l);
void init_lfo(lfo *l, double offset, double inc, double thresh);
