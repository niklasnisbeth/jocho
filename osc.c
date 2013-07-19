#include "osc.h"
#include <stdio.h>

void 
osc_init_osc ( struct osc_t *osc, float frequency, float phase, float amp )
{
  osc->base.frequency = frequency;
  osc->base.amp = amp;
  osc->base.phase = phase;
}

void
osc_trigger ( struct osc_t *osc )
{
  osc->current.frequency = osc->base.frequency;
  osc->current.amp = osc->base.amp;
  osc->current.phase = osc->base.phase;
  osc->running = 1;
}

float
osc_phase_increment_of_next_sample ( struct osc_t *osc )
{
  return 1/(samplerate/osc->current.frequency);
}

void
osc_update_phase ( struct osc_t *osc, float phase_increment )
{
  osc->current.phase += phase_increment;

  if (osc->current.phase >= 1)
  {
    osc->current.phase = 0;
  } 
}
