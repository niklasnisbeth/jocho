#include "env.h"
#include "stdlib.h"
#include "math.h"

void
env_init ( struct env_t * env, float peak, float hold, float decay, float target, float slope )
{
  env_set_peak(env, peak);
  env_set_hold(env, hold);
  env_set_decay(env, decay);
  env_set_target(env, target);
  env_set_slope(env, slope);

  env->run = 0;
  env->cur = 0;
  env->state = ENV_STOPPED;
}

void 
env_trigger ( struct env_t *env )
{
  env->cur = env->peak;
  env->state = ENV_HOLD;
  env->run = 0;
}

static float
nonlinearize ( float val, float start, float end, float slope )
{
  float fx = (val*(1+slope))/(1+(slope*val));
  float sx = start+((end-start)*fx);
  return sx;
}

float
env_update ( struct env_t *env )
{
  switch (env->state)
  {
    case ENV_HOLD:
      if (env->run >= env->hold) {
        env->state = ENV_DECAY;
        env->run = 0;
        break;
      }
      else {
        env->run += 1 / (SAMPLERATE / 1000);
        break;
      }

    case ENV_DECAY:
      env->run += 1/( SAMPLERATE/1000 );
      if ((env->run/env->decay)>=1.f) {
        env->state = ENV_STOPPED;
        break;
      }
      else {
        env->cur = nonlinearize(env->run/env->decay, env->peak, env->target, env->slope);
        break;
      }

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
  if(decay>0) {
    env->decay = decay;
  }
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
  if(slope > -1.0 && slope <= 10.0) {
    env->slope = slope;
  }
}
