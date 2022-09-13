#pragma once

#ifndef cgmain
#define cgmain

#include "pch.h"

namespace cg
{
	inline char(__cdecl*CG_CalcCrosshairColor_f)(float alphaScale, dvar_s* col);
	void __cdecl CG_CalcCrosshairColor(float alphaScale, dvar_s* col);
}

#endif