#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void write_ppm1(const char * file_name, uint32_t width, uint32_t height, uint32_t image[width][height])
{
  FILE * fp = fopen(file_name, "w");

  fprintf(fp, "P3\n%d\n%d\n255\n", width, height);

  for(int y = height-1; y >= 0 ; y--)
  {
    for(int x=0; x < width ; x++)
    {
      fprintf(fp, "%d %d %d ", (image[x][y] >> 16) & 0xFF, (image[x][y] >> 8) & 0xFF, image[x][y] & 0xFF);
    }
  }

  fclose(fp);
}

void write_ppm(const char * file_name, uint32_t width, uint32_t height, uint32_t * image)
{
  FILE * fp = fopen(file_name, "w");

  fprintf(fp, "P3\n%d\n%d\n255\n", width, height);

  for(int y = height-1; y >= 0 ; y--)
  {
    for(int x=0; x < width ; x++)
    {
      fprintf(fp, "%d %d %d ", (*(image + y*width + x) >> 16) & 0xFF, (*(image + y*width + x) >> 8) & 0xFF, *(image + y*width + x) & 0xFF);
    }
  }

  fclose(fp);
}

void write_ppm2(FILE * fp, uint32_t width, uint32_t height, uint32_t * image)
{
  fprintf(fp, "P3\n%d\n%d\n255\n", width, height);

  for(int y = height-1; y >= 0 ; y--)
  {
    for(int x=0; x < width ; x++)
    {
      fprintf(fp, "%d %d %d ", (*(image + y*width + x) >> 16) & 0xFF, (*(image + y*width + x) >> 8) & 0xFF, *(image + y*width + x) & 0xFF);
    }
  }

  fclose(fp);
}
