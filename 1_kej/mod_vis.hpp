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

	void Mod_DrawEvents();

	void Mod_DrawVelocity();
	void Mod_DrawCoordinates();
	void Mod_DrawSurfaceInfo();
	void Mod_DrawVelocityDirection();
	void Mod_DrawWorldAxes();
	void FPS_CalculateSingleBeatDirection(bool& rightmove, const usercmd_s* cmd);
	void Mod_DrawFPSHelpers();
	void Mod_GetAccelerationAngles(const bool rightmove, vec2_t accel_angles);
	void Mod_DrawAngleHelper();
	void Mod_DrawCurveSpeed();
	void Mod_DrawJumpPath();
	void Mod_DrawJumpHitbox();
	void Mod_DrawJumpDirection();

	void Mod_B_DrawPath();

	inline fps_s mod_fps;
}

#endif