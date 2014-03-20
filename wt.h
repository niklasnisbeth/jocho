#ifndef WT_H
#define WT_H

struct wavetable_t {
  unsigned int size;
  float *vals;
};

float wt_lookup_offset(struct wavetable_t *table, float phase, float offset);

float wt_lookup(struct wavetable_t *table, float phase);

void wt_generate_sine(float *table, unsigned int table_size);

#endif
