#include "defines.h"
#include <stdlib.h>

float* vector2_value_ptr(vector2 vec) {
    float* ret = malloc(sizeof(float) * 2);
    ret[0] = vec.x;
    ret[1] = vec.y;
    return ret;
}

float* vector3_value_ptr(vector3 vec) {
    float* ret = malloc(sizeof(float) * 3);
    ret[0] = vec.x;
    ret[1] = vec.y;
    ret[2] = vec.z;
    return ret;
}

float* vector4_value_ptr(vector4 vec) {
    float* ret = malloc(sizeof(float) * 4);
    ret[0] = vec.x;
    ret[1] = vec.y;
    ret[2] = vec.z;
    ret[3] = vec.w;
    return ret;

}

float* matrix4_value_ptr(matrix4 m) {
    float* ret = malloc(sizeof(matrix4));

    ret[0] = m.row1.x;
    ret[1] = m.row1.y;
    ret[2] = m.row1.z;
    ret[3] = m.row1.w;

    ret[4] = m.row2.x;
    ret[5] = m.row2.y;
    ret[6] = m.row2.z;
    ret[7] = m.row2.w;

    ret[8] = m.row3.x;
    ret[9] = m.row3.y;
    ret[10] = m.row3.z;
    ret[11] = m.row3.w;

    ret[12] = m.row4.x;
    ret[13] = m.row4.y;
    ret[14] = m.row4.z;
    ret[15] = m.row4.w;

    return ret;
}

matrix4 orthographic_matrix(float left, float right, float top, float bottom) {
    matrix4 ret = matrix4_identity();
    ret.row1.x = 2 / (right - left);
    ret.row2.y = 2 / (top - bottom);
    ret.row3.z = -1;
    ret.row4.x = -(right + left) / (right - left);
    ret.row4.y = -(top + bottom) / (top - bottom);

    return ret;
}

matrix4 matrix4_identity() {
      matrix4 ret = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}};
    return ret;
}

vector4 vector4_additition(vector4 v1, vector4 v2) {
    return (vector4){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}
vector4 vector4_scaler_multiplication(vector4 v, float k) {
    return (vector4){v.x * k, v.y * k, v.z * k, v.w * k};
}
matrix4 translate_mv(matrix4 m, vector3 v) {
       matrix4 ret = m;
    ret.row4 = vector4_additition(vector4_additition(
                                      vector4_scaler_multiplication(m.row1, v.x),
                                      vector4_scaler_multiplication(m.row2, v.y)),
                                  vector4_additition(vector4_scaler_multiplication(m.row3, v.z),
                                                     m.row4));

    return ret;
}

matrix4 scale_mv(matrix4 m, vector3 v) {
    matrix4 ret;
    ret.row1 = vector4_scaler_multiplication(m.row1, v.x);
    ret.row2 = vector4_scaler_multiplication(m.row2, v.y);
    ret.row3 = vector4_scaler_multiplication(m.row3, v.z);
    ret.row4 = m.row4;
    return ret;
}

matrix4 matrix4_mult(matrix4 m1, matrix4 m2) {
    vector4 SrcA0 = m1.row1;
    vector4 SrcA1 = m1.row2;
    vector4 SrcA2 = m1.row3;
    vector4 SrcA3 = m1.row4;

    vector4 SrcB0 = m2.row1;
    vector4 SrcB1 = m2.row2;
    vector4 SrcB2 = m2.row3;
    vector4 SrcB3 = m2.row4;

    matrix4 ret;

    ret.row1 = vector4_additition(vector4_additition(
                                      vector4_scaler_multiplication(SrcA0, SrcB0.x),
                                      vector4_scaler_multiplication(SrcA1, SrcB0.y)),
                                  vector4_additition(
                                      vector4_scaler_multiplication(SrcA2, SrcB0.z),
                                      vector4_scaler_multiplication(SrcA3, SrcB0.w)));
    ret.row2 = vector4_additition(vector4_additition(
                                      vector4_scaler_multiplication(SrcA0, SrcB1.x),
                                      vector4_scaler_multiplication(SrcA1, SrcB1.y)),
                                  vector4_additition(
                                      vector4_scaler_multiplication(SrcA2, SrcB1.z),
                                      vector4_scaler_multiplication(SrcA3, SrcB1.w)));
    ret.row3 = vector4_additition(vector4_additition(
                                      vector4_scaler_multiplication(SrcA0, SrcB2.x),
                                      vector4_scaler_multiplication(SrcA1, SrcB2.y)),
                                  vector4_additition(
                                      vector4_scaler_multiplication(SrcA2, SrcB2.z),
                                      vector4_scaler_multiplication(SrcA3, SrcB2.w)));
    ret.row4 = vector4_additition(vector4_additition(
                                      vector4_scaler_multiplication(SrcA0, SrcB3.x),
                                      vector4_scaler_multiplication(SrcA1, SrcB3.y)),
                                  vector4_additition(
                                      vector4_scaler_multiplication(SrcA2, SrcB3.z),
                                      vector4_scaler_multiplication(SrcA3, SrcB3.w)));
    return ret;
}