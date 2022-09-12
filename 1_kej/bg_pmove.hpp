#pragma once

#ifndef slidemove
#define slidemove

#include "pch.h"

namespace cg
{
	//typedef void(*Pmove_h)(pmove_t* pmove);
	inline void (*PmoveSingle)(pmove_t* pm) = (void(__cdecl*)(pmove_t*))0x4143A0;


	inline void(__cdecl* PM_AirMove_f)(pmove_t* pm, pml_t* pml);
	inline void(*Pmove_f)(pmove_t* pmove);


	void PM_AirMove(pmove_t* pm, pml_t* pml);
	void Pmove(pmove_t* pmove);

}

#endif