#include "synth.h"

#ifndef OSC_H
#define OSC_H

struct osc_settings_t {
  double frequency;
  double phase;
  double amp;
};

struct osc_t {
  struct osc_settings_t base;
  struct osc_settings_t current;
  int running;
};


void osc_init_osc ( struct osc_t *osc, double frequency, double phase, double amp );
void osc_trigger ( struct osc_t *osc );
double osc_phase_increment_of_next_sample ( struct osc_t *osc );
void osc_update_phase ( struct osc_t *osc, double phase_increment );

#endif
