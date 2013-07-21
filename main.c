#include <stdio.h>
#include <stdlib.h>

#include "synth.h"
#include "op.h"
#include "env.h"

typedef int16_t buffer_t[256];

void
fill_buffer ( buffer_t buffer, struct synth_t *synth )
{
  int pos;
  for (pos = 0; pos <= 255; pos++)
  {
    synth_update_ops(synth);
    synth_update_envs(synth);
    buffer[pos] = 32768 - synth->output_buffer*32768;
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
  struct synth_t synth;

  struct op_t op1;
  struct op_t op2;

  struct env_t op1_aenv;
  struct env_t op1_penv;
  struct env_t op2_aenv;
  struct env_t op2_penv;

  buffer_t *buffer = malloc(sizeof(buffer_t));
  FILE *fd = fopen("/tmp/tst.raw", "w"); 

  int j = 0, dur = 200;

  synth.ops[0] = &op1;
  synth.ops[0]->aenv = &op1_aenv;
  synth.ops[0]->penv = &op1_penv;
  synth.ops[1] = &op2;
  synth.ops[1]->aenv = &op2_aenv;
  synth.ops[1]->penv = &op2_penv;
  synth.algorithm = &alg1;
  synth.output_buffer = 0.0f; 

  op_init_op(synth.ops[0], 440, 0.0f, 0.6f);
  env_init(synth.ops[0]->penv, 1.0, 200, 0.5);
  env_init(synth.ops[0]->aenv, 1.0, 999, 0.0);

  op_init_op(synth.ops[1], 440, 0.0f, 0.4f);
  env_init(synth.ops[1]->penv, 1.0, 900, 2.1);
  env_init(synth.ops[1]->aenv, 1.0, 500, 1.0);

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

