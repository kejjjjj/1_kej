#pragma once

#ifndef cmbrush
#define cmbrush

#include "pch.h"

namespace cg
{
	void CM_BuildAxialPlanes(float *planes, const cbrush_t* mins);
	void Phys_GetWindingForBrushFace(unsigned int brushSide, cbrush_t* brush, Poly* outPolys, const float(*planes)[4], signed int maxVerts);
}

#endif