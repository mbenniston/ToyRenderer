#include "vec.h"
#include <string.h>
#include <stdio.h>

void vec2_add(const vec2 left, const vec2 right, vec2 out) {
    out[0] = left[0] + right[0];
    out[1] = left[1] + right[1];
}

void vec2_sub(const vec2 left, const vec2 right, vec2 out) {
    out[0] = left[0] - right[0];
    out[1] = left[1] - right[1];
}

void vec2_mul(const vec2 left, const vec2 right, vec2 out) {
    out[0] = left[0] * right[0];
    out[1] = left[1] * right[1];
}

void vec2_div(const vec2 left, const vec2 right, vec2 out) {
    out[0] = left[0] / right[0];
    out[1] = left[1] / right[1];
}

float vec2_dot(const vec2 left, const vec2 right) {
    return left[0] * right[0] + left[1] * left[1];
}

float vec2_legnthSqaured(const vec2 vec){
    return vec2_dot(vec, vec);
}

float vec2_length(const vec2 vec) {
    return sqrtf(vec2_legnthSqaured(vec));
}

////////////////////////////////////////////////////////

void vec3_add(const vec3 left, const vec3 right, vec3 out) {
    out[0] = left[0] + right[0];
    out[1] = left[1] + right[1];
    out[2] = left[2] + right[2];
}

void vec3_sub(const vec3 left, const vec3 right, vec3 out) {
    out[0] = left[0] - right[0];
    out[1] = left[1] - right[1];
    out[2] = left[2] - right[2];
}

void vec3_mul(const vec3 left, const vec3 right, vec3 out) {
    out[0] = left[0] * right[0];
    out[1] = left[1] * right[1];
    out[2] = left[2] * right[2];
}

void vec3_div(const vec3 left, const vec3 right, vec3 out) {
    out[0] = left[0] / right[0];
    out[1] = left[1] / right[1];
    out[2] = left[2] / right[2];
}

float vec3_dot(const vec3 left, const vec3 right) {
    return left[0] * right[0] + left[1] * right[1] + left[2] * right[2];
}

float vec3_legnthSqaured(const vec3 vec){
    return vec3_dot(vec, vec);
}

float vec3_length(const vec3 vec) {
    return sqrtf(vec3_legnthSqaured(vec));
} 

////////////////////////////////////////////////////////

void vec4_add(const vec4 left, const vec4 right, vec4 out) {
    out[0] = left[0] + right[0];
    out[1] = left[1] + right[1];
    out[2] = left[2] + right[2];
    out[3] = left[3] + right[3];
}

void vec4_sub(const vec4 left, const vec4 right, vec4 out) {
    out[0] = left[0] - right[0];
    out[1] = left[1] - right[1];
    out[2] = left[2] - right[2];
    out[3] = left[3] - right[3];
}

void vec4_mul(const vec4 left, const vec4 right, vec4 out) {
    out[0] = left[0] * right[0];
    out[1] = left[1] * right[1];
    out[2] = left[2] * right[2];
    out[2] = left[2] * right[2];
}

void vec4_mul_mat4(const vec4 left, const mat4 right, vec4 out) {
    memset(out, 0, 4 * sizeof(float));

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            out[i] += left[i]* right[i][j];
        }
    }
}

void vec4_div(const vec4 left, const vec4 right, vec4 out) {
    out[0] = left[0] / right[0];
    out[1] = left[1] / right[1];
    out[2] = left[2] / right[2];
    out[3] = left[3] / right[3];
}

float vec4_dot(const vec4 left, const vec4 right) {
    return left[0] * right[0] + left[1] * right[1] + left[2] * right[2] + left[3] * right[3];
}

float vec4_legnthSqaured(const vec4 vec){
    return vec4_dot(vec, vec);
}

float vec4_length(const vec4 vec) {
    return sqrtf(vec4_legnthSqaured(vec));
} 

void mat4_setPerspective(mat4 mat, float fov, float aspect, float nearPlane, float farPlane) {
    mat4_setZero(mat);
    float fovRad = fov * PI / 180.0f;
    float tanfov = tanf(fov * 0.5f);

    mat[0][0] = 0.0f;
    mat[0][0] = 0.0f;
    mat[0][0] = 0.0f;
    mat[0][0] = 0.0f;
}

void vec4_print(const vec4 vec) {
    printf("%f, %f, %f, %f\n", vec[0], vec[1], vec[2], vec[3]);
}

////////////////////////////////////////////////////////

void mat4_setIdentity(mat4 mat) {
    memset(mat, 0, 16 * sizeof(float));
    mat[0][0] = 1.0f;
    mat[1][1] = 1.0f;
    mat[2][2] = 1.0f;
    mat[3][3] = 1.0f; 
}

void mat4_setZero(mat4 mat) {
    memset(mat, 0, 16 * sizeof(float));
}

void mat4_mul(const mat4 left, const mat4 right, mat4 out){
    mat4_setZero(out);

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            float temp = 0;

            for(int k = 0; k < 4; k++){
                temp += left[k][j] * right[i][k];
            }

            out[i][j] = temp; 
        }
    }
}

void mat4_print(const mat4 mat) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%f, ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void mat4_setTranslation(mat4 mat, float x, float y, float z) {
    mat[0][3] = x;
    mat[1][3] = y;
    mat[2][3] = z;
}

void mat4_setScale(mat4 mat, float sx, float sy, float sz) {
    mat[0][0] = sx;
    mat[1][1] = sy;
    mat[2][2] = sz;
}

