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
float AngleNormalizePI(float angle);
float AngleNormalize360(float angle);
float AngleNormalize180(float angle);
float AngleDelta(float angle1, float angle2);

vec_t VectorNormalize(vec3_t v);       // returns vector length
vec_t VectorNormalize2(const vec3_t v, vec3_t out);
void VectorInverse(vec3_t v);
#endif
