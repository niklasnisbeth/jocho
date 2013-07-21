#ifndef ENV_H
#define ENV_H

#include "synth.h"

enum env_state_t {
  ENV_STOPPED,
  ENV_HOLD,
  ENV_DECAY,
  ENV_SUSTAIN
};

struct env_t {
  enum env_state_t state;
  float peak; /* peak value multiple */
  float hold; /* hold time (ms) */
  float held;
  float decay; /* decay time (ms) */
  float target; /* target value multiple */
  float cur; /* current value */
};

void env_init ( struct env_t *env, float peak, float hold, float decay, float targ );

void env_trigger ( struct env_t *env );

void env_finish ( struct env_t *env );

float env_update ( struct env_t *env );

#endif
