#pragma once

#ifndef autom
#define autom

#include "pch.h"

namespace cg
{
	//actively updating automation data
	struct automation_s {
		bool pendingSlide;
		bool currentlySliding;

	};
	inline automation_s automation; //actively updating automation data
	void Mod_A_Strafebot();
	void Mod_A_AutoFPS();
	void Mod_A_AdjustRPG(pmove_t* pm, pml_t* pml);
	void Mod_A_AutoSliding(pmove_t* pm, pml_t* pml);
}

#endif