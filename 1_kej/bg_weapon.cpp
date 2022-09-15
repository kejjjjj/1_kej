#include "pch.h"

void _spread(float* a3, float* spread)
{
	*a3 = 1;
	*spread = 1;
}

void* __fastcall cg::BG_GetSpreadForWeapon(float* a3, gclient_s* gameclient, WeaponDef* weapDef, float* spread)
{

	//BG_GetSpreadForWeapon_f(a3, gameclient, weapDef, spread);
	float* _ptr, *_ptr2;
	__asm
	{
		mov eax, esi;
		mov _ptr, eax;
		mov eax, edi;
		mov _ptr2, eax;
	}
	BG_GetSpreadForWeapon_f(a3, gameclient, weapDef, spread);



	return;
}