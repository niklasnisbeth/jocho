#include <stdio.h>
#include <stdlib.h>

#include "voice.h"
#include "op.h"
#include "env.h"

typedef int16_t buffer_t[256];

#define SAMPLERATE 44100.f

void
fill_buffer ( buffer_t buffer, struct voice_t *voice )
{
  int pos;
  for (pos = 0; pos <= 255; pos++)
  {
    voice_update_ops(voice);
    voice_update_envs(voice);
    buffer[pos] = 32768 - voice->output_buffer*32768;
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
  FILE *fd = fopen("/tmp/tst.raw", "w"); 

  struct voice_t voice;

  voice_init(&voice);
  voice_trigger(&voice);

  while(1)
  {
    fill_buffer(*buffer, &voice);
    out(*buffer, fd); 
    if (voice.ops[0]->aenv->state == ENV_SUSTAIN)
      break;
  }

  return 0;
}

