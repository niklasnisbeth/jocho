#include <stdio.h>
#include <stdlib.h>

#include "synth.h"
#include "osc.h"
#include "env.h"

typedef int16_t buffer_t[256];

void
fill_buffer (buffer_t buffer, struct synth_t *synth)
{
  for (int pos = 0; pos <= 255; pos++)
  {
    synth_update_oscs(synth);
    printf("%f\n",synth->output_buffer);
    buffer[pos] = 32768 - synth->output_buffer*32768;
  }
}

size_t
out (buffer_t buffer, FILE *fd)
{
  size_t size = fwrite(buffer, sizeof(int16_t), 256, fd);
  
  return size;
}


int 
main(void)
{
  struct synth_t synth;

  struct osc_t osc1;
  struct osc_t osc2;

  buffer_t *buffer = malloc(sizeof(buffer_t));
  FILE *fd = fopen("/tmp/tst.raw", "w");

  int j = 0, dur = 200;

  synth.oscs[0] = &osc1;
  synth.oscs[1] = &osc2;
  synth.algorithm = &alg1;
  synth.output_buffer = 0.0; 

  osc_init_osc(synth.oscs[0], 443, 0.0, 0.4);
  osc_init_osc(synth.oscs[1], 438, 0.0, 0.4);

  osc_trigger(synth.oscs[0]);
  osc_trigger(synth.oscs[1]);

  while(j < dur)
  {
    fill_buffer(*buffer, &synth);
    out(*buffer, fd);
    j++;
  }

  return 0;
}

