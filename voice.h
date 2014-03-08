#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifndef VOICE_H
#define VOICE_H

#include "env.h"
#include "op.h"

#define NUM_OPS 4

struct voice_t { 
  struct op_t ops[NUM_OPS]; 
  int algorithm;
  float output_buffer;
}; 

void voice_init ( struct voice_t *voice );
void voice_trigger ( struct voice_t *voice );
float voice_next_sample ( struct voice_t *voice );
void voice_update_envs ( struct voice_t *voice );

#endif
