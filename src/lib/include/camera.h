#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"

typedef mat4 camera;

camera get_camera(vec4 right, vec4 up, vec4 eye, vec4 origin)
{
  mat4 ret = {right, up, eye, origin};
  return ret;
}
#endif
