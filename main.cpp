#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "img.h"
#include "world.h"

int main(int argv, char **argc)
{
  int w = 2048;
  int h = 1024;
  int aa = 100;
  int bounce = 10;

  for(int i = 0; i < argv; i++)
  {
    if(strcmp(argc[i],"quick") == 0)
    {
      w = 200;
      h = 100;
    }
    else if(strcmp(argc[i],"dirty") == 0)
    {
      aa = 10;
      bounce = 2;
    }
  }

  canvas cimg;
  cimg.w = w;
  cimg.h = h;
  alloc_px_canvas(&cimg);
  gen_img(cimg,aa,bounce);
  ppm pimg = ppm_for_canvas(cimg);
  canvas_to_ppm(cimg,pimg);
  print_ppm(pimg);
}

