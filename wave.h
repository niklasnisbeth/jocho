#ifndef WAVE_H
#define WAVE_H

struct wave_t {
  unsigned int size;
  float *vals;
};

float wave_lookup_offset(struct wave_t *table, float phase, float offset);

float wave_lookup(struct wave_t *table, float phase);

void wave_generate_sine(float *table, unsigned int table_size);
void wave_generate_saw(float *table, unsigned int table_size);
void wave_generate_triangle(float *table, unsigned int table_size);

#endif
