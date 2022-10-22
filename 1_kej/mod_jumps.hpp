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

	};
	inline jumpanalyzer_s jumpanalyzer; 	//actively updating jump data
	void Mod_HitAnalyzer(pmove_t* pm, pml_t* pml);
	void Mod_JumpAnalyzer(pmove_t* pm, pml_t* pml);
	void Mod_RPGAnalyzer(pmove_t* pm, pml_t* pml);
	int32_t Mod_RecommendedFPS(float yaw, char forwardmove, char rightmove);

	void Mod_DetermineFPS(pmove_t* pm, pml_t* pml);
	void Mod_JumpView(pmove_t* pm, pml_t* pml);
	void Mod_SaveData(std::vector<jump_data>& storage, pmove_t* pm, bool& hasBounced, bool& hasJumped, bool& hasShotRpg);


}
#endif