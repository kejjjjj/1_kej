#pragma once

#ifndef scrobj
#define scrobj


#include "pch.h"

void Scr_ObjectError(const char* msg, ...);
int Scr_GetInt(uint32_t param);
float Scr_GetFloat(uint32_t param);
float Scr_GetVector(uint32_t param, float* vector);
int Scr_GetNumParam();
int Scr_AddInt(int val);
int Scr_AddFloat(float val);
float* Scr_AddVector(float* vector);
#endif