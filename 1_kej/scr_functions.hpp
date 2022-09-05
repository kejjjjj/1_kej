#pragma once

#ifndef scrfunc
#define scrfunc

#include "pch.h"

typedef void(__cdecl* xmethod_t)(scr_entref_t);

void Scr_LoadMethods();
xmethod_t Player_GetMethod(const char** name);

void PlayerCmd_GetButtonPressed(scr_entref_t arg);
void PlayerCmd_GetForwardMove(scr_entref_t arg);
void PlayerCmd_GetRightMove(scr_entref_t arg);

#endif