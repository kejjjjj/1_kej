#pragma once

#ifndef modjumps
#define modjumps

#include "pch.h"

namespace cg {

	//actively updating jump data
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
		int recommendedFPS;
		bool walking; //pml->walking
		float frametime;
		int msec;
		bool hugging_bounce;
		int pm_flags;
		float jumpOriginZ;

	};
	inline jumpanalyzer_s jumpanalyzer; 	//actively updating jump data
	void Mod_HitAnalyzer(pmove_t* pm, pml_t* pml);
	void Mod_JumpAnalyzer(pmove_t* pm, pml_t* pml);
	void Mod_RPGAnalyzer(pmove_t* pm, pml_t* pml);
	int32_t Mod_RecommendedFPS(float yaw, char forwardmove, char rightmove);

	void Mod_DetermineFPS(pmove_t* pm, pml_t* pml);
	void Mod_JumpView(pmove_t* pm, pml_t* pml);
	void Mod_SaveData(std::vector<jump_data>& storage, pmove_t* pm, bool& hasBounced, bool& hasJumped, bool& hasShotRpg);
	void Mod_BounceCalculator();
	void Mod_BounceCalculator_Create();
	void Mod_DisallowHalfbeat();

	struct bcalc_t
	{
		bool exists;
		vec3_t normal;
		vec3_t origin;
	};
	inline bcalc_t bcalc;
}
#endif