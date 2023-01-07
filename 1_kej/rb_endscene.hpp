#pragma once

#ifndef rbendscn
#define rbendscn

#include "pch.h"

namespace r {

	inline char(*RB_DrawDebug_f)(GfxViewParms* viewParms);
	char RB_DrawDebug(GfxViewParms* viewParms);
	int RB_BeginSurface(MaterialTechniqueType tech, Material* material);
	void RB_EndTessSurface();
	void RB_SetPolyVertice(const vec3_t pos, const BYTE* col, const int vert, const int index);
	void RB_DrawPolyInteriors(int n_points, const vec3_t* points, const BYTE* color, bool two_sided = false, bool depthTest = false);
	char RB_DrawLines3D(int count, int width, GfxPointVertex* verts, char depthTest);
	void RB_DrawTriangleOutline(vec3_t points[3], vec4_t color, int width = 3, bool depthTest = false);
	int RB_AddDebugLine(GfxPointVertex* verts, char depthTest, const vec_t* start, vec_t* end, const vec_t* color, int vertCount);
	void R_ConvertColorToBytes(const vec4_t in, uint8_t* out);
}
#endif