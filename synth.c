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
synth_update_oscs ( struct synth_t *synth )
{
  synth->output_buffer = 0;

  int i = 0; 
  for (i = 0; i < NUM_OSCS; i++)
  {
    osc_update_phase(synth->oscs[i], osc_phase_increment_of_next_sample(synth->oscs[i]));
    synth->output_buffer += synth->oscs[i]->current.amp * synth_wt_lookup(synth->oscs[i]);
  }
}

float
synth_wt_lookup ( struct osc_t *osc )
{
  return sinf(2.0 * 3.14159 * osc->current.phase);
}
