#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"

/* Column Vectors form the Basis for This Matrix */
typedef struct mat4 {
  vec4 col1;
  vec4 col2;
  vec4 col3;
  vec4 col4;
} mat4;

typedef struct mat3 {
  vec3 col1;
  vec3 col2;
  vec3 col3;
} mat3;

extern mat4 get_mat4(vec4 col1, vec4 col2, vec4 col3, vec4 col4);

extern vec4 get_row_mat4(mat4 mat, int row);
extern vec4 get_col_mat4(mat4 mat, int col);

extern mat4 mat4_mul(mat4 a, mat4 b);
extern mat4 mat4_add(mat4 a, mat4 b);
extern mat4 mat4_sub(mat4 a, mat4 b);

extern vec4 mat4_vmul(mat4 a, vec4 b);

extern mat4 rotate_x_m4(mat4 a, float degrees);
extern mat4 rotate_y_m4(mat4 a, float degrees);
extern mat4 rotate_z_m4(mat4 a, float degrees);

extern mat4 rotate4xM(mat4 a, float degrees);
extern mat4 rotate4yM(mat4 a, float degrees);
extern mat4 rotate4zM(mat4 a, float degrees);

extern void print_mat4(mat4 a);

extern mat3 mat3_mul(mat3 a, mat3 b);
extern mat3 mat3_add(mat3 a, mat3 b);
extern mat3 mat3_sub(mat3 a, mat3 b);

extern mat3 rotate_x_m3(mat3 a, float degrees);
extern mat3 rotate_y_m3(mat3 a, float degrees);
extern mat3 rotate_z_m3(mat3 a, float degrees);

#endif
