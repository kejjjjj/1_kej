#pragma once

#ifndef slidemove
#define slidemove

#include "pch.h"

namespace cg
{
	typedef void(__cdecl* PM_AirMove_h)(pmove_t* pm, pml_t* pml);
	inline PM_AirMove_h PM_AirMove_f;

	void PM_AirMove(pmove_t* pm, pml_t* pml);
}

#endif