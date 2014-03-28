#ifndef INTERP_C
#define INTERP_C

static float
lin_interpolate(float val1, float val2, float index)
{
  return (val1 * index) + (val2 * (1.f - index));
}

#endif
