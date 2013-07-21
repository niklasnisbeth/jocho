#include <stdlib.h>
#include "op.h"

void 
op_init ( struct op_t *op, float frequency, float phase, float amp )
{
  op->aenv = malloc(sizeof(struct env_t));
  op->penv = malloc(sizeof(struct env_t));

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

  env_trigger(op->aenv);
  env_trigger(op->penv);

  op->running = 1;
}

float
op_phase_increment ( struct op_t *op )
{
  return 1/(SAMPLERATE/(op->current.frequency*op->penv->cur));
}

void
op_update_phase ( struct op_t *op, float phase_increment )
{
  op->current.phase += phase_increment;

  if (op->current.phase >= 1)
  {
    op->current.phase = 0;
  } 
}
