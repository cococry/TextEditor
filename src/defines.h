#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned int render_id;

typedef unsigned char bool8;
typedef unsigned int bool32;

#define false 0
#define true 1

#define nullptr (void*)0

#define ASSERT(cond) {if(cond) {} else {__debugbreak();}}

typedef struct vector2 {
    float x, y;
} vector2;

typedef struct vector3 {
    float x, y, z;
} vector3;

typedef struct vector4 {
    float x, y, z, w;
} vector4;

typedef struct matrix4 {
    vector4 row1, row2, row3, row4;
} matrix4;

float* vector2_value_ptr(vector2 vec);

float* vector3_value_ptr(vector3 vec);

float* vector4_value_ptr(vector4 vec);

float* matrix4_value_ptr(matrix4 m);

vector4 vector4_additition(vector4 v1, vector4 v2);

vector4 vector4_scaler_multiplication(vector4 v, float k);

matrix4 orthographic_matrix(float left, float right, float top, float bottom);

matrix4 matrix4_identity();

matrix4 translate_mv(matrix4 m, vector3 v);

matrix4 scale_mv(matrix4 m, vector3 v);

matrix4 matrix4_mult(matrix4 m1, matrix4 m2);