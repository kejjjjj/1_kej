#pragma once


#ifndef g_trace
#define g_trace

#include "pch.h"

namespace cg
{
	//Allows script to do a point trace with MASK_SHOT.
	char CG_BulletTrace(BulletTraceResults* trace, BulletFireParams* fireParams, centity_s* ignore, int depthSurfaceType);
	char BG_AdvanceTrace(BulletTraceResults* br, BulletFireParams* bpp, float a3);
	void __cdecl CG_TracePoint(const vec3_t maxs, trace_t* trace, const vec3_t start, const vec3_t mins, const vec3_t end, int entityNum, int contentMask, int locational, int staticModels);

	//basically just CG_TracePoint except the last 2 params are set to 0
	inline void (*CG_Trace)(trace_t* result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int skipEntity, int tracemask) = (void(__cdecl*)(trace_t*, const vec3_t, const vec3_t, const vec3_t, const vec3_t, int, int))0x45A230;
	int PM_playerTrace(pmove_t* pm, trace_t* trace, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask);
	pmove_t* PM_AddTouchEnt(pmove_t* pm, int groundEntityNum);

}


#endif