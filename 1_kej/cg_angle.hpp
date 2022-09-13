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
}

#endif