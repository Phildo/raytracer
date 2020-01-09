#ifndef WORLD_H
#define WORLD_H

#include <cstdlib>
#include "img.h"

void gen_img(canvas img);
inline double random_double()
{
  return rand() / (RAND_MAX + 1.0);
}

#endif //WORLD_H

