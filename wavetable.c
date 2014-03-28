#include "wavetable.h"
#include "wave.h"

#include "interpolate.c"

void
wavetable_init ( struct wavetable_t *wt, struct wave_t *w, int size )
{
  wt->size = size;
  wt->waves = w;
}

float
wavetable_lookup_offset ( struct wavetable_t *wt, float phase, float offset, float scan )
{
  float real_phase = phase+offset;
  if(real_phase<0.f) {
    real_phase = 1+real_phase;
  }
  return wavetable_lookup(wt, real_phase, scan);
}

float
wavetable_lookup ( struct wavetable_t *wt, float phase, float scan )
{
  unsigned int low = scan*wt->size;
  unsigned int high = ((low+1>=wt->size) ? wt->size : low+1);

  float low_w = wave_lookup(&wt->waves[low], phase);
  float high_w = wave_lookup(&wt->waves[high], phase);

  return lin_interpolate(low_w, high_w, scan);
}
