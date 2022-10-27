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
void cg::CG_FillAngleYaw(float start, float end, float yaw, float y, float h, float fov, vec4_t const color, bool useImGui)
{

	range_t const range = AnglesToRange(DEG2RAD(start), DEG2RAD(end), DEG2RAD(yaw), fov);

	const float widthOffs = v::mod_fps_transferz.GetArray(5);
	const float minX = widthOffs;
	const float maxX = 1920.f - widthOffs;

	float x1 = range.x1 < minX ? minX : range.x1;
	float x2 = range.x2 - range.x1;

	
	x1 = range.x1 > maxX ? maxX : x1;
	x2 = range.x2 > maxX ? maxX - x1 : x2;
	

	if (!range.split) {
		//r::R_DrawRect("white", range.x1, y, range.x2 - range.x1, h, color);
		if(useImGui)
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(r::X(x1), r::Y(y)), ImVec2(r::X(ImClamp(range.x2, minX, maxX)), r::Y(y + h)), ImColor(color[0], color[1], color[2], color[3]));
		else
			r::R_DrawRect("white", range.x1, y, range.x2 - range.x1, h, color);
	}
	else {
		if (useImGui) {
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(r::X(minX), r::Y(y)), ImVec2(r::X(x1), r::Y(y + h)), ImColor(color[0], color[1], color[2], color[3]));
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(r::X(ImClamp(range.x2, minX, maxX)), r::Y(y)), ImVec2(r::X(ImClamp((float)cgs->refdef.width, minX, maxX)), r::Y(y + h)), ImColor(color[0], color[1], color[2], color[3]));
		}
		else {
			r::R_DrawRect("white", 0, y, range.x1, h, color);
			r::R_DrawRect("white", range.x2, y, 1920.f - range.x2, h, color);
		}
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
//more suited for visual stuff
float cg::R_getOptAngle(const bool rightmove, float& diff)
{

	//usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);

	char* forwardmove = &input->move;
	char* sidemove = &input->strafe;


	float _speed = glm::length(glm::vec2(clients->cgameVelocity[0], clients->cgameVelocity[1]));

	if (_speed < 1)
		return -400.0;

	float yaw = ps_loc->viewangles[YAW];
	float g_speed = (float)cgs->snap->ps.speed;
	const float FPS = (float)Dvar_FindMalleableVar("com_maxfps")->current.integer;

	float accel = FPS / g_speed;

	if (_speed < 190)
		g_speed = 190.f - (190.f - _speed);
	else if (GROUND)
		g_speed = 224.f;

	const double velocitydirection = atan2(clients->cgameVelocity[1], clients->cgameVelocity[0]) * 180.f / PI;
	const double accelerationAng = atan2(-(int)*sidemove, (int)*forwardmove) * 180.f / PI;
	diff = acos((g_speed - accel) / _speed) * 180.f / PI;
	//const float minAngle = acos(g_speed / _speed) * 180.f / PI;

	if (jumpanalyzer.recommendedFPS == 125)
		diff += accel;

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
	if (!glob_pm || !glob_pml)
		return -400.0;

	if (!glob_pm->ps)
		return -400.0;

	usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);

	char forwardmove = cmd->forwardmove;
	char rightmove = cmd->rightmove;

	const bool all_techs = v::mod_strafebot_all.isEnabled();

	float _speed = glm::length(glm::vec2(glob_pm->ps->velocity[1], glob_pm->ps->velocity[0]));

	if (_speed < 1 || !all_techs && forwardmove != 127 && rightmove != 0 || analyzer.isSegmenting() && !analyzer.segmenterData.isReady) 
		return -400.0;

	

	if (all_techs)
		forwardmove = cmd->forwardmove;
	else forwardmove = 127;


	float yaw = glob_pm->ps->viewangles[YAW];
	float g_speed = (float)clients->snap.ps.speed;
	const float FPS = (float)Dvar_FindMalleableVar("com_maxfps")->current.integer;

	float accel = FPS / g_speed;

	//float accel = g_speed * jumpanalyzer.frametime;

	if (jumpanalyzer.recommendedFPS == 125)
		accel = g_speed / FPS;

	//float r = sqrtf();

	if (_speed < 190)
		g_speed = 190.f - (190.f - _speed);
	else if (GROUND)
		g_speed = 224.f;

	const double velocitydirection = atan2(glob_pm->ps->velocity[1], glob_pm->ps->velocity[0]) * 180.f / PI;
	const double accelerationAng = atan2(-rightmove, forwardmove) * 180.f / PI;
	double diff = acos((g_speed - accel) / _speed) * 180.f / PI;
	//const float minAngle = acos(g_speed / _speed) * 180.f / PI;

	//if (jumpanalyzer.recommendedFPS == 125)
	//	diff += accel; 

	float delta = yaw;


	if (rightmove > 0 || WE && all_techs || SE && all_techs) {
		delta = (velocitydirection - diff - accelerationAng);
		_opt = delta - yaw;
	}
	else if (rightmove < 0 || WQ && all_techs || SQ && all_techs) {
		delta = (velocitydirection + diff - accelerationAng);
		_opt = delta - yaw;
	}
	yaw = delta;

	

	return yaw;
}
float cg::getOptForAnalyzer(jump_data* data, bool onGround)
{
	const float _speed = glm::length(glm::vec2(data->velocity[0], data->velocity[1]));

	if (_speed < 1)
		return -400.0;

	float yaw = data->angles[YAW];
	float g_speed = (float)cgs->snap->ps.speed;
	const float FPS = (float)data->FPS;

	float accel = FPS / g_speed;

	if (jumpanalyzer.recommendedFPS == 125)
		accel = g_speed / FPS;

	if (_speed < 190)
		g_speed = 190.f - (190.f - _speed);
	else if (onGround && _speed < 370)
		g_speed = 224.f;

	const float velocitydirection = atan2(data->velocity[1], data->velocity[0]) * 180.f / PI;
	const float accelerationAng = atan2(-(int)data->rightmove, (int)data->forwardmove) * 180.f / PI;
	float diff = acos((g_speed - accel) / _speed) * 180.f / PI;
	//const float minAngle = acos(g_speed / _speed) * 180.f / PI;

	//if (jumpanalyzer.recommendedFPS == 125)
	//	diff += accel;

	float delta = yaw;


	if ((int)data->rightmove > 0) {
		delta = (velocitydirection - diff - accelerationAng);
	}
	else if ((int)data->rightmove < 0) {
		delta = (velocitydirection + diff - accelerationAng);
	}
	yaw = delta;

	return yaw;
}
float cg::DistanceToOpt(float delta, const float& yaw)
{
	float opt = fabs(yaw - delta);

	opt = opt > 90 == true ? 360.f - opt : opt;
	return opt;

}

