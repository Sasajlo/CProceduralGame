#pragma once

#define PI 3.14159265358979323846f

float toRadians(float degrees);
void normalize(float* v);
void crossProduct(float* result, const float* a, const float* b);
float dotProduct(const float* a, const float* b);
void setModelMatrix(float translation[3], float rotation[3], float scale[3], float* matrix);
void setViewMatrix(float* viewMatrix, const float* eye, const float* center);
void setPerspectiveMatrix(float fov, float aspect, float near, float far, float* matrix);
void rotateOffset(float* offset, float xAngle, float yAngle, float* resultOffset);