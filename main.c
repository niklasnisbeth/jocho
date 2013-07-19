#include <stdio.h>
#include <stdlib.h>

#include "synth.h"
#include "op.h"
#include "env.h"

typedef int16_t buffer_t[256];

void
fill_buffer ( buffer_t buffer, struct synth_t *synth )
{
  for (int pos = 0; pos <= 255; pos++)
  {
    synth_update_ops(synth);
    buffer[pos] = 32768 - synth->output_buffer*32768;
  }
}

size_t
out ( buffer_t buffer, FILE *fd )
{
  size_t size = fwrite(buffer, sizeof(int16_t), 256, fd);
  
  return size;
}

void
update_controls ( struct synth_t *synth )
{
  synth->ops[0]->current.amp = synth->ops[0]->current.amp;
}


int 
main( void )
{
  struct synth_t synth;

  struct op_t op1;
  struct op_t op2;

  buffer_t *buffer = malloc(sizeof(buffer_t));
  FILE *fd = fopen("/tmp/tst.raw", "w");

  int j = 0, dur = 200;

  synth.ops[0] = &op1;
  synth.ops[1] = &op2;
  synth.algorithm = &alg1;
  synth.output_buffer = 0.0; 

  op_init_op(synth.ops[0], 443, 0.0, 0.4);
  op_init_op(synth.ops[1], 222, 0.0, 0.4);

  op_trigger(synth.ops[0]);
  op_trigger(synth.ops[1]);

  while(j < dur)
  {
    fill_buffer(*buffer, &synth);
    out(*buffer, fd);
    j++;
  }

  return 0;
}

