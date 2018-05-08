#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../include/matrix.h"
#include "../include/vector.h"

mat4 get_mat4(vec4 col1, vec4 col2, vec4 col3, vec4 col4)
{
  mat4 ret = {col1, col2, col3, col4};
  return ret;
}

mat4 mat4_mul(mat4 a, mat4 b)
{
  vec4 row1 = get_row_mat4(a, 0);
  vec4 row2 = get_row_mat4(a, 1);
  vec4 row3 = get_row_mat4(a, 2);
  vec4 row4 = get_row_mat4(a, 3);

  vec4 col1 = get_col_mat4(b, 0);
  vec4 col2 = get_col_mat4(b, 1);
  vec4 col3 = get_col_mat4(b, 2);
  vec4 col4 = get_col_mat4(b, 3);

  mat4 ret = get_mat4( get_vec4( dot4(row1, col1), dot4(row2, col1), dot4(row3, col1), dot4(row4, col1) ),
                       get_vec4( dot4(row1, col2), dot4(row2, col2), dot4(row3, col2), dot4(row4, col2) ),
                       get_vec4( dot4(row1, col3), dot4(row2, col3), dot4(row3, col3), dot4(row4, col3) ),
                       get_vec4( dot4(row1, col4), dot4(row2, col4), dot4(row3, col4), dot4(row4, col4) ) );
  return ret;
}

vec4 mat4_vmul(mat4 a, vec4 b)
{
  vec4 row1 = get_row_mat4(a, 0);
  vec4 row2 = get_row_mat4(a, 1);
  vec4 row3 = get_row_mat4(a, 2);
  vec4 row4 = get_row_mat4(a, 3);

  vec4 ret = get_vec4(dot4(row1, b), dot4(row2, b), dot4(row3, b), dot4(row4, b));
  return ret;
}

mat4 rotate4zM(mat4 b, float deg)
{
  float c = cos(M_PI*deg/180.0);
  float s = sin(M_PI*deg/180.0);

	mat4 rot_mat = get_mat4( get_vec4( c, s, 0, 0),
													 get_vec4(-s, c, 0, 0),
												 	 get_vec4( 0, 0, 1, 0),
												 	 get_vec4( 0, 0, 0, 1));

  return mat4_mul(rot_mat, b);
}


mat4 rotate4yM(mat4 b, float deg)
{
  float c = cos(M_PI*deg/180.0);
  float s = sin(M_PI*deg/180.0);

	mat4 rot_mat = get_mat4( get_vec4( c, 0,-s, 0),
													 get_vec4( 0, 1, 0, 0),
												 	 get_vec4( s, 0, c, 0),
												 	 get_vec4( 0, 0, 0, 1));

  return mat4_mul(rot_mat, b);
}

mat4 rotate4xM(mat4 b, float deg)
{
  float c = cos(M_PI*deg/180.0);
  float s = sin(M_PI*deg/180.0);

	mat4 rot_mat = get_mat4( get_vec4( 1, 0, 0, 0),
													 get_vec4( 0, c, s, 0),
												 	 get_vec4( 0,-s, c, 0),
												 	 get_vec4( 0, 0, 0, 1));

  return mat4_mul(rot_mat, b);
}

mat4 mat4_add(mat4 a, mat4 b)
{
  mat4 ret = get_mat4( add4(a.col1, b.col1),
                       add4(a.col2, b.col2),
                       add4(a.col3, b.col3),
                       add4(a.col4, b.col4));
  return ret;
}

vec4 get_col_mat4(mat4 mat, int col)
{
  switch(col)
  {
    case 0:   return mat.col1;
    case 1:   return mat.col2;
    case 2:   return mat.col3;
    case 3:   return mat.col4;
    default:  fprintf(stderr, "Error %s %s %d\n", __FILE__, __FUNCTION__, __LINE__); exit(-1);
  }
}

vec4 get_row_mat4(mat4 mat, int row)
{
  vec4 ret;

  if(row >= 0 && row < 4)
  {
    ret.x = *(((float *)&mat) + row);
    ret.y = *(((float *)&mat) + row + 4);
    ret.z = *(((float *)&mat) + row + 8);
    ret.w = *(((float *)&mat) + row + 12);
  }
  else
  {
    fprintf(stderr, "Error: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__); exit(-1);
  }
  return ret;
}

void print_mat4(mat4 mat)
{
  float * ptr = (float *)(&mat);

  printf("[\n");
  for(int i=0; i < 4; i++)
  {
    printf("[");
    printf("%f %f %f %f", *(ptr + i), *(ptr + 4 + i), *(ptr + 8 + i), *(ptr + 12 + i));
    printf("]\n");
  }
  printf("]\n");
}
