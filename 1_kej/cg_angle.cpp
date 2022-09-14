#include "pch.h"

cg::range_t cg::AnglesToRange(float start, float end, float yaw, float fov)
{
	if (fabsf(end - start) > 2 * (float)M_PI)
	{
		range_t const ret = { 0, float(1920.f), false };
		return ret;
	}

	bool split = end > start;
	start = AngleNormalizePI(start - yaw);
	end = AngleNormalizePI(end - yaw);

	if (end > start)
	{
		split = !split;
		float const tmp = start;
		start = end;
		end = tmp;
	}

	range_t const ret = { ProjectionX(start, fov), ProjectionX(end, fov), split };
	return ret;
}
float cg::ProjectionX(float angle, float fov)
{
	float SCREEN_WIDTH = 1920.f;
	float const half_fov_x = (float)DEG2RAD(fov) / 2;
	if (angle >= half_fov_x)
	{
		return 0;
	}
	if (angle <= -half_fov_x)
	{
		return SCREEN_WIDTH;
	}

	return SCREEN_WIDTH / 2 * (1 - angle / half_fov_x);

}
void cg::CG_FillAngleYaw(float start, float end, float yaw, float y, float h, float fov, vec4_t const color)
{

	range_t const range = AnglesToRange(DEG2RAD(start), DEG2RAD(end), DEG2RAD(yaw), fov);
	if (!range.split) {
		r::R_DrawRect("white", range.x1, y, range.x2 - range.x1, h, color);
		//ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(range.x1, y), ImVec2(range.x1 + range.x2 - range.x1, y + h), IM_COL32(color[0], color[1], color[2], color[3]));
	}
	else {
		r::R_DrawRect("white", 0, y, range.x1, h, color);
		r::R_DrawRect("white", range.x2, y, 1920.f - range.x2, h, color);

		//ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, y), ImVec2(range.x1, y + h), IM_COL32(color[0], color[1], color[2], color[3]));
		//ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(range.x2, y), ImVec2(range.x2 + cgs->refdef.width - range.x2, y + h), IM_COL32(color[0], color[1], color[2], color[3]));

	}
}