#pragma once

#define PI 3.14159265358979323846f

float ToRadians(float degrees);
void Normalize(float* v);
void CrossProduct(float* result, const float* a, const float* b);
float DotProduct(const float* a, const float* b);
void CreateModelMatrix(float position[3], float rotation[3], float scale[3], float* matrix);
void Create2DViewMatrix(float x, float y, float* matrix);
void Create2DProjectionMatrix(float aspect, float* matrix);
float Lerp(float a, float b, float t);
//void setViewMatrix(float* viewMatrix, const float* eye, const float* center);
//void setPerspectiveMatrix(float fov, float aspect, float near, float far, float* matrix);
//void rotateOffset(float* offset, float xAngle, float yAngle, float* resultOffset);