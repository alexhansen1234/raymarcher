#ifndef PPM_H
#define PPM_H
extern void write_ppm1(const char * file_name, uint32_t width, uint32_t height, uint32_t image[width][height]);
extern void write_ppm(const char * file_name, uint32_t width, uint32_t height, uint32_t * image);
extern void write_ppm2(FILE * fp, uint32_t width, uint32_t height, uint32_t * image);
#endif
