#ifndef WT_H
#define WT_H

struct wavetable_t {
  unsigned int size; 
  struct wave_t *waves;
};

void wavetable_init ( struct wavetable_t *wt, struct wave_t *vals, int tablesize );
float wavetable_lookup_offset ( struct wavetable_t *wt, float phase, float offset, float scan );
float wavetable_lookup ( struct wavetable_t *wt, float phase, float scan );

#endif
