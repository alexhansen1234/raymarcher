#include <math.h>
#include <stdint.h>

#include "../include/vector.h"

vec2 get_vec2(float x, float y)
{
  vec2 ret = {x, y};
  return ret;
}

vec3 get_vec3(float x, float y, float z)
{
  vec3 ret = {x, y, z};
  return ret;
}

vec4 get_vec4(float r, float g, float b, float a)
{
  vec4 ret = {r, g, b, a};
  return ret;
}

vec3 add3(vec3 v1, vec3 v2)
{
  vec3 ret = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
  return ret;
}

vec4 add4(vec4 v1, vec4 v2)
{
  vec4 ret = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
  return ret;
}

vec3 sub3(vec3 v1, vec3 v2)
{
  vec3 ret = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
  return ret;
}

vec4 sub4(vec4 v1, vec4 v2)
{
  vec4 ret = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
  return ret;
}
float length2(vec2 v)
{
  return sqrt(v.x * v.x + v.y * v.y);
}
float length3(vec3 v)
{
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float length4(vec4 v)
{
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

vec2 scale2(float c, vec2 v)
{
  vec2 ret = {c * v.x, c * v.y};
  return ret;
}

vec3 scale3(float c, vec3 v)
{
  vec3 ret = {c * v.x, c * v.y, c * v.z};
  return ret;
}

vec4 scale4(float c, vec4 v)
{
  vec4 ret = {c * v.x, c * v.y, c * v.z, c * v.w};
  return ret;
}

float dot3(vec3 v1, vec3 v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float dot4(vec4 v1, vec4 v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

vec3 normalize3(vec3 v)
{
  vec3 ret = scale3(1.0/length3(v), v);
  return ret;
}

vec4 normalize4(vec4 v)
{
  vec4 ret = scale4(1.0/length4(v), v);
  return ret;
}

uint32_t make_rgb(vec4 v)
{
  return ((uint8_t)((clamp(v.x, 0.0, 1.0)*255))) << 16 | ((uint8_t)(clamp(v.y, 0.0, 1.0)*255)) << 8 | ((uint8_t)((clamp(v.z, 0.0, 1.0))*255));
}

vec3 rotate3x(vec3 v, float degrees)
{
  vec3 ret = {v.x,
              v.y * cos(M_PI * degrees / 180.0) - v.z * sin(M_PI * degrees / 180.0),
              v.y * sin(M_PI * degrees / 180.0) + v.z * cos(M_PI * degrees / 180.0)};
  return ret;
}

vec3 rotate3y(vec3 v, float degrees)
{
  vec3 ret = {v.x * cos(M_PI * degrees / 180) + v.z * sin(M_PI * degrees / 180),
              v.y,
              -v.x * sin(M_PI * degrees / 180) + v.z * cos(M_PI * degrees / 180)};
  return ret;
}

vec3 rotate3z(vec3 v, float degrees)
{
  vec3 ret = {v.x * cos(M_PI * degrees / 180) - v.y * sin(M_PI * degrees / 180),
              v.x * sin(M_PI * degrees / 180) + v.y * cos(M_PI * degrees / 180),
              v.z};

  return ret;
}

vec4 rotate4x(vec4 v, float degrees)
{
  vec4 ret = {v.x,
              v.y * cos(M_PI * degrees / 180.0) - v.z * sin(M_PI * degrees / 180.0),
              v.y * sin(M_PI * degrees / 180.0) + v.z * cos(M_PI * degrees / 180.0),
              v.w};
  return ret;
}

vec4 rotate4y(vec4 v, float degrees)
{
  vec4 ret = {v.x * cos(M_PI * degrees / 180) + v.z * sin(M_PI * degrees / 180),
              v.y,
              -v.x * sin(M_PI * degrees / 180) + v.z * cos(M_PI * degrees / 180),
              v.w};
  return ret;
}

vec4 rotate4z(vec4 v, float degrees)
{
  vec4 ret = {v.x * cos(M_PI * degrees / 180) - v.y * sin(M_PI * degrees / 180),
              v.x * sin(M_PI * degrees / 180) + v.y * cos(M_PI * degrees / 180),
              v.z,
              v.w};

  return ret;
}

vec3 translate3(vec3 v, float dx, float dy, float dz)
{
  vec3 ret = {v.x + dx, v.y + dy, v.z + dz};
  return ret;
}

vec3 vec2_to_vec3(vec2 v)
{
  vec3 ret = {v.x, v.y, 0};
  return ret;
}

vec3 mod3(vec3 v1, vec3 v2)
{
  vec3 ret = {fmod(v1.x, v2.x), fmod(v1.y, v2.y), fmod(v1.z, v2.z)};

  return ret;
}

vec3 abs3(vec3 v)
{
  vec3 ret = {fabs(v.x), fabs(v.y), fabs(v.z)};
  return ret;
}

vec4 abs4(vec4 v)
{
  vec4 ret = {fabs(v.x), fabs(v.y), fabs(v.z), fabs(v.w)};
  return ret;
}

float modfloat(float a, float b)
{
  if(b < 0.01)
    return a;

  if(a < 0)
  {
    while(a < 0)
      a += b;
  }
  else
  {
    while(a > b)
      a -= b;
  }
  return a;
}

vec3 max_vec3(vec3 v1, vec3 v2)
{
  vec3 ret = {max(v1.x, v2.x),
              max(v1.y, v2.y),
              max(v1.z, v2.z)};
  return ret;
}

vec3 reflect(vec3 in, vec3 nor)
{
  vec3 ret = sub3(in, scale3(2*dot3(nor,in)/dot3(nor,nor), nor));
  return ret;
}

vec3 clamp3(vec3 z, float min, float max)
{
  vec3 ret = {clamp(z.x, min, max),
              clamp(z.y, min, max),
              clamp(z.z, min, max)};
  return ret;
}

float clamp(float val, float min, float max)
{
  if(val < min)
  {
    return min;
  }

  if(val > max)
  {
    return max;
  }

  return val;
}

float mix(float a, float b, float k)
{

  return a*(1.0-clamp(k, 0.0, 1.0)) + b*(clamp(k, 0.0, 1.0));
}

vec4 mix4(vec4 a, vec4 b, float k)
{
  vec4 ret = {mix(a.x, b.x, k), mix(a.y, b.y, k), mix(a.z, b.z, k), mix(a.w, b.w, k)};
  return ret;
}

float smin_p(float a, float b, float k)
{
  float h = clamp( 0.5 + 0.5*(b-a)/k, 0.0, 1.0);
  return mix(b, a, h) - k*h*(1.0-h);
}

float smin_exp(float a, float b, float k)
{
  return 0.0;
}

vec4 min4(vec4 a, vec4 b)
{
  vec4 ret = get_vec4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w));
  return ret;
}

vec4 color_norm(vec4 z)
{
  float max_com = max(max(z.x, z.y), z.z);
  if(max_com == 0)
  {
    return get_vec4(0.0, 0.0, 0.0, 0.0);
  }
  else
  {
    vec4 ret = get_vec4(z.x / max_com, z.y / max_com, z.z / max_com, z.w);
    return ret;
  }

}

vec4 color_ramp(uint32_t val, uint32_t max)
{
  uint8_t red, green, blue;

  uint32_t step = (uint32_t)(((double)val * (double)1536) / (double)max);

  if(step < 256)
  {
    red = 255;
    green = step % 256;
    blue = 0;
  }
  else if (step < 512)
  {
    red = 255 - (step % 256);
    green = 255;
    blue = 0;
  }
  else if (step < 768)
  {
    red = 0;
    green = 255;
    blue = step % 256;
  }
  else if (step < 1024)
  {
    red = 0;
    green = 255 - (step % 256);
    blue = 255;
  }
  else if (step < 1280)
  {
    red = step % 256;
    green = 0;
    blue = 255;
  }
  else
  {
    red = 255;
    green = 0;
    blue = 255 - (step % 256);
  }

  return get_vec4(red/255.0, green/255.0, blue/255.0, 0);
}
