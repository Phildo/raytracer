#ifndef IMG_H
#define IMG_H

#include "vec3.h"

struct canvas
{
  int w;
  int h;
  vec3 *px;
};

struct ppm
{
  int w;
  int h;
  unsigned char *px;
};

void alloc_px_canvas(canvas *img);
void alloc_px_ppm(ppm *img);
ppm ppm_for_canvas(canvas cimg);
void canvas_to_ppm(canvas cimg, ppm pimg);
void print_ppm(ppm img);
void gen_img(canvas img);

#endif

