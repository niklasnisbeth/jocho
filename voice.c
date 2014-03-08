#include "voice.h"
#include "algorithms.h"

void
voice_init ( struct voice_t *voice )
{
  voice->algorithm = 3;
  int i = 0;
  for (i = 0; i<NUM_OPS-1; i++)
  {
    op_init(&voice->ops[i], 110, 0.05f, 0.0f);
    env_init(&voice->ops[i].aenv, 1.0, 20, 1500, 0.0);
    env_init(&voice->ops[i].penv, 1.0, 0, 0, 1.0);
  }
  op_init(&voice->ops[2], 220, 0.0f, 0.2f);
  env_init(&voice->ops[2].aenv, 1.0, 10, 100, 0.0);
  env_init(&voice->ops[2].penv, 1.0, 50, 100, 0.4);
  op_init(&voice->ops[3], 80, 0.1f, 1.0f);
  env_init(&voice->ops[3].aenv, 1.0, 40, 750, 0.0);
  env_init(&voice->ops[3].penv, 2.0, 10, 300, 1.0);
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


float
voice_next_sample ( struct voice_t *voice )
{
  voice->output_buffer = 0;

  for (int i=0; i<NUM_OPS; i++)
  {
    op_update_phase(&voice->ops[i]);
  }

  return (*algorithms[voice->algorithm])(voice);

  /* 
  float offset;
  offset = op_cur_amp(&voice->ops[1])*op_wave(&voice->ops[1]);
  voice->output_buffer += op_cur_amp(&voice->ops[0]) * op_wave_with_offset(&voice->ops[0], offset);
  */ 
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
