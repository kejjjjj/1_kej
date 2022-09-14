#pragma once

#ifndef modvis
#define modvis

#include "pch.h"

namespace cg
{
	struct fps_s
	{
		float DistanceToTransferZone;
	};

	void Mod_DrawVelocity();
	void Mod_DrawCoordinates();
	void Mod_DrawSurfaceInfo();
	void FPS_CalculateSingleBeatDirection(bool& rightmove, const usercmd_s* cmd);

	void Mod_DrawFPSHelpers();

	inline fps_s mod_fps;
}

#endif