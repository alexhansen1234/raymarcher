#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/camera.h"
#include "../include/matrix.h"
#include "../include/vector.h"
#include "../include/sdfs.h"
#include "../include/ppm.h"

#define WIDTH 500
#define HEIGHT 500
#define SCALE 0.333
#define RAYMARCH_ITER 320
#define AA 1
#define HEATMAP 0

vec3 light = {0, 0, -200};
//vec3 light = {-200, 200, -200};

// Build scene here
float distance_field(vec3 p)
{
  /*
  vec3 sphere1 = get_vec3(2.0, 2.0, 0);
  vec3 sphere2 = get_vec3(-2.0, 1.5, 10);
  float dist1 = length3(sub3(p, sphere1)) - 1.0;
  float dist2 = length3(sub3(p, sphere2)) - 2.0;
  return min(dist1, dist2);
  */
  return 1.0;
}


vec3 gradient(vec3 pos, float eps)
{
  vec3 epx = get_vec3(eps, 0, 0);
  vec3 epy = get_vec3(0, eps, 0);
  vec3 epz = get_vec3(0, 0, eps);
  vec3 ret = get_vec3( distance_field(add3(pos, epx)) - distance_field(sub3(pos, epx)),
                       distance_field(add3(pos, epy)) - distance_field(sub3(pos, epy)),
                       distance_field(add3(pos, epz)) - distance_field(sub3(pos, epx)));
  return normalize3(scale3(1.0 / (2.0 * eps), ret));
}


float raymarch(vec3 pos, vec3 dir, vec4 * color, float start, float end, int max_iter, float eps)
{
  float t=start;
  float dist;
  int step;
  vec3 current_pos;
  for(step=0; step < max_iter; step++)
  {
    current_pos = add3(pos, scale3(t, dir));
    dist = mandelbox( current_pos, color );

    if(dist < eps)
    {
      #if HEATMAP
      color->x = (float)step;
      #endif
      return t;
    }
    if(dist > end)
      break;
    t += dist;
  }
  return -1.0;
}

float soft_shadow(vec3 pos, vec3 dir, float k, float start, float end, int max_iter, float eps)
{
  float t=start;
  float dist, res=1.0;
  vec4 temp;
  for(int i=0; i < max_iter; i++)
  {
    dist = mandelbox( add3( pos, scale3(t, dir)), &temp);
    res = min(res, k*dist/t);
    if(res < eps)
      break;
    t += dist;
  }
  return clamp(res, 0.0, 1.0);
}

vec4 render(camera cam, vec4 screen_pos)
{
  vec4 color;
  cam.col1 = scale4(screen_pos.x, cam.col1);
  cam.col2 = scale4(screen_pos.y, cam.col2);

  vec4 dir4 = add4(cam.col1, cam.col2);
  vec4 pos4 = mat4_vmul(cam, get_vec4(0.0, 0.0, 1.0, 1.0));

  vec3 pos = get_vec3(pos4.x, pos4.y, pos4.z);
  vec3 dir = get_vec3(dir4.x, dir4.y, dir4.z);

  dir = normalize3(sub3(dir, pos));

  float dist = raymarch(pos, dir, &color, 0.0, 200.0, RAYMARCH_ITER, 0.0001);
  if(dist > 0.0)
  {
    #if HEATMAP
    return color;
    #else
    vec3 surface = add3(pos, scale3(dist, dir));
    //vec3 grad = gradient(surface, 0.001);
    float shad = soft_shadow( surface, normalize3(sub3(light, surface)), 4.0, 0.1, 20.0, 20, 0.001);
    return scale4(shad, get_vec4(1.0, 1.0, 1.0, 0.0));
    #endif

  }
  else
  {
    return get_vec4(0.15, 0.0, 0.25, 0.0);
  }
}

int main(int argc, char ** argv)
{
  vec4 right = get_vec4(1.0, 0, 0, 0);
  vec4 up = get_vec4(0, 1.0, 0, 0);
  vec4 eye = get_vec4(0, 0, -10, 0);
  vec4 translate = get_vec4(0, 0, -20, 0.0);
  vec4 pixel_color;
  camera cam = get_mat4(right,
                        up,
                        eye,
                        translate);


  cam = rotate4yM(cam, 45);
  cam = rotate4zM(cam, 45);
  //cam = rotate4zM(cam, 45);

  uint32_t * image = (uint32_t *)malloc(sizeof(uint32_t) * HEIGHT * WIDTH);

  for(int y=0; y < HEIGHT; y++)
  {
    for(int x=0; x < WIDTH; x++)
    {
      pixel_color = get_vec4(0, 0, 0, 0);

      vec4 screen_pos = get_vec4(
                                (-1.0 + 2.0 * x / WIDTH)/SCALE,   // X position on screen, -1.0 <= pixel-x < 1.0
                                (-1.0 + 2.0 * y / HEIGHT)/SCALE,  // Y position on screen, -1.0 <= pixel-y < 1.0
                                0,                        // Screen is 2D, so no z component
                                1.0                 // This term will scale the components, but keep the translations regular
      );

      for(int aa=0; aa < AA*AA; aa++)
      {
        screen_pos.x = screen_pos.x + (float)rand()/((float)RAND_MAX)/(100.0*WIDTH*SCALE);
        screen_pos.y = screen_pos.y + (float)rand()/((float)RAND_MAX)/(100.0*HEIGHT*SCALE);

        #if HEATMAP
        pixel_color = render(cam, screen_pos);
        if(pixel_color.x > 1.0)
        {
          pixel_color = color_ramp((int)pixel_color.x, RAYMARCH_ITER);
        }
        #else
        pixel_color = add4(pixel_color, render(cam, screen_pos));
        #endif

      }
      #if !HEATMAP
      pixel_color = scale4(1.0 / (AA*AA), pixel_color);
      #endif
      *(image + y*WIDTH + x) = make_rgb(pixel_color);
    }
  }

  write_ppm("mandelbox.ppm", WIDTH, HEIGHT, image);

  free(image);
}
