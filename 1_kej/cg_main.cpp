#include "pch.h"

void SetCrosshairColor(vec4_t col)
{
	static dvar_s* cg_crosshairAlphaMin = Dvar_FindMalleableVar("cg_crosshairAlphaMin");
	col[0] = v::mod_crosshair.GetVector(0);
	col[1] = v::mod_crosshair.GetVector(1);
	col[2] = v::mod_crosshair.GetVector(2);
	col[3] = 1.f;
	cg_crosshairAlphaMin->current.value = v::mod_crosshair.GetVector(3);
}

__declspec(naked) void cg::CG_CalcCrosshairColor()
{
	static float* X;
	
	__asm
	{
		fst dword ptr[esi];
		mov X, esi;
		pop edi;
		fst dword ptr[esi+4];
		fstp dword ptr[esi + 8];
		fld dword ptr[ecx + 0xC];
		fmul[esp + 4 + 4];
		fstp dword ptr[esi + 0xC];
		push X;
		call SetCrosshairColor;
		add esp, 0x4;
		pop esi;
		retn;

	}
	
}
