#include "osc.h"

int32_t wsize = 256;

struct 
osc_settings_t {
  double frequency;
  double phase;
  double amp;
};

struct 
osc_t {
  struct osc_settings_t base;
  struct osc_settings_t current;
  int running;
};

void 
osc_init_osc ( struct osc_t *osc, double frequency, double phase, double amp )
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

void 
osc_update_phase ( struct osc_t *osc )
{
  osc->current.phase += wsize / (samplerate / osc->current.frequency);

  if (osc->current.phase >= 1)
  {
    osc->current.phase = 0;
  }
}

