#include "../include/vector.h"

vec3 n1 = {1.000,0.000,0.000};
vec3 n2 = {0.000,1.000,0.000};
vec3 n3 = {0.000,0.000,1.000};
vec3 n4 = {0.577,0.577,0.577};
vec3 n5 = {-0.577,0.577,0.577};
vec3 n6 = {0.577,-0.577,0.577};
vec3 n7 = {0.577,0.577,-0.577};
vec3 n8 = {0.000,0.357,0.934};
vec3 n9 = {0.000,-0.357,0.934};
vec3 n10 = {0.934,0.000,0.357};
vec3 n11 = {-0.934,0.000,0.357};
vec3 n12 = {0.357,0.934,0.000};
vec3 n13 = {-0.357,0.934,0.000};
vec3 n14 = {0.000,0.851,0.526};
vec3 n15 = {0.000,-0.851,0.526};
vec3 n16 = {0.526,0.000,0.851};
vec3 n17 = {-0.526,0.000,0.851};
vec3 n18 = {0.851,0.526,0.000};
vec3 n19 = {-0.851,0.526,0.000};

// p as usual, e exponent (p in the paper), r radius or something like that
float octahedral(vec3 p, float r) {
	float s = fabs(dot3(p,n4));
	s = max(s, fabs(dot3(p,n5)));
	s = max(s, fabs(dot3(p,n6)));
	s = max(s, fabs(dot3(p,n7)));
	return s-r;
}

float dodecahedral(vec3 p, float r) {
	float s =fabs(dot3(p,n14));
	s = max(s, fabs(dot3(p,n15)));
	s = max(s, fabs(dot3(p,n16)));
	s = max(s, fabs(dot3(p,n17)));
	s = max(s, fabs(dot3(p,n18)));
	s = max(s, fabs(dot3(p,n19)));
	return s-r;
}

float icosahedral(vec3 p, float r) {
	float s = fabs(dot3(p,n4));
	s = max(s, fabs(dot3(p,n5)));
	s = max(s, fabs(dot3(p,n6)));
	s = max(s, fabs(dot3(p,n7)));
	s = max(s, fabs(dot3(p,n8)));
	s = max(s, fabs(dot3(p,n9)));
	s = max(s, fabs(dot3(p,n10)));
	s = max(s, fabs(dot3(p,n11)));
	s = max(s, fabs(dot3(p,n12)));
	s = max(s, fabs(dot3(p,n13)));

	return s-r;
}

float toctahedral(vec3 p, float e, float r) {
	float s = pow(fabs(dot3(p,n1)),e);
	s += pow(fabs(dot3(p,n2)),e);
	s += pow(fabs(dot3(p,n3)),e);
	s += pow(fabs(dot3(p,n4)),e);
	s += pow(fabs(dot3(p,n5)),e);
	s += pow(fabs(dot3(p,n6)),e);
	s += pow(fabs(dot3(p,n7)),e);
	s = pow(s, 1.0/e);
	return s-r;
}

float ticosahedral(vec3 p, float e, float r) {
	float s = pow(fabs(dot3(p,n4)),e);
	s += pow(fabs(dot3(p,n5)),e);
	s += pow(fabs(dot3(p,n6)),e);
	s += pow(fabs(dot3(p,n7)),e);
	s += pow(fabs(dot3(p,n8)),e);
	s += pow(fabs(dot3(p,n9)),e);
	s += pow(fabs(dot3(p,n10)),e);
	s += pow(fabs(dot3(p,n11)),e);
	s += pow(fabs(dot3(p,n12)),e);
	s += pow(fabs(dot3(p,n13)),e);
	s += pow(fabs(dot3(p,n14)),e);
	s += pow(fabs(dot3(p,n15)),e);
	s += pow(fabs(dot3(p,n16)),e);
	s += pow(fabs(dot3(p,n17)),e);
	s += pow(fabs(dot3(p,n18)),e);
	s += pow(fabs(dot3(p,n19)),e);
	s = pow(s, 1.0/e);
	return s-r;
}

vec4 boxFold(vec4 z)
{
  #define LENGTH 2.0
  vec3 temp = get_vec3(z.x, z.y, z.z);
  temp = sub3(scale3(2.0, clamp3(temp, -1.0, 1.0)), temp);
  return get_vec4(temp.x, temp.y, temp.z, z.w);
}

#define mR2 0.25
#define fR2 1.00
vec4 sphereFold(vec4 z)
{
  vec3 temp = get_vec3(z.x, z.y, z.z);
  vec4 res = scale4(fR2 / clamp(dot3(temp, temp), mR2, fR2), z);
  return res;
}

#define MR2 1.0
#define ITERATIONS 10
#define MBSCALE -2.0

float mandelbox(vec3 z, vec4 * color)
{
	float w2;
	vec4 w = get_vec4(z.x, z.y, z.z, 1.0), w0 = w;

	*color = w;

  for(int i=0; i < ITERATIONS; i++)
  {
		//w = mat4_vmul(rot_mat, w);
    //printf("w = (%f, %f, %f, %f)\n", w.x, w.y, w.z, w.w);
    w = boxFold(w);
    w = sphereFold(w);
    w = add4(scale4(MBSCALE,w), w0);
		*color = min4(w, *color);
		w2 = w.x * w.x + w.y * w.y + w.z * w.z;
		if(w2 > 1000.0) break;
    //printf("w = (%f, %f, %f, %f)\n", w.x, w.y, w.z, w.w);
  }
  return 0.25*sqrt(w2)/fabs(w.w);
}
