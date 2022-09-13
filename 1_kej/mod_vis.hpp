#pragma once

#ifndef modvis
#define modvis

#include "pch.h"

namespace cg
{
	void Mod_DrawVelocity();
	void Mod_DrawCoordinates();
	void Mod_DrawSurfaceInfo();
	void FPS_CalculateSingleBeatDirection(bool& rightmove, const usercmd_s* cmd);

	void Mod_DrawFPSHelpers();
}

#endif