#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifndef SYNTH_H
#define SYNTH_H

#include "env.h"
#include "op.h"

#define NUM_OPS 2

extern float samplerate;
extern struct algorithm_t alg1;

enum op_output_mode { OFF, ON }; 
 
struct algorithm_t { 
  enum op_output_mode outputs[NUM_OPS][NUM_OPS + 1]; 
}; 

struct synth_t { 
  struct op_t *ops[NUM_OPS]; 
  struct algorithm_t *algorithm; 
  float output_buffer;
}; 

void synth_update_ops ( struct synth_t *synth );
void synth_update_envs ( struct synth_t *synth );
float synth_wt_lookup ( float phase );

#endif
