#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifndef SYNTH_H
#define SYNTH_H

#include "env.h"
#include "osc.h"

#define NUM_OSCS 2

extern int32_t samplerate;
extern struct algorithm_t alg1;

enum osc_output_mode { OFF, ON }; 
 
struct algorithm_t { 
  enum osc_output_mode outputs[NUM_OSCS][NUM_OSCS + 1]; 
}; 

struct synth_t { 
  struct osc_t *oscs[NUM_OSCS]; 
  struct algorithm_t *algorithm; 
  double output_buffer;
}; 

void synth_update_oscs ( struct synth_t *synth );
double synth_wt_lookup ( double phase );

#endif
