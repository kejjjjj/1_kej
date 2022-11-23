#pragma once

#ifndef autom
#define autom

#include "pch.h"

namespace cg
{
	inline struct vangle_queue
	{
		bool yes;
		vec3_t src;
		vec3_t dst;
	}vangle_que;

	//actively updating automation data
	struct automation_s {
		bool keybindPressed;
		bool pendingSlide;
		bool currentlySliding;

	};
	struct area500_s
	{
		bool boxExists;
		vec3_t origin;
		vec3_t bounds;
		bool use500;
	};
	inline automation_s automation; //actively updating automation data
	void Mod_A_Strafebot();
	void Mod_A_AutoFPS();
	void Mod_A_AdjustRPG(pmove_t* pm, pml_t* pml);
	void Mod_A_AutoSliding(pmove_t* pm, pml_t* pml);


	inline area500_s box500;
	void Mod_A_500FPS();
	void Mod_A_OnCreate500FPS();
}

#endif