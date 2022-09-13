#include "pch.h"


void __cdecl cg::CG_CalcCrosshairColor(float alphaScale, dvar_s* col)
{
	//col[0] = 1;
	//col[1] = 1;
	//col[2] = 1;
	//col[3] = 1;
	//alphaScale = 1;
	//__asm
	//{
	//	mov col, esi;
	//}
	void* ptr = CG_CalcCrosshairColor;


	CG_CalcCrosshairColor_f(alphaScale, col);

	return;
}
