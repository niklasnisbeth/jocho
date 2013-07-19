#include "synth.h"
#include "stdio.h"

float samplerate = 44100.0;

struct algorithm_t alg1 = {
  {
    {OFF,OFF,OFF},
    {OFF,OFF,ON}
  }
};


void
synth_update_ops ( struct synth_t *synth )
{
  synth->output_buffer = 0;

  int i = 0; 
  for (i = 0; i < NUM_OPS; i++)
  {
    op_update_phase(synth->ops[i], op_phase_increment_of_next_sample(synth->ops[i]));
    synth->output_buffer += synth->ops[i]->current.amp * synth_wt_lookup(synth->ops[i]);
  }
}

float
synth_wt_lookup ( struct op_t *op )
{
  return sinf(2.0 * 3.14159 * op->current.phase);
}
