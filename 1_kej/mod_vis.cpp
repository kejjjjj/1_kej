#include "pch.h"


void cg::Mod_DrawVelocity()
{
	if (!v::mod_velometer.isEnabled())
		return;

	const int32_t velocity = (int32_t)glm::length(glm::vec2(cg::clients->cgameVelocity[0], cg::clients->cgameVelocity[1]));
	static int32_t velocity_prev_frame = velocity;

	static DWORD ms = Sys_MilliSeconds();
	const DWORD timePassed = Sys_MilliSeconds() - ms;

	static glm::vec4 col{};

	if (timePassed > (1000.f / cgs->frametime) / 10) {
		ms = Sys_MilliSeconds();
		col.a = 255;
		if (velocity > velocity_prev_frame) {
			col.r = 0;
			col.g = 255;
			col.b = 0;
		}
		else if (velocity < velocity_prev_frame) {
			col.r = 255;
			col.g = 0;
			col.b = 0;
		}
		else {
			col.r = 255;
			col.g = 255;
			col.b = 0;
		}

		velocity_prev_frame = velocity;

	}

	char buffer[10];
	sprintf_s(buffer, "%i", velocity);
	r::R_DrawText(buffer, v::mod_velometer.evar->arrayValue[1], v::mod_velometer.evar->arrayValue[2], v::mod_velometer.evar->arrayValue[3], v::mod_velometer.evar->arrayValue[3], 0, (float*)&col, 0);
}
void cg::Mod_DrawCoordinates()
{
	if (!v::mod_coordinates.isEnabled())
		return;

	char buffer[128];
	static glm::vec4 col{};

	sprintf_s(buffer, "x:     %.6f\ny:     %.6f\nz:     %.6f\nyaw: %.6f", clients->cgameOrigin[0], clients->cgameOrigin[1], clients->cgameOrigin[2], cgs->refdefViewAngles[YAW]);

	col.r = 0;
	col.g = 255;
	col.b = 0;
	col.w = 255;

	if (clients->cgameOrigin[0] == (int)clients->cgameOrigin[0] || clients->cgameOrigin[1] == (int)clients->cgameOrigin[1])
		col.b = 255;

	r::R_DrawText(buffer, v::mod_coordinates.evar->arrayValue[1], v::mod_coordinates.evar->arrayValue[2], v::mod_coordinates.evar->arrayValue[3], v::mod_coordinates.evar->arrayValue[3], 0, (float*)&col, 0);

}
#define BANGLE2COLOR( x )  ( (int)( ( x ) * 255.f / 35 ) & 255 )

