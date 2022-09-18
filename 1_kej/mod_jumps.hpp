#pragma once

#ifndef modjumps
#define modjumps

#include "pch.h"

namespace cg {

	struct jumpanalyzer_s
	{
		int jumpVelocity;
		int bounceVelocity;
		bool hasBounced;
		DWORD bounceTime;
		bool hasJumped;
		bool weapon_cant_fire;
		bool velocity_clipped;

	};
	inline jumpanalyzer_s jumpanalyzer;
	void Mod_HitAnalyzer(pmove_t* pm, pml_t* pml);
	void Mod_JumpAnalyzer(pmove_t* pm, pml_t* pml);
	void Mod_RPGAnalyzer(pmove_t* pm, pml_t* pml);

	void Mod_JumpView(pmove_t* pm, pml_t* pml);

}
#endif