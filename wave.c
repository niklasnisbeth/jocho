#include <stdlib.h>
#include <math.h>
#include "wave.h"
#include "defs.h"
#include "interpolate.c"
#include <stdio.h>

float 
wave_lookup_offset(struct wave_t *wave, float phase, float offset)
{
  float real_phase = phase+offset;
  if(real_phase<0.f) {
    real_phase = 1+real_phase;
  }
  return wave_lookup(wave, real_phase);
}

float 
wave_lookup(struct wave_t *wave, float phase)
{
  unsigned int low = phase*wave->size;
  unsigned int high = low+1;
  float rem = (phase*wave->size)-low;

  float val1 = wave->vals[high];
  float val2 = wave->vals[low];

  return lin_interpolate(val1, val2, rem);
}

void
wave_generate_sine(float *wave, unsigned int table_size)
{
  float step = 1.f/table_size;
  unsigned int i;
  for(i = 0; i<=table_size; i++) { 
    wave[i] = sinf((i*step)*PI*2.f);
  }
}

void
wave_generate_saw(float *wave, unsigned int table_size)
{
  float step = 1.f/table_size;
  unsigned int i;
  for (i = 0; i<=table_size; i++) {
    wave[i] = 1-(i*step*2);
  }
}

void
wave_generate_triangle(float *wave, unsigned int table_size)
{
  float step = 1.f/(table_size/2);
  unsigned int i;
  for (i = 0; i<=table_size/2; i++) {
    wave[i] = 1-(i*step*2);
  }
  for (i = 1; i<=table_size/2; i++) {
    wave[(table_size/2)+i] = wave[(table_size/2)-i];
  }
}
