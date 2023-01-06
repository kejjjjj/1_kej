#pragma once

#ifndef qmath
#define qmath

#ifndef M_PI
#define M_PI        3.14159265358979323846f // matches value in gcc v2 math.h
#endif

#include "pch.h"

void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
void vectoangles(const vec3_t value1, vec3_t angles);
void VectorsToAngles(vec3_t src, vec3_t dst, vec3_t outA);
void vector_scale(vec3_t vector, float scale, vec3_t out);
void vector_add(vec3_t veca, vec3_t vecb, vec3_t out);
float vector_scaleComponent(float index, float scale);
float vector_addComponent(float index, float amount);
void AnglesToForward(vec3_t angles, vec3_t origin, float scale, vec3_t out);
void AnglesToRight(vec3_t angles, vec3_t origin, float scale, vec3_t out);
void AnglesToUp(vec3_t angles, vec3_t origin, float scale, vec3_t out);

float AngleNormalizePI(float angle);
float AngleNormalize360(float angle);
float AngleNormalize180(float angle);
float AngleDelta(float angle1, float angle2);

vec_t VectorNormalize(vec3_t v);       // returns vector length
vec_t VectorNormalize2(const vec3_t v, vec3_t out);
void VectorInverse(vec3_t v);

float GetAverage(float* arr, size_t size);

void CrossProduct(const vec3_t v1, const vec3_t v2, vec3_t cross);

bool PlaneFromPoints(vec4_t plane, const vec3_t a, const vec3_t b, const vec3_t c);


void RotatePointAroundVector(vec3_t dst, vec3_t dir, float degrees, vec3_t point);
void MatrixMultiply(float in1[3][3], float in2[3][3], float out[3][3]);
void PerpendicularVector(vec3_t dst, const vec3_t src);
void ProjectPointOnPlane(vec3_t dst, const vec3_t p, const vec3_t normal);

bool VectorCompare(const vec3_t v1, const vec3_t v2);

bool WithinRange(float value, float a, float b);


#endif
