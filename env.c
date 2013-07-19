#include "env.h"

void 
env_trigger ( struct env_t *env )
{
  env->cur = env->peak;
  env->running=1;
}


void 
env_finish ( struct env_t *env )
{
  env->running = 0;
}

int32_t 
env_update ( struct env_t *env )
{
  int32_t delta = (env->peak - env->targ) / (env->decay * (samplerate / 1000));
  env->cur -= delta;

  return env->cur;
}

