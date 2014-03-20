#ifndef ENV_H
#define ENV_H

#include "defs.h"

enum env_settable_param_t {
  ENV_PEAK_VAL,
  ENV_HOLD_TIME,
  ENV_DECAY_TIME,
  ENV_TARGET_VAL,
  ENV_SLOPE_COEF,
  ENV_NUM_SETTABLE_PARAMS
};

enum env_state_t {
  ENV_STOPPED,
  ENV_HOLD,
  ENV_DECAY
};

struct env_t {
  enum env_state_t state;
  float peak; /* peak value multiple */
  float hold; /* hold time (ms) */
  float run; /* ticks run */
  float decay; /* decay time (ms) */
  float target; /* target value multiple */
  float cur; /* current value */
  float slope; /* slope time */
};

void env_init ( struct env_t *env, float peak, float hold, float decay, float targ, float slope );

void env_trigger ( struct env_t *env );

void env_finish ( struct env_t *env );

float env_update ( struct env_t *env );

void env_set_peak ( struct env_t *env, float peak );
void env_set_hold ( struct env_t *env, float hold );
void env_set_held ( struct env_t *env, float held );
void env_set_decay ( struct env_t *env, float decay ); 
void env_set_target ( struct env_t *env, float target );
void env_set_cur  ( struct env_t *env, float cur );
void env_set_slope ( struct env_t *env, float slope );


#endif
