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
void cg::setYaw(float ref, float ang)
{
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	clients->viewangles[1] += ref;

}
void cg::setPitch(float ref, float ang)
{
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	clients->viewangles[0] += ref;

}
void cg::setRoll(float ref, float ang)
{
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	clients->viewangles[2] += ref;

}
void cg::CG_SetPlayerAngles(vec3_t source, vec3_t target)
{
	setPitch(source[0], target[0]);
	setYaw(source[1], target[1]);
	setRoll(source[2], target[2]);
}
float cg::R_getOptAngle(const bool rightmove, float& diff)
{

	//usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);

	char* forwardmove = &input->move;
	char* sidemove = &input->strafe;


	float _speed = glm::length(glm::vec2(clients->cgameVelocity[0], clients->cgameVelocity[1]));

	if (_speed < 1)
		return -400.0;

	float yaw = clients->cgameViewangles[YAW];
	float g_speed = (float)cgs->nextSnap->ps.speed;
	const float FPS = 1000.f / (cgs->frametime == NULL ? 1 : cgs->frametime);

	const float accel = FPS / g_speed;

	if (_speed < 190)
		g_speed = 190 - (190 - _speed);
	else if (GROUND)
		g_speed = 270.f;

	const float velocitydirection = atan2(clients->cgameVelocity[1], clients->cgameVelocity[0]) * 180.f / PI;
	const float accelerationAng = atan2(-(int)*sidemove, (int)*forwardmove) * 180.f / PI;
	diff = acos((g_speed - accel) / _speed) * 180.f / PI;
	const float minAngle = acos(g_speed / _speed) * 180.f / PI;

	if (mod_fps.DistanceToTransferZone > 45.f)
		diff = minAngle + accel;

	float delta = yaw;


	if (rightmove) {
		delta = (velocitydirection - diff - accelerationAng);
		//_opt = delta - yaw;
	}
	else{
		delta = (velocitydirection + diff - accelerationAng);
		//_opt = delta - yaw;
	}
	diff /= 2;
	yaw = delta;

	return yaw;
}
float cg::getOptAngle(float& _opt)
{

	//usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);

	char* forwardmove = &input->move;
	char* sidemove = &input->strafe;


	float _speed = glm::length(glm::vec2(clients->cgameVelocity[0], clients->cgameVelocity[1]));

	if (_speed < 1)
		return -400.0;

	float yaw = clients->cgameViewangles[YAW];
	float g_speed = (float)cgs->nextSnap->ps.speed;
	const float FPS = 1000.f / (cgs->frametime == NULL ? 1 : cgs->frametime);

	const float accel = FPS / g_speed;

	if (_speed < 190)
		g_speed = 190 - (190 - _speed);
	else if (GROUND)
		g_speed = 270.f;

	const float velocitydirection = atan2(clients->cgameVelocity[1], clients->cgameVelocity[0]) * 180.f / PI;
	const float accelerationAng = atan2(-(int)*sidemove, (int)*forwardmove) * 180.f / PI;
	float diff = acos((g_speed - accel) / _speed) * 180.f / PI;
	const float minAngle = acos(g_speed / _speed) * 180.f / PI;

	if (mod_fps.DistanceToTransferZone > 45.f)
		diff = minAngle + accel;

	float delta = yaw;


	if ((int)*sidemove > 0 || WE || SE) {
		delta = (velocitydirection - diff - accelerationAng);
		_opt = delta - yaw;
	}
	else if ((int)*sidemove < 0 || WQ || SQ) {
		delta = (velocitydirection + diff - accelerationAng);
		_opt = delta - yaw;
	}
	yaw = delta;

	return yaw;
}
float cg::DistanceToOpt(float delta, const float& yaw)
{
	return fabs(yaw - delta);
}