#pragma once

#ifndef cmoddata
#define cmoddata

#include "pch.h"

struct v3
{
	float x, y, z;
};

namespace cg
{
	void CMod_GetBrushOriginFromBounds(const cbrush_t* brush, vec3_t out);
	cbrush_t* CMod_FindBrushByOrigin(vec3_t origin); //assumes origin is inside of the brush

	void CMod_HighlightSelected();

	void CMod_OnHighlightTriangle();
	void CMod_OnHighlightLeafBrushNode();

	cplane_s* FindPlaneFromPoints(const vec3_t A, const vec3_t b, const vec3_t c);
}


#endif