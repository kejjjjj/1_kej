#pragma once

#ifndef scrfunc
#define scrfunc

#include "pch.h"

typedef void(__cdecl* xmethod_t)(scr_entref_t);
//typedef void(__cdecl* xscr_function_t)();

void Scr_LoadMethods();
xmethod_t Player_GetMethod(const char** name);
xfunction_t Scr_GetFunction(const char** name, int* type);

void PlayerCmd_GetButtonPressed(scr_entref_t arg);
void PlayerCmd_GetForwardMove(scr_entref_t arg);
void PlayerCmd_GetRightMove(scr_entref_t arg);
void PlayerCmd_SetVelocity(scr_entref_t arg);


void GScr_WeaponExists();
void GScr_WorldToScreen(scr_entref_t arg);
void GScr_GetEvarInt();
void GScr_GetEvarFloat();
void GScr_GetEvar();
void GScr_WriteToAddress();
void Gscr_GetAddressInt();
void Gscr_GetAddressFloat();

void GScr_SendCommand();
#endif