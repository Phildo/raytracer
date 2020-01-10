#include <stdlib.h>
#include <stdio.h>

#include "img.h"
#include "world.h"

int main(int argv, char **argc)
{
  int w = 2048;
  int h = 1024;

  canvas cimg;
  cimg.w = w;
  cimg.h = h;
  alloc_px_canvas(&cimg);
  gen_img(cimg,100,50);
  ppm pimg = ppm_for_canvas(cimg);
  canvas_to_ppm(cimg,pimg);
  print_ppm(pimg);
}

