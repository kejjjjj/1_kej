
#include "pch.h"

void cg::Mod_A_Strafebot()
{
	if (!v::mod_strafebot.isEnabled() || clients->snap.ps.pm_type == PM_UFO || v::mod_strafebot.isEnabled() && (GetAsyncKeyState(v::mod_strafebot_ow.GetInt()) < 0) == true)
		return;

	float optYaw, test;

	//static DWORD old_ms = Sys_Milliseconds();
	//DWORD ms = Sys_Milliseconds();

	if (std::isnan(clients->viewangles[YAW]))
		clients->viewangles[YAW] = 0;
	else if (clients->viewangles[YAW] > 3000 || clients->viewangles[YAW] < -3000)
		clients->viewangles[YAW] = fmodf(clients->viewangles[YAW], 360);

	optYaw = getOptAngle(test, v::mod_strafebot_all.isEnabled());
	if (optYaw == -400.f || std::isnan(optYaw))
		return;

	const usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);


	if (GROUND && cmd->forwardmove <= 0 || GROUND && cmd->rightmove == 0)
		return;


	if (cmd->forwardmove != 0 || cmd->rightmove != 0) {
		float smoothed_yaw = optYaw;

		const int time_since_jumped = jumpanalyzer.serverTime - jumpanalyzer.airTime;
		const int groundTime = jumpanalyzer.serverTime - jumpanalyzer.groundTime;


		if (NOT_GROUND && v::mod_strafebot_smooth.GetFloat() != 1.f || (time_since_jumped > 0 && time_since_jumped < 300 || groundTime < 200) && v::mod_strafebot_bhop_s.GetFloat() != 1.f) {
			const float dist2opt = DistanceToOpt(optYaw, clients->cgameViewangles[YAW]);
			if (time_since_jumped < 400 && dist2opt > 1) {
				CG_ApplySmoothing(clients->cgameViewangles[YAW], optYaw, v::mod_strafebot_bhop_s.GetFloat(), smoothed_yaw);
			}
			else if (dist2opt > 1 && dist2opt < 90)
				CG_ApplySmoothing(clients->cgameViewangles[YAW], optYaw, v::mod_strafebot_smooth.GetFloat(), smoothed_yaw);
			
				
		}

		setYaw(clients->cgameViewangles[YAW], smoothed_yaw);

	}
}
void cg::Mod_A_AutoFPS()
{

	if (!v::mod_autoFPS.isEnabled() && !box500.boxExists && v::mod_autoFPS_hug500.GetInt() == 0)
		return;
	


	if (jumpanalyzer.recommendedFPS != NULL && !analyzer.isPreviewing() && VID_ACTIVE && !jbuilder.isGeneratingMovement())
	{
		dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");

		bool const spaceHeld = (GetAsyncKeyState(VK_SPACE) < 0) == true;

		int fps = jumpanalyzer.recommendedFPS;

		if (!v::mod_autoFPS.isEnabled())
			fps = com_maxfps->current.integer;

		if (v::mod_autoFPS_hug500.GetInt() > 0 && jumpanalyzer.hugging_bounce && !jumpanalyzer.walking && !spaceHeld) {

			switch (v::mod_autoFPS_hug500.GetInt()) {
			case 1:
				fps = 333;
				break;
			case 2:
				fps = 500;
				break;
			case 3:
				fps = 1000;
				break;
			default:
				break;
			}
		}

		if (box500.use500) {
			//r::R_AddCmdDrawTextWithEffects((char*)"500fps", "fonts/objectivefont", r::X(300), r::Y(300), v::mod_velometer.GetArray(3), v::mod_velometer.GetArray(3), 0.f, vec4_t{ 255,0,255,255 }, 3, v::mod_velometer_glow.evar->vecValue, 0, 0, 0, 500, 1000, 2000);

			fps = 500;
		}
		

		if (v::mod_autoFPS.isEnabled()) {
			if (GROUND)
				fps = 125;
			else if (spaceHeld && v::mod_autoFPS_space333.isEnabled())
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

	if (!v::mod_autoslide.isEnabled()) {
		//Com_PrintError(CON_CHANNEL_OBITUARY, "Mod_A_AutoSliding(): shouldn't have been called at this time! (keybind used but the feature itself thinks its unbound?)\n");
		//Com_PrintError(CON_CHANNEL_CONSOLEONLY, "Mod_A_AutoSliding(): shouldn't have been called at this time! (keybind used but the feature itself thinks its unbound?)\n");
		return;
	}

	// force sliding through engine
	const auto methodA = [](pmove_t* pmove, pml_t* pml, DWORD& old_ms, const bool part1) -> void
	{
		hook* a = nullptr;
		if (automation.pendingSlide && (pml->almostGroundPlane || pml->groundPlane)) {
			automation.currentlySliding = true;
			a->write_addr(0x410660, "\xC3", 1); 
			old_ms = Sys_MilliSeconds();
		}
		if (part1)
			return;

		const DWORD ms = Sys_MilliSeconds();


		if ((old_ms + (move->jump == true && v::mod_bhop_nodelay.isEnabled() ? 1 : 100)) < ms) { //allow 100ms to slide and if jump is not held
			old_ms = ms;
			automation.currentlySliding = false;
			a->write_addr(0x410660, "\x83", 1);
			automation.pendingSlide = false;
		}

	};	
	//switch to 15fps
	const auto methodB = [](pmove_t* pm, pml_t* pml, DWORD& old_ms, const bool part1) -> void 
	{
		static int fps_b4_switch = 125;
		if (automation.pendingSlide && !automation.currentlySliding) {
			fps_b4_switch = Dvar_FindMalleableVar("com_maxfps")->current.integer;
			trace_t trace;
			playerState_s* ps = pm->ps;
			vec3_t end(ps->origin[0], ps->origin[1], ps->origin[2]);
			end[2] -= 100;
			
			PM_playerTrace(pm, &trace, ps->origin, pm->mins, pm->maxs, end, ps->clientNum, pm->tracemask);

			if (trace.fraction != 1.f && ps->velocity[2] > 0 && NOT_GROUND) {
				//Com_Printf(CON_CHANNEL_OBITUARY, "hey from 15fps\n");
				automation.currentlySliding = true;
			}

			old_ms = Sys_MilliSeconds();

		}
		else if (automation.currentlySliding) {
			if (v::mod_autoFPS.isEnabled())
				jumpanalyzer.recommendedFPS = 15;
			else
				Dvar_FindMalleableVar("com_maxfps")->current.integer = 15;

			if (old_ms + 250 < Sys_MilliSeconds()) {
				automation.pendingSlide = false;
				automation.currentlySliding = false;

				Dvar_FindMalleableVar("com_maxfps")->current.integer = fps_b4_switch;


			}

		}
	};

	hook* a = 0;
	static DWORD old_ms(0);

	if (automation.keybindPressed & 1 && !automation.currentlySliding) { 
		automation.pendingSlide = true;
		automation.keybindPressed = false;
	}

	bool use_methodA = v::mod_autoslide.GetInt() == 1;

	if (use_methodA)
		methodA(pmove, pml, old_ms, true);
	else
		methodB(pmove, pml, old_ms, true);


	if (!automation.currentlySliding)
		return;
	

	if (use_methodA)
		methodA(pmove, pml, old_ms, false);



}
void cg::Mod_A_OnCreate500FPS()
{
	if (!v::mod_auto500_enabled.isEnabled()) {
		Com_PrintError(CON_CHANNEL_OBITUARY, "500fps area spawning is disabled!\n");
		return;
	}

	trace_t trace;
	vec3_t end;

	AnglesToForward(clients->cgameViewangles, rg->viewOrg, 99999, end);

	CG_TracePoint(vec3_t{ 1,1,1 }, &trace, rg->viewOrg, vec3_t{ -1,-1,-1 }, end, cgs->clientNum, MASK_PLAYERSOLID, 1, 1);

	vec3_t endpos{};

	box500.origin[0] = rg->viewOrg[0] + trace.fraction * (end[0] - rg->viewOrg[0]);
	box500.origin[1] = rg->viewOrg[1] + trace.fraction * (end[1] - rg->viewOrg[1]);
	box500.origin[2] = rg->viewOrg[2] + trace.fraction * (end[2] - rg->viewOrg[2]);

	Com_Printf(CON_CHANNEL_OBITUARY, "^2Spawned at (%.3f, %.3f, %.3f)\n", box500.origin[0], box500.origin[1], box500.origin[2]);

	box500.boxExists = true;

}
void cg::Mod_A_500FPS()
{
	if (!box500.boxExists)
		return;

	static bool isInside(false);

	vec3_t mins, maxs, null{0,0,0};

	VectorCopy(null, mins);
	VectorCopy(null, maxs);

	VectorSubtract(mins, box500.bounds, mins);
	VectorSubtract(maxs, box500.bounds, maxs);

	if (!isInside) { // don't draw the box when we are inside of it
		r::box_s box(box500.origin, mins, maxs);
		box.R_DrawConstructedBox(vec4_t{ 255,0,0,55 });
		box.R_DrawConstructedBoxEdges(vec4_t{ 255,0,0,255 });
	}
	const auto PlayerWithinBounds = [](vec3_t mins, vec3_t maxs) -> bool {


		if (	clients->cgameOrigin[0] > mins[0] && clients->cgameOrigin[0] < maxs[0]
			&&	clients->cgameOrigin[1] > mins[1] && clients->cgameOrigin[1] < maxs[1]
			&&	clients->cgameOrigin[2] > mins[2] && clients->cgameOrigin[2] < maxs[2]) 

			return true;

			

		
		return false;

	};

	VectorCopy(null, mins);
	VectorCopy(null, maxs);

	VectorSubtract(mins, box500.bounds, mins);
	VectorAdd(maxs, box500.bounds, maxs);

	VectorAdd(maxs, box500.origin, maxs);
	VectorAdd(mins, box500.origin, mins);

	isInside = PlayerWithinBounds(mins, maxs);
	box500.use500 = isInside && !jumpanalyzer.hasBounced;


}