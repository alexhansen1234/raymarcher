#include <math.h>
#include <stdint.h>

#ifndef VECTOR_H
#define VECTOR_H

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct vec3
{
  float x, y, z;
} vec3;

typedef struct vec4
{
  float x, y, z, w;
}  vec4;

typedef struct vec2
{
  float x, y;
} vec2;

extern vec2 get_vec2(float x, float y);

extern vec3 get_vec3(float x, float y, float z);
extern vec4 get_vec4(float r, float g, float b, float a);
extern vec3 add3(vec3 v1, vec3 v2);
extern vec4 add4(vec4 v1, vec4 v2);
extern vec3 sub3(vec3 v1, vec3 v2);
extern vec4 sub4(vec4 v1, vec4 v2);
extern float length2(vec2 v);

extern float length3(vec3 v);

extern float length4(vec4 v);

extern vec2 scale2(float c, vec2 v);

extern vec3 scale3(float c, vec3 v);

extern vec4 scale4(float c, vec4 v);

extern float dot3(vec3 v1, vec3 v2);

extern float dot4(vec4 v1, vec4 v2);

extern vec3 normalize3(vec3 v);

extern vec4 normalize4(vec4 v);

extern uint32_t make_rgb(vec4 v);

extern vec3 rotate3x(vec3 v, float degrees);

extern vec3 rotate3y(vec3 v, float degrees);

extern vec3 rotate3z(vec3 v, float degrees);

extern vec4 rotate4x(vec4 v, float degrees);

extern vec4 rotate4y(vec4 v, float degrees);

extern vec4 rotate4z(vec4 v, float degrees);

extern vec3 translate3(vec3 v, float dx, float dy, float dz);

extern vec3 vec2_to_vec3(vec2 v);

extern vec3 mod3(vec3 v1, vec3 v2);

extern vec3 abs3(vec3 v);

extern vec4 abs4(vec4 v);

extern float modfloat(float a, float b);

extern vec3 max_vec3(vec3 v1, vec3 v2);

extern vec3 reflect(vec3 in, vec3 nor);

extern float clamp(float val, float min, float max);

extern vec3 clamp3(vec3 z, float min, float max);

extern float mix(float a, float b, float k);

extern vec4 mix4(vec4 a, vec4 b, float k);

extern float smin_p(float a, float b, float k);

extern float smin_exp(float a, float b, float k);

extern vec4 min4(vec4 a, vec4 b);

extern vec4 color_norm(vec4 z);

extern vec4 color_ramp(uint32_t val, uint32_t max);

#endif
