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
		bool velocity_clipped; //velocity was clipped during this frame
		int32_t commandTime; //write from PM_ModCode
		int32_t serverTime; //write from PM_ModCode

	};
	inline jumpanalyzer_s jumpanalyzer;
	void Mod_HitAnalyzer(pmove_t* pm, pml_t* pml);
	void Mod_JumpAnalyzer(pmove_t* pm, pml_t* pml);
	void Mod_RPGAnalyzer(pmove_t* pm, pml_t* pml);

	void Mod_DetermineFPS(pmove_t* pm, pml_t* pml);
	void Mod_JumpView(pmove_t* pm, pml_t* pml);

}
#endif