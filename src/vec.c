#include "vec.h"

#include <string.h>
#include <stdio.h>

vec2 vec2_add(const vec2 left, const vec2 right) {
    vec2 out;
    out.x = left.x + right.x;
    out.y = left.y + right.y;
    return out;
}

vec2 vec2_sub(const vec2 left, const vec2 right) {
    vec2 out;
    out.x = left.x - right.x;
    out.y = left.y - right.y;
    return out;
}

vec2 vec2_mul(const vec2 left, const vec2 right) {
    vec2 out;
    out.x = left.x * right.x;
    out.y = left.y * right.y;
    return out;
}

vec2 vec2_div(const vec2 left, const vec2 right) {
    vec2 out;
    out.x = left.x * right.x;
    out.y = left.y * right.y;
    return out;
}

float vec2_dot(const vec2 left, const vec2 right) {
    return left.x * right.x + left.y * left.y;
}

float vec2_lengthSquared(const vec2 vec){
    return vec2_dot(vec, vec);
}

float vec2_length(const vec2 vec) {
    return sqrtf(vec2_lengthSquared(vec));
}

////////////////////////////////////////////////////////

vec3 vec3_add(const vec3 left, const vec3 right) {
    vec3 out;
    out.x = left.x + right.x;
    out.y = left.y + right.y;
    out.z = left.z + right.z;     
    return out;
}

vec3 vec3_sub(const vec3 left, const vec3 right) {
    vec3 out;
    out.x = left.x - right.x;
    out.y = left.y - right.y;
    out.z = left.z - right.z;     
    return out;
}

vec3 vec3_mul(const vec3 left, const vec3 right) {
    vec3 out;
    out.x = left.x * right.x;
    out.y = left.y * right.y;
    out.z = left.z * right.z;     
    return out;

}

vec3 vec3_mul_f(const vec3 left, const float right) {
    vec3 out;
    out.x = left.x + right;
    out.y = left.y + right;
    out.z = left.z + right;     
    return out;
}

vec3 vec3_div(const vec3 left, const vec3 right) {
    vec3 out;
    out.x = left.x / right.x;
    out.y = left.y / right.y;
    out.z = left.z / right.z;     
    return out;
}

vec3 vec3_div_f(const vec3 left, const float right) {
    vec3 out;
    out.x = left.x / right;
    out.y = left.y / right;
    out.z = left.z / right;     
    return out;
}

float vec3_dot(const vec3 left, const vec3 right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

float vec3_lengthSquared(const vec3 vec){
    return vec3_dot(vec, vec);
}

float vec3_length(const vec3 vec) {
    return sqrtf(vec3_lengthSquared(vec));
} 

vec3 vec3_neg(const vec3 vec) {
    vec3 out;
    out.x = -vec.x;
    out.y = -vec.y;
    out.z = -vec.z;
    return out;    
}

vec3 vec3_normalize(const vec3 vec) {
    float length = vec3_length(vec);
    return vec3_div_f(vec, length);
}

void vec3_print(const vec3 vec) {
    printf("%f, %f, %f\n\n", vec.x, vec.y, vec.z);
}

vec3 vec3_cross(const vec3 left, const vec3 right) {
    vec3 out;
    out.x = left.y * right.z - left.z* right.y;
    out.y = left.z * right.x - left.x * right.z;
    out.z = left.x * right.y - left.y * right.x;
    return out;
}

////////////////////////////////////////////////////////

vec4 vec4_add(const vec4 left, const vec4 right) {
    vec4 out;
    out.x = left.x + right.x;
    out.y = left.y + right.y;
    out.z = left.z + right.z;     
    out.w = left.w + right.w;     
    return out;
}

vec4 vec4_sub(const vec4 left, const vec4 right) {
    vec4 out;
    out.x = left.x - right.x;
    out.y = left.y - right.y;
    out.z = left.z - right.z;     
    out.w = left.w - right.w;     
    return out;
}

vec4 vec4_mul(const vec4 left, const vec4 right) {
    vec4 out;
    out.x = left.x * right.x;
    out.y = left.y * right.y;
    out.z = left.z * right.z;     
    out.w = left.w * right.w;     
    return out;

}

vec4 vec4_mul_f(const vec4 left, const float right) {
    vec4 out;
    out.x = left.x * right;
    out.y = left.y * right;
    out.z = left.z * right;     
    out.w = left.w * right;     
    return out;
}

vec4 vec4_div(const vec4 left, const vec4 right) {
    vec4 out;
    out.x = left.x / right.x;
    out.y = left.y / right.y;
    out.z = left.z / right.z;     
    out.w = left.w / right.w;     
    return out;
}

vec4 vec4_div_f(const vec4 left, const float right) {
    vec4 out;
    out.x = left.x / right;
    out.y = left.y / right;
    out.z = left.z / right;     
    out.w = left.w / right;     
    return out;
}

float vec4_dot(const vec4 left, const vec4 right) {
    return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

float vec4_lengthSquared(const vec4 vec){
    return vec4_dot(vec, vec);
}

float vec4_length(const vec4 vec) {
    return sqrtf(vec4_lengthSquared(vec));
} 

vec4 vec4_neg(const vec4 vec) {
    vec4 out;
    out.x = -vec.x;
    out.y = -vec.y;
    out.z = -vec.z;
    out.w = -vec.w;
    return out;    
}

vec4 vec4_normalize(const vec4 vec) {
    float length = vec4_length(vec);
    return vec4_div_f(vec, length);
}

void vec4_print(const vec4 vec) {
    printf("%f, %f, %f\n\n", vec.x, vec.y, vec.z);
}

vec4 vec4_mul_mat4(const vec4 left, const mat4 right) {
    vec4 temp = {0,0,0,0};

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            (&temp.x)[i] += (&left.x)[j]* right[i][j];
        }
    }

    return temp;
}

