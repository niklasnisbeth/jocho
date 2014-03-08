#include "algorithms.h"

alg_f algorithms[NUM_ALGORITHMS] = {
  &algorithm_1,
  &algorithm_2,
  &algorithm_3,
  &algorithm_4,
  &algorithm_5,
  &algorithm_6,
  &algorithm_7,
  &algorithm_8,
  &algorithm_9,
  &algorithm_10,
  &algorithm_11};

float algorithm_1 ( struct voice_t *voice )   /* 1 -> 2 -> 3 -> 4o */
{
  float offset = 0.f;
  float output = 0.f;

  //assumes NUM_OPS = 4;

  offset = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);
  offset = op_cur_amp(&voice->ops[1])*op_wave_with_offset(&voice->ops[1], offset);
  offset = op_cur_amp(&voice->ops[2])*op_wave_with_offset(&voice->ops[2], offset);

  output = op_cur_amp(&voice->ops[3])*op_wave_with_offset(&voice->ops[3], offset);

  return output;
}

float algorithm_2 ( struct voice_t *voice )   /* 1,3 -> 2 -> 4o */
{
  float offset1 = 0;
  float offset2 = 0;
  float offset3 = 0;
  float output = 0;

  //assumes NUM_OPS = 4...

  offset1 = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);
  offset2 = op_cur_amp(&voice->ops[1])*op_wave(&voice->ops[1]);
  
  offset3 = op_cur_amp(&voice->ops[2])*op_wave_with_offset(&voice->ops[2], offset1+offset2);

  output = op_cur_amp(&voice->ops[3])*op_wave_with_offset(&voice->ops[3], offset3);

  return output;
}

float algorithm_3 ( struct voice_t *voice )   /* 1 -> 2 -> 4o <-  3 */
{
  float offset1 = 0;
  float offset2 = 0;
  float offset3 = 0;
  float output = 0;

  //assumes NUM_OPS = 4...

  offset1 = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);
  offset2 = op_cur_amp(&voice->ops[1])*op_wave_with_offset(&voice->ops[1], offset1);
  
  offset3 = op_cur_amp(&voice->ops[2])*op_wave(&voice->ops[2]);

  output = op_cur_amp(&voice->ops[3])*op_wave_with_offset(&voice->ops[3], offset2+offset3);

  return output;
}

float algorithm_4 ( struct voice_t *voice )   /* (3 <- 1 -> 2) -> 4o */
{
  float offset1 = 0;
  float offset2 = 0;
  float offset3 = 0;
  float output = 0;

  // assumes NUM_OPS = 4...

  offset1 = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);
  
  offset2 = op_cur_amp(&voice->ops[1])*op_wave_with_offset(&voice->ops[1], offset1);
  offset3 = op_cur_amp(&voice->ops[2])*op_wave_with_offset(&voice->ops[2], offset1);

  output = op_cur_amp(&voice->ops[3])*op_wave_with_offset(&voice->ops[3], offset2+offset3);

  return output;
}

float algorithm_5 ( struct voice_t *voice )   /* 3o <- (1 -> 2) -> 4o */
{
  float offset1 = 0;
  float offset2 = 0;
  float output = 0;

  // assumes NUM_OPS = 4...

  offset1 = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);
  
  offset2 = op_cur_amp(&voice->ops[1])*op_wave_with_offset(&voice->ops[1], offset1);

  output += 0.5f*op_cur_amp(&voice->ops[2])*op_wave_with_offset(&voice->ops[2], offset2);
  output += 0.5f*op_cur_amp(&voice->ops[3])*op_wave_with_offset(&voice->ops[3], offset2);

  return output;
}

float algorithm_6 ( struct voice_t *voice )   /* 1 -> 2 -> 3o | 4o */
{
  float offset1 = 0;
  float offset2 = 0;
  float output = 0;

  offset1 = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);
  offset2 = op_cur_amp(&voice->ops[1])*op_wave_with_offset(&voice->ops[1], offset1);

  output += 0.5f*op_cur_amp(&voice->ops[2])*op_wave_with_offset(&voice->ops[2], offset2);
  output += 0.5f*op_cur_amp(&voice->ops[3])*op_wave(&voice->ops[3]);

  return output;
}

float algorithm_7 ( struct voice_t *voice )   /* 1,2,3 -> 4o */
{
  float offset1 = 0;
  float offset2 = 0;
  float offset3 = 0;
  float output = 0;

  offset1 = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);
  offset2 = op_cur_amp(&voice->ops[1])*op_wave(&voice->ops[1]);
  offset3 = op_cur_amp(&voice->ops[2])*op_wave(&voice->ops[2]);

  output += op_cur_amp(&voice->ops[3])*op_wave_with_offset(&voice->ops[3], offset1+offset2+offset3);

  return output;
}

float algorithm_8 ( struct voice_t *voice )   /* 1 -> 2o | 3 -> 4o */
{
  float offset = 0;
  float output = 0;

  offset = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);

  output += 0.5*op_cur_amp(&voice->ops[1])*op_wave_with_offset(&voice->ops[1], offset); 

  offset = op_cur_amp(&voice->ops[2])*op_wave(&voice->ops[2]);

  output += 0.5*op_cur_amp(&voice->ops[3])*op_wave_with_offset(&voice->ops[3], offset); 
  
  return output;
}

float algorithm_9 ( struct voice_t *voice )   /* 1 -> 2o3o4o */
{
  float offset = 0;
  float output = 0;

  offset = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);

  output += 0.33f*op_cur_amp(&voice->ops[1])*op_wave_with_offset(&voice->ops[1], offset); 
  output += 0.33f*op_cur_amp(&voice->ops[2])*op_wave_with_offset(&voice->ops[2], offset); 
  output += 0.33f*op_cur_amp(&voice->ops[3])*op_wave_with_offset(&voice->ops[3], offset); 

  return output;
}

float algorithm_10 ( struct voice_t *voice )  /* 1 -> 2o | 3o4o */
{
  float offset = 0;
  float output = 0;

  offset = op_cur_amp(&voice->ops[0])*op_wave(&voice->ops[0]);

  output += 0.33f*op_cur_amp(&voice->ops[1])*op_wave_with_offset(&voice->ops[1], offset); 
  output += 0.33f*op_cur_amp(&voice->ops[2])*op_wave(&voice->ops[2]);
  output += 0.33f*op_cur_amp(&voice->ops[2])*op_wave(&voice->ops[2]);

  return output;
}

float algorithm_11 ( struct voice_t *voice )  /* 1o2o3o4o */
{
  float output = 0;
  int i;

  for(i = 0; i < NUM_OPS; i++)
  {
    output += 0.25f*op_cur_amp(&voice->ops[i])*op_wave(&voice->ops[i]);
  }

  return output;
}

