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

  /*int i = 0; 
  for (i = 0; i < NUM_OPS; i++)
  {
    op_update_phase(synth->ops[i], op_phase_increment_of_next_sample(synth->ops[i]));
    synth->output_buffer += synth->ops[i]->current.amp * synth_wt_lookup(synth->ops[i]);
  } */

  op_update_phase(synth->ops[1], op_phase_increment(synth->ops[1]));
  op_update_phase(synth->ops[0], op_phase_increment(synth->ops[0]));
  synth->output_buffer += (synth->ops[0]->current.amp * synth->ops[0]->aenv->cur) *
    synth_wt_lookup(synth->ops[0]->current.phase + 
        ((synth->ops[1]->current.amp * synth->ops[1]->aenv->cur) * synth_wt_lookup(synth->ops[1]->current.phase)));
}

void
synth_update_envs ( struct synth_t *synth )
{
  int i;
  for (i=0; i < NUM_OPS; i++)
  {
    env_update(synth->ops[i]->aenv);
    env_update(synth->ops[i]->penv);
  }
}


float
synth_wt_lookup ( float phase )
{
  return sinf(2.0 * 3.14159 * phase);
}
