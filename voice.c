#include "voice.h"
#include "stdio.h"

void
voice_init ( struct voice_t *voice )
{
  int i;
  for (i = 0; i<NUM_OPS; i++)
  {
    op_init(&voice->ops[i], 440, 0.0f, 1.0f);
    env_init(&voice->ops[i].aenv, 1.0, 20, 500, 0.0);
    env_init(&voice->ops[i].penv, 1.0, 0, 0, 1.0);
  }
}

void
voice_trigger (struct voice_t *voice )
{
  int i;
  for (i = 0; i<NUM_OPS; i++)
  {
    op_trigger(&voice->ops[i]);
  }
}


void
voice_update_ops ( struct voice_t *voice )
{
  voice->output_buffer = 0;

  op_update_phase(&voice->ops[1], op_phase_increment(&voice->ops[1]));
  op_update_phase(&voice->ops[0], op_phase_increment(&voice->ops[0]));
  voice->output_buffer += (voice->ops[0].current.amp * voice->ops[0].aenv.cur) *
    voice_wt_lookup(voice->ops[0].current.phase + 
        ((voice->ops[1].current.amp * voice->ops[1].aenv.cur) * voice_wt_lookup(voice->ops[1].current.phase)));
}

void
voice_update_envs ( struct voice_t *voice )
{
  int i;
  for (i=0; i<NUM_OPS; i++)
  {
    env_update(&voice->ops[i].aenv);
    env_update(&voice->ops[i].penv);
  }
}


float
voice_wt_lookup ( float phase )
{
  return sinf(2.0 * 3.14159 * phase);
}
