#include <stdlib.h>
#include <math.h>
#include "op.h"

void 
op_init ( struct op_t *op, float frequency, float phase, float amp, struct wavetable_t *w )
{
  op_set_wavetable(op, w);
  op_set_frequency(op, frequency);
  op_set_amp(op, amp);
  op_set_phase(op, phase);
}

void
op_trigger ( struct op_t *op )
{
  op->current.frequency = op->base.frequency;
  op->current.amp = op->base.amp;
  op->current.phase = op->base.phase;

  env_trigger(&op->aenv);
  env_trigger(&op->penv);
  env_trigger(&op->wenv);

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
  return wavetable_lookup(op->wt, op->current.phase, op->wenv.cur);
}

float
op_wave_with_offset ( struct op_t *op, float offset )
{
  return wavetable_lookup_offset(op->wt, op->current.phase, op->wenv.cur, offset);
}

void 
op_set_frequency ( struct op_t *op, float frequency )
{
  op->base.frequency = frequency;
}

void 
op_set_phase ( struct op_t *op, float phase )
{
  if(phase <= 1.0 && phase >= 0) {
    op->base.phase = phase;
  }
}

void 
op_set_amp ( struct op_t *op, float amp )
{
  if(amp <= 1.0 && amp >= 0) {
    op->base.amp = amp;
  }
}

void
op_set_wavetable ( struct op_t *op, struct wavetable_t *wt )
{
  op->wt = wt;
}