void cg::Mod_DrawSurfaceInfo()
{
	if (!v::mod_elevatable_surf.isEnabled() && !v::mod_bounceable_surf.isEnabled())
		return;

	trace_t trace;
	const vec3_t mins = { -1,-1,-1 };
	const vec3_t maxs = { 1, 1, 1 };
	vec3_t angles;

	const auto AnglesToForward = [](vec3_t angles, vec3_t out) -> void {
		float fwd = angles[1] * 0.01745329238474369;
		const float ycos = cos(fwd);
		const float ysin = sin(fwd);

		fwd = angles[0] * 0.01745329238474369;
		const float xcos = cos(fwd);
		const float xsin = sin(fwd);

		out[0] = xcos * ycos;
		out[1] = xcos * ysin;
		out[2] = -xsin;
	};
	AnglesToForward(clients->cgameViewangles, angles);
	VectorScale(angles, 99999, angles);
	CG_TracePoint(maxs, &trace, rg->viewOrg, mins, angles, cgs->clientNum, MASK_PLAYERSOLID, 0, 1);

	const float normalX = trace.normal[0] >= 0.f ? trace.normal[0] : -trace.normal[0];
	const float normalY = trace.normal[1] >= 0.f ? trace.normal[1] : -trace.normal[1];


	if (trace.normal[2] >= .3f && trace.normal[2] <= .7f && v::mod_bounceable_surf.isEnabled()) {
		char buffer[64];
		const float bAngle = (90.f + trace.normal[2] * 90.f) - 117;
		const float _col = (bAngle / 36.f);
		sprintf_s(buffer, "bounce (+%.6f)", bAngle); //as long as it gives an idea of the angle :blush:

		vec4_t col;
		col[0] = 0.f + (_col);
		col[1] = 1.f - (_col);
		col[2] = 0.f;
		col[3] = 1.f;

		r::R_DrawText(buffer, 960, 700, 1.6f, 1.6f, 0.f, col, 0);

	}
	else if ((normalX == 1.f || normalY == 1.f) && v::mod_elevatable_surf.isEnabled()) {
		r::R_DrawText("elevator", 960, 700, 1.6f, 1.6f, 0.f, vec4_t{0,1,0,1}, 0); //can never be true when bounce is true, so draw on top of it

	}
}
//#define BAR_START_Y 490
//#define BAR_HEIGHT 10
void cg::Mod_DrawFPSHelpers()
{
	constexpr static float length_marker250 = 1.f;

	static bool rightmove{};

	const usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);

	if (cmd->rightmove > 0)
		rightmove = true;
	else if (cmd->rightmove < 0)
		rightmove = false;

	FPS_CalculateSingleBeatDirection(rightmove, cmd);

	float yaw = clients->cgameViewangles[YAW] > 0 ? clients->cgameViewangles[YAW] : 180.f - clients->cgameViewangles[YAW] * -1; //mirror the yaw
	float aa = atan2(-(int)cmd->rightmove, (int)cmd->forwardmove) * 57.2957795f;

	aa > 0 ? aa -= 45 : aa += 45;

	static const float m250 = 86.f;
	vec2_t marker250 = { m250, 90.f + m250 };

	if (rightmove) {
		marker250[0] = 189.f - marker250[0];
		marker250[1] = 189.f - marker250[1];
	}

	yaw = AngleNormalize180(yaw += aa);
	if (yaw < 0)
		yaw = 180.f - fabs(yaw);

	const dvar_s* _fov = Dvar_FindMalleableVar("cg_fov");
	const dvar_s* fovscale = Dvar_FindMalleableVar("cg_fovscale");

	float fov = _fov->current.value * fovscale->current.value * v::mod_fps_transferz.evar->arrayValue[3];

	const bool isInverted = clients->cgameViewangles[YAW] < fov || clients->cgameViewangles[YAW] > 180.f - fov;
	
	//r::R_DrawRect("white", 0, BAR_START_Y, 1920, 10, vec4_t{ 1,1,1,100 });

	const float BAR_START_Y = v::mod_fps_transferz.evar->arrayValue[1];
	const float BAR_HEIGHT = v::mod_fps_transferz.evar->arrayValue[2];


	if (v::mod_fps_transferz.evar->arrayValue[0] != NULL) {
		if (isInverted) {
			CG_FillAngleYaw(-180.f + marker250[0], -180.f + (marker250[0] + length_marker250), yaw, BAR_START_Y, BAR_HEIGHT, fov, vec4_t{ 1,0,0,255 });
			CG_FillAngleYaw(-180.f + marker250[1], -180.f + (marker250[1] + length_marker250), yaw, BAR_START_Y, BAR_HEIGHT, fov, vec4_t{ 1,0,0,255 });
		}

		CG_FillAngleYaw(marker250[0], (marker250[0] + length_marker250), yaw, BAR_START_Y, BAR_HEIGHT, fov, vec4_t{ 1,0,0,255 });
		CG_FillAngleYaw(marker250[1], (marker250[1] + length_marker250), yaw, BAR_START_Y, BAR_HEIGHT, fov, vec4_t{ 1,0,0,255 });

		r::R_DrawRect("white", 958, BAR_START_Y - 10, 4, BAR_HEIGHT + 20, vec4_t{ 1,1,1,255 });
	}
}
void cg::FPS_CalculateSingleBeatDirection(bool& rightmove, const usercmd_s* cmd)
{
	static uint16_t frames = NULL;
	static vec_t oldYaw = NULL;
	vec_t newYaw = cgs->refdefViewAngles[YAW];

	frames += 1;

	if (frames >= 4) {
		frames = 0;

		if (oldYaw < newYaw && cmd->forwardmove != 0 && cmd->rightmove == 0 && rightmove)
			rightmove = false;
		else if (oldYaw > newYaw && cmd->forwardmove != 0 && cmd->rightmove == 0 && !rightmove)
			rightmove = true;
		oldYaw = newYaw;
	}
}