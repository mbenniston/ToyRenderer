#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <math.h>

typedef struct {
    union { float x; float u; float s; };
    union { float y; float v; float t; };
} vec2;

typedef struct {
    float x,y,z;
} vec3;

typedef struct {
    float x,y,z,w;
} vec4;

typedef float mat4[4][4];

struct triangle {
    vec3 vertices[3], normals[3];
};

#define PI 3.1415926535

////////////////////////////////////////////////////////////

vec2 vec2_add(const vec2 left, const vec2 right);
vec2 vec2_sub(const vec2 left, const vec2 right);
vec2 vec2_mul(const vec2 left, const vec2 right);
vec2 vec2_div(const vec2 left, const vec2 right);

float vec2_dot(const vec2 left, const vec2 right);
float vec2_lengthSquared(const vec2 vec);
float vec2_length(const vec2 vec);

////////////////////////////////////////////////////////////

vec3 vec3_add(const vec3 left, const vec3 right);
vec3 vec3_sub(const vec3 left, const vec3 right);
vec3 vec3_mul(const vec3 left, const vec3 right);
vec3 vec3_mul_f(const vec3 left, const float right); 
vec3 vec3_div(const vec3 left, const vec3 right);
vec3 vec3_div_f(const vec3 left, const float right); 
vec3 vec3_cross(const vec3 left, const vec3 right);
vec3 vec3_neg(const vec3 vec); 
vec3 vec3_normalize(const vec3 vec); 

float vec3_dot(const vec3 left, const vec3 right); 
float vec3_lengthSquared(const vec3 vec);
float vec3_length(const vec3 vec);

void vec3_print(const vec3 vec);

////////////////////////////////////////////////////////////

vec4 vec4_add(const vec4 left, const vec4 right);
vec4 vec4_sub(const vec4 left, const vec4 right);
vec4 vec4_mul(const vec4 left, const vec4 right);
vec4 vec4_mul_f(const vec4 left, const float right);
vec4 vec4_div(const vec4 left, const vec4 right);
vec4 vec4_div_f(const vec4 left, const float right);
vec4 vec4_normalize(const vec4 vec);
vec4 vec4_neg(const vec4 vec);
vec4 vec4_mul_mat4(const vec4 left, const mat4 right);

float vec4_dot(const vec4 left, const vec4 right);
float vec4_lengthSquared(const vec4 vec);
float vec4_length(const vec4 vec);
void vec4_print(const vec4 vec);

////////////////////////////////////////////////////////////


void mat4_setPerspective(mat4 mat, float fov, float aspect, float nearPlane, float farPlane);
void mat4_setIdentity(mat4 mat);
void mat4_setZero(mat4 mat);
void mat4_mul(const mat4 left, const mat4 right, mat4 out);
void mat4_print(const mat4 mat);
void mat4_setTranslation(mat4 mat, float x, float y, float z);
void mat4_setScale(mat4 mat, float sx, float sy, float sz);
void mat4_inverse(const mat4 mat, mat4 invOut);
void mat4_transpose(const mat4 mat, mat4 transOut);
void mat4_cpy(const mat4 mat, mat4 out);
void mat4_setRotX(float rx, mat4 mat);
void mat4_setRotY(float ry, mat4 mat);
void mat4_setRotZ(float rz, mat4 mat);
void mat4_setRotXYZ(float rx, float ry, float rz, mat4 mat);
void mat4_rotate(const mat4 inMat, float rx, float ry, float rz, mat4 outMat);
void mat4_translate(const mat4 inMat, float x, float y, float z, mat4 outMat);

#endif