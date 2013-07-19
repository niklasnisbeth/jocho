#ifndef OSC_H
#define OSC_H

#include "synth.h"

struct osc_settings_t {
  float frequency;
  float phase;
  float amp;
};

struct osc_t {
  struct osc_settings_t base;
  struct osc_settings_t current;
  int running;
};


void osc_init_osc ( struct osc_t *osc, float frequency, float phase, float amp );
void osc_trigger ( struct osc_t *osc );
float osc_phase_increment_of_next_sample ( struct osc_t *osc );
void osc_update_phase ( struct osc_t *osc, float phase_increment );

#endif
