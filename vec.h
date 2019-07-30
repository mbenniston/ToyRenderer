#ifndef VEC_H
#define VEC_H

#include <math.h>

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];
typedef float mat4[4][4];

struct triangle {
    vec3 vertices[3];
    vec3 normals[3];
};

#define PI 3.1415926535

///////////////////////////////////////////////////////////

void vec2_add(const vec2 left, const vec2 right, vec2 out);
void vec2_sub(const vec2 left, const vec2 right, vec2 out);
void vec2_mul(const vec2 left, const vec2 right, vec2 out);
void vec2_div(const vec2 left, const vec2 right, vec2 out);
float vec2_dot(const vec2 left, const vec2 right);
float vec2_lengthSquared(const vec2 vec);
float vec2_length(const vec2 vec);

///////////////////////////////////////////////////////////

void vec3_cpy(const vec3 vec, vec3 out);
void vec3_add(const vec3 left, const vec3 right, vec3 out);
void vec3_sub(const vec3 left, const vec3 right, vec3 out);
void vec3_mul(const vec3 left, const vec3 right, vec3 out);
void vec3_div(const vec3 left, const vec3 right, vec3 out);
float vec3_dot(const vec3 left, const vec3 right);
float vec3_lengthSquared(const vec3 vec);
float vec3_length(const vec3 vec);
void vec3_neg(const vec3 vec, vec3 out);
void vec3_normalize(const vec3 vec, vec3 out);
void vec3_print(const vec3 vec);

///////////////////////////////////////////////////////////

void vec4_cpy(const vec4 vec, vec4 out);
void vec4_add(const vec4 left, const vec4 right, vec4 out);
void vec4_sub(const vec4 left, const vec4 right, vec4 out); 
void vec4_mul(const vec4 left, const vec4 right, vec4 out); 
void vec4_mul_mat4(const vec4 left, const mat4 right, vec4 out); 
void vec4_div(const vec4 left, const vec4 right, vec4 out); 
float vec4_dot(const vec4 left, const vec4 right);
float vec4_lengthSquared(const vec4 vec);
float vec4_length(const vec4 vec);
void vec4_print(const vec4 vec);

///////////////////////////////////////////////////////////

void mat4_cpy(const mat4 mat, mat4 out);
void mat4_setIdentity(mat4 mat);
void mat4_setZero(mat4 mat);
void mat4_mul(const mat4 left, const mat4 right, mat4 out);
void mat4_setTranslation(mat4 mat, float x, float y, float z);
void mat4_setScale(mat4 mat, float sx, float sy, float sz);
void mat4_setOrtho(mat4 mat, float left, float right, float top, float bottom);
void mat4_setPerspective(mat4 mat, float fov, float aspect, float nearPlane, float farPlane); //fov in degrees
void mat4_setRotX(float rx, mat4 mat);
void mat4_setRotY(float ry, mat4 mat);
void mat4_setRotZ(float rz, mat4 mat);
void mat4_setRotXYZ(float rx, float ry, float rz, mat4 mat);
void mat4_inverse(const mat4 mat, mat4 invOut);
void mat4_transpose(const mat4 mat, mat4 transOut);
void mat4_print(const mat4 mat);

#endif