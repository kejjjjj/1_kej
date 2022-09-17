#pragma once

#ifndef cgangle
#define cgangle

#include "pch.h"

namespace cg
{
	struct range_t
	{
		float x1;
		float x2;
		bool split;
	};

	float ProjectionX(float angle, float fov);
	range_t AnglesToRange(float start, float end, float yaw, float fov);
	void CG_FillAngleYaw(float start, float end, float yaw, float y, float h, float fov, const vec4_t color);

	void setYaw(float ref, float ang);
	void setPitch(float ref, float ang);
	void setRoll(float ref, float ang);
	void CG_SetPlayerAngles(vec3_t source, vec3_t target);

	float getOptAngle(float& delta);
	float R_getOptAngle(const bool rightmove, float& delta); //more suited for visual stuff
	float DistanceToOpt(float delta, const float& yaw);

	enum axis_e {
		yNegative = -2,
		xNegative = -1,
		xPositive = 1,
		yPositive = 2
	};

	struct axis_s {
		float angle;
		axis_e axis;
	};

	axis_s CG_GetNearestWorldAxisFromYaw();
	axis_s CG_GetNearestWorldAxisFromYaw(float yaw);
}

#endif