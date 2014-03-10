#include "stdlib.h"
#include "env.h"
#include "math.h"

void
env_init ( struct env_t * env, float peak, float hold, float decay, float target, float slope )
{
  env->peak = peak;
  env->hold = hold;
  env->held = 0;
  env->decay = decay;
  env->target = target;
  env->slope = slope;

  env->cur = 0;
  env->state = ENV_STOPPED;
}

void 
env_trigger ( struct env_t *env )
{
  env->cur = env->peak;
  env->state = ENV_HOLD;
  env->held = 0;
}

static float
nonlinearize ( float val, float slope )
{
  return ((1+slope)*val)/(1+(slope*fabsf(val)));
}

float
env_update ( struct env_t *env )
{
  float delta = 0;

  switch (env->state)
  {
    case ENV_HOLD:
      if (env->held >= env->hold) {
        env->state = ENV_DECAY;
      }
      else {
        env->held += 1 / (SAMPLERATE / 1000);
      }
      break;

    case ENV_DECAY:
      delta = nonlinearize((env->peak - env->target) / ((env->decay + 0.01f) *  (SAMPLERATE / 1000)), env->slope);
      env->cur -= delta;
      if (env->cur <= 0) {
        env->state = ENV_STOPPED;
      }
      if ((env->peak > env->target && env->cur < env->target) || (env->peak < env->target && env->cur > env->target)) {
        env->state = ENV_SUSTAIN;
      }
      break;

    case ENV_SUSTAIN:
      break;

    case ENV_STOPPED:
      return 0;
  }

  return env->cur;
}
