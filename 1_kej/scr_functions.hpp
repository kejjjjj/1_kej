#pragma once

#ifndef scrfunc
#define scrfunc

#include "pch.h"

typedef void(__cdecl* xmethod_t)(scr_entref_t);

void Scr_LoadMethods();
xmethod_t Player_GetMethod(const char** name);

void PlayerCmd_JumpButtonPressed(scr_entref_t arg);

#endif