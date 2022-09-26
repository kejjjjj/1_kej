
#include "pch.h"


void cg::Mod_A_Strafebot()
{
	if (!v::mod_strafebot.isEnabled() || clients->snap.ps.pm_type == PM_UFO)
		return;

	float optYaw, test;

	//static DWORD old_ms = Sys_Milliseconds();
	//DWORD ms = Sys_Milliseconds();

	if (std::isnan(clients->viewangles[YAW]))
		clients->viewangles[YAW] = 0;
	else if (clients->viewangles[YAW] > 3000 || clients->viewangles[YAW] < -3000)
		clients->viewangles[YAW] = fmodf(clients->viewangles[YAW], 360);

	optYaw = getOptAngle(test);
	if (optYaw == -400.f || std::isnan(optYaw))
		return;

	uint32_t forwardmove = (uint32_t)input->move;
	uint32_t sidemove = (uint32_t)input->strafe;

	if (GROUND && forwardmove <= 0 || GROUND && sidemove == 0)
		return;


	if (sidemove != 0 || forwardmove != 0) {
		setYaw(cgs->refdefViewAngles[YAW], optYaw);	
	}

}
void cg::Mod_A_AutoFPS()
{
	if (!v::mod_autoFPS.isEnabled())
		return;

	if (jumpanalyzer.recommendedFPS != NULL && !analyzer.isPreviewing())
	{
		int fps = jumpanalyzer.recommendedFPS;

		dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");

		if (v::mod_autoFPS_space333.isEnabled())
			if (GetAsyncKeyState(VK_SPACE) < 0)
				fps = 333;

		if(com_maxfps)
			com_maxfps->current.integer = fps;
	}



}