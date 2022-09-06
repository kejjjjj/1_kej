#pragma once

#ifndef scrmain
#define scrmain

#include "pch.h"

void Scr_Init();
typedef void*(__cdecl* Player_GetMethod_hook)(const char** name);
inline Player_GetMethod_hook Player_GetMethod_f = (Player_GetMethod_hook)(0x4C9E90);

typedef void* (__cdecl* Scr_GetFunction_hook)(const char** name, int* type);
inline Scr_GetFunction_hook Scr_GetFunction_f = (Scr_GetFunction_hook)(0x4D8470);

#endif