axis_s cg::CG_GetNearestWorldAxisFromYaw(float yawangle)
{
	if (yawangle > 180 || yawangle < -180)
		yawangle = AngleNormalize180(yawangle);

	axis_s ax;


	if (yawangle >= 135 || yawangle <= -135) {
		ax.axis = axis_e::xNegative;
		ax.angle = 180;
		return ax;
	}
	else if (yawangle <= -45 && yawangle >= -135) {
		ax.axis = axis_e::yNegative;
		ax.angle = 270;
		return ax;
	}
	else if (yawangle >= 45 && yawangle <= 135) {
		ax.axis = axis_e::yPositive;
		ax.angle = 90;
		return ax;
	}
	ax.axis = axis_e::xPositive;
	ax.angle = 0;
	return ax;  


}
axis_s cg::CG_GetNearestWorldAxisFromYaw()
{
	axis_s ax;

	const float yawangle = clients->cgameViewangles[YAW];

	if (yawangle >= 135 || yawangle <= -135) {
		ax.axis = axis_e::xNegative;
		ax.angle = 180;
		return ax;
	}
	else if (yawangle <= -45 && yawangle >= -135) {
		ax.axis = axis_e::yNegative;
		ax.angle = 270;
		return ax;
	}
	else if (yawangle >= 45 && yawangle <= 135) {
		ax.axis = axis_e::yPositive;
		ax.angle = 90;
		return ax;
	}
	ax.axis = axis_e::xPositive;
	ax.angle = 0;
	return ax; 

}