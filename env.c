#include "env.h"

void
env_init ( struct env_t * env, float peak, float decay, float target )
{
  env->peak = peak;
  env->decay = decay;
  env->target = target;
  env->cur = 0;
  env->running = 0;
}

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

float
env_update ( struct env_t *env )
{
  if (env->running)
  {
    float delta = (env->peak - env->target) / (env->decay * (samplerate / 1000));
    env->cur -= delta;
  }

  if ((env->peak > env->target && env->cur < env->target) || (env->peak < env->target && env->cur > env->target))
  {
    env_finish(env);
  }

  return env->cur;
}