////////////////////////////////////////////////////////

void mat4_setPerspective(mat4 mat, float fov, float aspect, float nearPlane, float farPlane) {
    float fovRad = fov * PI / 180.0f;
    float tanfov = 1.0f / tanf(fovRad * 0.5f);

    mat4_setZero(mat);
    mat[0][0] = tanfov / aspect;
    mat[1][1] = tanfov;
    mat[2][2] = farPlane / (farPlane - nearPlane);
    mat[2][3] = (-farPlane * nearPlane) / (farPlane - nearPlane);
    mat[3][2] = 1.0f;
}

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

void mat4_inverse(const mat4 mat, mat4 invOut)
{
    float inv[16], det;
    int i;
    const float* m = (const float*)&mat[0];

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0) {
        printf("No inverse!\n");
        return;
    }

    det = 1.0 / det;

    for (i = 0; i < 16; i++) { 
        ((float*)invOut)[i] = inv[i] * det;
    }
}
void mat4_transpose(const mat4 mat, mat4 transOut)
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            transOut[j][i] = mat[i][j];
        }
    }
}

void mat4_cpy(const mat4 mat, mat4 out) {
    memcpy(out, mat, 16 * sizeof(float));
}

void mat4_setRotX(float rx, mat4 mat) {
    mat4_setIdentity(mat);
    float cosTheta = cosf(rx);
    float sinTheta = sinf(rx);
    mat[1][1] = cosTheta;
    mat[1][2] = -sinTheta;
    mat[2][1] = sinTheta;
    mat[2][2] = cosTheta;
}

void mat4_setRotY(float ry, mat4 mat) {
    mat4_setIdentity(mat);
    float cosTheta = cosf(ry);
    float sinTheta = sinf(ry);
    mat[0][0] = cosTheta;
    mat[0][2] = sinTheta;
    mat[2][0] = -sinTheta;
    mat[2][2] = cosTheta;
}

void mat4_setRotZ(float rz, mat4 mat) {
    mat4_setIdentity(mat);
    float cosTheta = cosf(rz);
    float sinTheta = sinf(rz);
    mat[0][0] = cosTheta;
    mat[0][1] = -sinTheta;
    mat[1][0] = sinTheta;
    mat[1][1] = cosTheta; 
}

void mat4_setRotXYZ(float rx, float ry, float rz, mat4 mat) {
    mat4 mx, my, mz;
    mat4_setRotX(rx, mx);
    mat4_setRotY(ry, my);
    mat4_setRotZ(rz, mz);

    mat4 mzy;
    mat4_mul(mz, my, mzy);
    // mat4 mzyx;
    mat4_mul(mzy, mx, mat);
}

void mat4_rotate(const mat4 inMat, float rx, float ry, float rz, mat4 outMat)
{
    mat4 rotMat, tempOut;
    mat4_setRotXYZ(rx,ry,rz, rotMat);
    mat4_mul(inMat, rotMat, tempOut);
    mat4_cpy(tempOut, outMat);
}

void mat4_translate(const mat4 inMat, float x, float y, float z, mat4 outMat)
{
    mat4 transMat, tempOut;
    mat4_setIdentity(transMat);
    mat4_setTranslation(transMat, x, y, z);
    mat4_mul(inMat, transMat, tempOut);
    mat4_cpy(tempOut, outMat);
}