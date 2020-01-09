#include "img.h"

#include <stdlib.h>
#include <stdio.h>

void alloc_px_canvas(canvas *img) { img->px = (vec3 *)malloc(sizeof(vec3)*img->w*img->h); }
void alloc_px_ppm(ppm *img) { img->px = (unsigned char *)malloc(sizeof(unsigned char)*3*img->w*img->h); }

ppm ppm_for_canvas(canvas cimg)
{
  ppm pimg;
  pimg.w = cimg.w;
  pimg.h = cimg.h;
  alloc_px_ppm(&pimg);
  return pimg;
}

void canvas_to_ppm(canvas cimg, ppm pimg)
{
  int ci = 0;
  int pi = 0;
  for(int y = 0; y < cimg.h; y++)
  {
    for(int x = 0; x < cimg.w; x++)
    {
      pimg.px[pi+0] = sqrt(cimg.px[ci].r())*255.999;
      pimg.px[pi+1] = sqrt(cimg.px[ci].g())*255.999;
      pimg.px[pi+2] = sqrt(cimg.px[ci].b())*255.999;
      pi += 3;
      ci++;
    }
  }
}

void print_ppm(ppm img)
{
  printf("P3\n%d %d\n255\n",img.w,img.h);
  int i = 0;
  for(int y = 0; y < img.h; y++)
  {
    for(int x = 0; x < img.w; x++)
    {
      printf("%d %d %d ",img.px[i+0],img.px[i+1],img.px[i+2]);
      printf("\n");
      i += 3;
    }
    printf("\n");
  }

}


