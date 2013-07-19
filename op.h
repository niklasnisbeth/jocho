#ifndef OP_H
#define OP_H

#include "synth.h"

struct op_settings_t {
  float frequency;
  float phase;
  float amp;
};

struct op_t {
  struct op_settings_t base;
  struct op_settings_t current;
  int running;
};


void op_init_op ( struct op_t *op, float frequency, float phase, float amp );
void op_trigger ( struct op_t *op );
float op_phase_increment_of_next_sample ( struct op_t *op );
void op_update_phase ( struct op_t *op, float phase_increment );

#endif
