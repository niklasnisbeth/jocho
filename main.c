#include <stdio.h>
#include <stdlib.h>

#include "voice.h"
#include "op.h"
#include "env.h"
#include "wt.h"
#include "defs.h"

typedef int16_t buffer_t[256];

#define SINE_SIZE 1024

void
assert(int res)
{
  if (!res)
  {
    printf("assertion failed\n");
  }
}

void
fill_buffer ( buffer_t buffer, struct voice_t *voice )
{
  int pos;
  float sample;
  for (pos = 0; pos <= 255; pos++)
  {
    voice_update_envs(voice);
    sample = voice_next_sample(voice);
#ifdef DEBUG
    assert(sample >= -1.0f && sample <= 1.0f);
#endif
    buffer[pos] = (int16_t)(sample*32767.f);
  }
}

size_t
out ( buffer_t buffer, FILE *fd )
{
  size_t size = fwrite(buffer, sizeof(int16_t), 256, fd);
  
  return size;
}

int 
main( void )
{
  buffer_t *buffer = malloc(sizeof(buffer_t));
  FILE *fd = fopen("tst.raw", "w"); 

  float *sinevals = malloc(sizeof(float)*SINE_SIZE);

  struct voice_t voice;

  wt_generate_sine(sinevals, SINE_SIZE);

  struct wavetable_t sinetable;
  sinetable.vals = sinevals;
  sinetable.size = SINE_SIZE;

  voice_init(&voice, &sinetable);
  voice_trigger(&voice);

  while(1)
  {
    fill_buffer(*buffer, &voice);
    out(*buffer, fd); 
    if (voice.ops[3].aenv.state == ENV_STOPPED)
      break;
  }

  return 0;
}

