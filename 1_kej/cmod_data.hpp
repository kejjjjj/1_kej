#pragma once

#ifndef cmoddata
#define cmoddata

#include "pch.h"

namespace cg
{
	void CMod_GetBrushOriginFromBounds(cbrush_t* brush, vec3_t out);
	cbrush_t* CMod_FindBrushByOrigin(vec3_t origin); //assumes origin is inside of the brush

	void CMod_HighlightSelected();

}


#endif