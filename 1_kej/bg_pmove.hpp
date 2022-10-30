#pragma once

#ifndef slidemove
#define slidemove

#include "pch.h"

namespace cg
{
	//typedef void(*Pmove_h)(pmove_t* pmove);
	inline void (*PmoveSingle)(pmove_t* pm) = (void(__cdecl*)(pmove_t*))0x4143A0;

	inline void(__cdecl* PM_WalkMove_f)(pmove_t* pm, pml_t* pml);
	inline void(__cdecl* PM_AirMove_f)(pmove_t* pm, pml_t* pml);
	inline void(__cdecl* PM_UFOMove_f)(pmove_t* pm, pml_t* pml);
	inline void(__cdecl* PM_Weapon_f)(pml_t* pml, pmove_t* pm);
	inline void(__cdecl* PM_OverBounce_f)();
	inline bool(*CM_IsEdgeWalkable_f)(int edgeIndex, int triIndex);
	inline void (*PM_ProjectVelocity_f)(float* normal, float* velIn, float* velOut);
	inline void (*PM_BounceHeight_f)();
	inline void (*PM_BounceSteepness_f)();

	inline BOOL(*PM_SlideMove_f)(pmove_t* pm, pml_t* pml, int gravity);


	inline void(*Pmove_f)(pmove_t* pmove);


	void PM_WalkMove(pmove_t* pm, pml_t* pml);
	void PM_AirMove(pmove_t* pm, pml_t* pml);
	void PM_UFOMove(pmove_t* pm, pml_t* pml);
	void PM_Weapon(pml_t* pml, pmove_t* pm);
	bool CM_IsEdgeWalkable(int edgeIndex, int triIndex);
	BOOL PM_SlideMove(pmove_t* pm, pml_t* pml, int gravity);

	bool PM_CanBeBounced(float* normal, float* velIn);
	void PM_ProjectVelocity(float* normal, float* velIn, float* velOut);
	void PM_BounceHeight();
	void PM_BounceSteepness();


	void Pmove(pmove_t* pmove);

	inline void(*PmoveSingle_stub_f)();
	void PmoveSingle_stub();

	void PM_ModCode(pml_t* pml, pmove_t* pm);
	void PM_OverBounce(pmove_t* pm, pml_t* pml);
	void PM_OverBounce_stub();

	void BG_AddPredictableEventToPlayerstate(playerState_s* ps, unsigned __int8 newEvent, unsigned int eventParm);

	inline pmove_t h_pm, *glob_pm;
	inline pml_t h_pml, *glob_pml;
	inline playerState_s h_ps;



	struct fps_zones_s
	{
		float fps125;
		float fps200;
		float fps250;
		float fps333;
		float length125;
		float length200;
		float length250;
		float length333;
	};

	inline fps_zones_s fps_zones;
}

#endif