#include "synth.h"
#include "stdio.h"

int32_t samplerate = 44100;

struct algorithm_t alg1 = {
  {
    {OFF,ON,OFF},
    {OFF,OFF,ON}
  }
};


void
synth_update_oscs ( struct synth_t *synth )
{
  int i, j;
  for (i = 0; i < NUM_OSCS; i++)
  {
    osc_update_phase(synth->oscs[i], osc_phase_increment_of_next_sample(synth->oscs[i]));
    for (j = 0; j < NUM_OSCS; j++)
    {
      if (synth->algorithm->outputs[i][j] == ON)
      {
        osc_update_phase(synth->oscs[j], synth_wt_lookup(synth->oscs[i]->current.phase));
      }
    }
    if (synth->algorithm->outputs[i][j] == ON)
    {
      synth->output_buffer += synth->oscs[i]->current.amp * synth_wt_lookup(synth->oscs[i]->current.phase);
    }
  }
}

double
synth_wt_lookup ( double phase )
{
  printf("%f\t", phase);
  return sin(phase * 2.0 * 3.14159);
}
