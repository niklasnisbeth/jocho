#include "synth.h"
#include "osc.h"
#include "env.h"

int32_t samplerate = 44100;

enum osc_output_mode { OFF, ON };

struct algorithm_t {
  enum osc_output_mode outputs[NUM_OSCS][NUM_OSCS + 1];
};

struct algorithm_t alg1 = {
  {
    {OFF,ON,OFF},
    {OFF,OFF,ON}
  }
};

struct synth_t {
  struct osc_t *oscs[NUM_OSCS];
  struct algorithm *algorithm;
};

void
synth_update_oscs ( struct synth_t *synth )
{
  int i;
  for (i = 0; i < NUM_OSCS; i++)
  {
    osc_update_phase(synth->oscs[i]);
  }
}

