#include "stdlib.h"
#include "env.h"
#include "math.h"

void
env_init ( struct env_t * env, float peak, float hold, float decay, float target, float slope )
{
  env_set_peak(env, peak);
  env_set_hold(env, hold);
  env_set_decay(env, decay);
  env_set_target(env, target);
  env_set_slope(env, slope);

  env->held = 0;
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

void 
env_set_peak ( struct env_t *env, float peak )
{
  if(peak >= -1.0 && peak <= 1.0) {
    env->peak = peak;
  }
}

void 
env_set_hold ( struct env_t *env, float hold )
{
  env->hold = hold;
}

void 
env_set_decay ( struct env_t *env, float decay ) 
{
  env->decay = decay;
}

void 
env_set_target ( struct env_t *env, float target )
{
  if(target >= -1.0 && target <= 1.0) {
    env->target = target;
  } 
}

void 
env_set_slope ( struct env_t *env, float slope )
{
  if(slope > -1.0 && slope <= 3.0) {
    env->slope = slope;
  }
}
