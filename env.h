#ifndef ENV_H
#define ENV_H

#include "synth.h"

struct env_t {
  int running;
  float peak; /* peak value multiple */
  float decay; /* decay time (ms) */
  float target; /* target value multiple */
  float cur; /* current value */
};

void env_init ( struct env_t *env, float peak, float decay, float targ );

void env_trigger ( struct env_t *env );

void env_finish ( struct env_t *env );

float env_update ( struct env_t *env );

#endif
