#include <stdlib.h>
#include <stdio.h>

#include "img.h"

int main(int argv, char **argc)
{
  int w = 200;
  int h = 100;
  canvas cimg;
  cimg.w = w;
  cimg.h = h;
  alloc_px_canvas(&cimg);
  gen_img(cimg);
  ppm pimg = ppm_for_canvas(cimg);
  canvas_to_ppm(cimg,pimg);
  print_ppm(pimg);
}

