#pragma once

#ifndef bgweapon
#define bgweapon

#include "pch.h"

namespace cg
{
	inline void*(__fastcall*BG_GetSpreadForWeapon_f)(float* a3, gclient_s* gameclient, WeaponDef* weapDef, float* spread);
	void* __fastcall BG_GetSpreadForWeapon(float* a3, gclient_s* gameclient, WeaponDef* weapDef, float* spread);
}

#endif