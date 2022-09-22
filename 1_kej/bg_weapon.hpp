#pragma once

#ifndef bgweapon
#define bgweapon

#include "pch.h"

namespace cg
{



	int BG_FindWeaponIndexForName(const char* name);

	inline void (*PM_Weapon_WeaponTimeAdjust_f)();
	void PM_Weapon_WeaponTimeAdjust();

	void __cdecl G_SelectWeaponIndex(int clientNum, int iWeaponIndex);
	size_t G_GetWeaponsList(int* weapons);
}

#endif