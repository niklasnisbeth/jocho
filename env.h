#ifndef ENV_H
#define ENV_H

#include "synth.h"

struct env_t {
  int running;
  int32_t peak;
  int32_t decay;
  int32_t targ;
  int32_t cur;
};

void env_trigger ( struct env_t *env );

void env_finish ( struct env_t *env );

int32_t env_update ( struct env_t *env );

#endif
