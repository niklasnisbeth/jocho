#include <stdio.h>
#include <stdlib.h>

#include "voice.h"
#include "op.h"
#include "env.h"
#include "wave.h"
#include "defs.h"

typedef int16_t buffer_t[256];

#define SINE_SIZE 1024
#define SAW_SIZE 3
#define TRI_SIZE 4

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


  struct voice_t voice;

  float *sinevals = malloc(sizeof(float)*(SINE_SIZE+1));
  wave_generate_sine(sinevals, SINE_SIZE); 
  struct wave_t sinetable;
  sinetable.vals = sinevals;
  sinetable.size = SINE_SIZE;

  float *sawvals = malloc(sizeof(float)*(SAW_SIZE+1));
  wave_generate_saw(sawvals, SAW_SIZE);
  struct wave_t sawtable;
  sawtable.vals = sawvals;
  sawtable.size = SAW_SIZE;

  /*
  float *trivals = malloc(sizeof(float)*(TRI_SIZE+1));
  wave_generate_triangle(trivals, TRI_SIZE);
  struct wave_t tritable;
  tritable.vals = trivals;
  tritable.size = TRI_SIZE;
  */

  struct wavetable_t wt;
  struct wave_t *waves[] = malloc(sizeof(struct wave_t *)*2);
  waves[0] = &sinetable;
  waves[1] = &sinetable;
  wavetable_init(&wt, &waves, 2);

  voice_init(&voice, &wt);
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

