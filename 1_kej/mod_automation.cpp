
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

	const usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);


	if (GROUND && cmd->forwardmove <= 0 || GROUND && cmd->rightmove == 0)
		return;


	if (cmd->forwardmove != 0 || cmd->rightmove != 0) {
		setYaw(clients->cgameViewangles[YAW], optYaw);

	}
}
void cg::Mod_A_AutoFPS()
{
	if (!v::mod_autoFPS.isEnabled())
		return;
	


	if (jumpanalyzer.recommendedFPS != NULL && !analyzer.isPreviewing() && VID_ACTIVE)
	{
		int fps = jumpanalyzer.recommendedFPS;

		dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");

		if (v::mod_autoFPS_space333.isEnabled()) {
			if (GROUND)
				fps = 125;
			else if (GetAsyncKeyState(VK_SPACE) < 0)
				fps = 333;

			//if (mod_fps.DistanceToTransferZone > 45 && jumpanalyzer.recommendedFPS == 250)
			//	fps = 200;

		}

		if(com_maxfps)
			com_maxfps->current.integer = fps;
	}



}
void cg::Mod_A_AdjustRPG(pmove_t* pm, pml_t* pml)
{

	if (!v::mod_autoanglerpg.isEnabled())
		return;

	static bool rpg_isangling(false);
	static float angleEveryFrame(0);
	int rpg_indx = BG_FindWeaponIndexForName("rpg_mp");



	if(pm->ps->weapon != rpg_indx)
		rpg_indx = BG_FindWeaponIndexForName("rpg_sustain_mp");




	if (pm->ps->weapon == rpg_indx && (pm->cmd.buttons & 1) && pm->ps->weaponstate == WEAPON_READY) {
		rpg_isangling = true;
		float DistanceToDown = glm::distance(pm->ps->viewangles[PITCH], 85.f);
		angleEveryFrame = DistanceToDown / 1000.f * (500.f / (float)Dvar_FindMalleableVar("com_maxfps")->current.integer);
		//Com_Printf(CON_CHANNEL_OBITUARY, "each frame: %.3f\n", angleEveryFrame);
	}

	if (!rpg_isangling)
		return;

	clients->viewangles[PITCH] += angleEveryFrame;

	if (pm->ps->viewangles[PITCH] >= 85 || pm->ps->weaponstate == WEAPON_RELOADING)
		rpg_isangling = false;

}
void cg::Mod_A_AutoSliding(pmove_t* pmove, pml_t* pml)
{
	hook* a = 0;
	static DWORD old_ms(0);

	if (automation.keybindPressed & 1 && !automation.currentlySliding) { 
		automation.pendingSlide = true;
		automation.keybindPressed = false;
	}

	
	if (automation.pendingSlide && (pml->almostGroundPlane || pml->groundPlane)) {
		automation.currentlySliding = true;
		a->write_addr(0x410660, "\xC3", 1);
		old_ms = Sys_MilliSeconds();
	}

	if (!automation.currentlySliding)
		return;

	const DWORD ms = Sys_MilliSeconds();
	

	if ((old_ms + (move->jump == true && v::mod_bhop_nodelay.isEnabled() ? 0.1f : 100)) < ms) { //allow 100ms to slide and if jump is held, then stop slide instantly
		old_ms = ms;
		automation.currentlySliding = false;
		a->write_addr(0x410660, "\x83", 1);
		automation.pendingSlide = false;
	}




}