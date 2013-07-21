#include "env.h"
#include "defs.h"

#ifndef OP_H
#define OP_H

struct op_settings_t {
  float frequency;
  float phase;
  float amp;
};

struct op_t {
  struct op_settings_t base;
  struct op_settings_t current;
  struct env_t aenv;
  struct env_t penv;
  int running;
};


void op_init ( struct op_t *op, float frequency, float phase, float amp );
void op_trigger ( struct op_t *op );
float op_update_phase ( struct op_t *op );
float op_cur_amp ( struct op_t *op );
float op_wave ( struct op_t *op );
float op_wave_with_offset ( struct op_t *op, float offset );

#endif
