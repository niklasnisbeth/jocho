#include "algorithms.h"

float algorithm_1 ( struct voice_t *voice )   /* 1 -> 2 -> 3 -> 4o */
{
  float offset = 0;
  float output = 0;
  int i;

  for(i = 0; i < NUM_OPS-1; i++)
  {
    offset = op_cur_amp(&voice->ops[i])*op_wave_with_offset(&voice->ops[i], offset);
  }

  output = op_cur_amp(&voice->ops[NUM_OPS])*op_wave_with_offset(&voice->ops[NUM_OPS], offset);

  return output;
}

float algorithm_2 ( struct voice_t *voice )   /* 1,3 -> 2 -> 4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_3 ( struct voice_t *voice )   /* 1 -> 2 -> 4o <-  3 */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_4 ( struct voice_t *voice )   /* (3 <- 1 -> 2) -> 4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_5 ( struct voice_t *voice )   /* 3o <- (1 -> 2) -> 4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_6 ( struct voice_t *voice )   /* 1 -> 2 -> 3o | 4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_7 ( struct voice_t *voice )   /* 1,2,3 -> 4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_8 ( struct voice_t *voice )   /* 1 -> 2o | 3 -> 4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_9 ( struct voice_t *voice )   /* 1 -> 2o3o4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_10 ( struct voice_t *voice )  /* 0 -> 2o | 3o4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

float algorithm_11 ( struct voice_t *voice )  /* 1o2o3o4o */
{
  float offset = 0;
  float output = 0;

  return output;
}

