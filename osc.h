#include "synth.h"

#ifndef OSC_H
#define OSC_H

#include "synth.h"

struct osc_settings_t;
struct osc_t;

void osc_init_osc ( struct osc_t *osc, double frequency, double phase, double amp );
void osc_trigger ( struct osc_t *osc );
void osc_update_phase ( struct osc_t *osc );

#endif
