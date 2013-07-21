#include <stdlib.h>
#include <math.h>
#include "op.h"

void 
op_init ( struct op_t *op, float frequency, float phase, float amp )
{
  op->base.frequency = frequency;
  op->base.amp = amp;
  op->base.phase = phase;
}

void
op_trigger ( struct op_t *op )
{
  op->current.frequency = op->base.frequency;
  op->current.amp = op->base.amp;
  op->current.phase = op->base.phase;

  env_trigger(&op->aenv);
  env_trigger(&op->penv);

  op->running = 1;
}

float
op_update_phase ( struct op_t *op )
{
  op->current.phase += 1/(SAMPLERATE/(op->current.frequency*op->penv.cur));

  if (op->current.phase >= 1)
  {
    op->current.phase = 0;
  } 

  return op->current.phase;
}

float
op_cur_amp ( struct op_t *op )
{
  return op->current.amp * op->aenv.cur;
}

float
op_wave ( struct op_t *op )
{
  return sinf(2.0 * 3.14159 * op->current.phase);
}

float
op_wave_with_offset ( struct op_t *op, float offset )
{
  return sinf(2.0 * 3.14159 * (op->current.phase + offset));
}

