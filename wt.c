#include <stdlib.h>
#include <math.h>
#include "wt.h"
#include "defs.h"
#include <stdio.h>

float 
wt_lookup_offset(struct wavetable_t *table, float phase, float offset)
{
  float real_phase = phase+offset;
  if(real_phase<0.f) {
    real_phase = 1+real_phase;
  }
  return wt_lookup(table, real_phase);
}

float 
wt_lookup(struct wavetable_t *table, float phase)
{
  float hi;
  float rem = modff((phase*table->size),&hi);
  unsigned int high = ceilf(phase*(float)table->size);
  unsigned int low = floorf(phase*(float)table->size);

  float val1 = table->vals[high];
  float val2 = table->vals[low];

  return (val1 * rem) + (val2 * (1.f - rem));
}

void
wt_generate_sine(float *table, unsigned int table_size)
{
  float step = 1.f/table_size;
  unsigned int i;
  for(i = 0; i<table_size; i++) { 
    table[i] = sinf((i*step)*PI*2.f);
  }
}
