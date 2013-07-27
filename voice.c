#include "voice.h"

void
voice_init ( struct voice_t *voice )
{
  voice->algorithm = 1;
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
voice_next_sample ( struct voice_t *voice )
{
  voice->output_buffer = 0;

  for (int i=0; i<NUM_OPS; i++)
  {
    op_update_phase(&voice->ops[i]);
  }

  /* ALGO_1 */
  float offset;
  offset = op_cur_amp(&voice->ops[1])*op_wave(&voice->ops[1]);
  voice->output_buffer += op_cur_amp(&voice->ops[0]) * op_wave_with_offset(&voice->ops[0], offset);
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
