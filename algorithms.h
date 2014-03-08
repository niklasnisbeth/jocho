#ifndef ALG_H
#define ALG_H

#include "voice.h"

#define NUM_ALGORITHMS 11

typedef float (*alg_f)( struct voice_t *voice);

float algorithm_1 ( struct voice_t *voice );   /* 1 -> 2 -> 3 -> 4o */
float algorithm_2 ( struct voice_t *voice );   /* 1,3 -> 2 -> 4o */
float algorithm_3 ( struct voice_t *voice );   /* 1 -> 2 -> 4o <-  3 */
float algorithm_4 ( struct voice_t *voice );   /* (3 <- 1 -> 2) -> 4o */
float algorithm_5 ( struct voice_t *voice );   /* 3o <- (1 -> 2) -> 4o */
float algorithm_6 ( struct voice_t *voice );   /* 1 -> 2 -> 3o | 4o */
float algorithm_7 ( struct voice_t *voice );   /* 1,2,3 -> 4o */
float algorithm_8 ( struct voice_t *voice );   /* 1 -> 2o | 3 -> 4o */
float algorithm_9 ( struct voice_t *voice );   /* 1 -> 2o3o4o */
float algorithm_10 ( struct voice_t *voice );  /* 1 -> 2o | 3o4o */
float algorithm_11 ( struct voice_t *voice );  /* 1o2o3o4o */

extern alg_f algorithms[NUM_ALGORITHMS];

#endif
