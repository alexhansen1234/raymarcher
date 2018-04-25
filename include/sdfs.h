#include "../include/vector.h"
#ifndef SDFS_H
#define SDFS_H
extern float octahedral(vec3 p, float r);
extern float dodecahedral(vec3 p, float r);
extern float icosahedral(vec3 p, float r);
extern float toctahedral(vec3 p, float e, float r);
extern float ticosahedral(vec3 p, float e, float r);
extern vec4 boxFold(vec4 z);
extern vec4 sphereFold(vec4 z);
extern float mandelbox(vec3 z, vec4 * color);
#endif
