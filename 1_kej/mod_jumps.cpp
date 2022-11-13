
#include "pch.h"

void cg::Mod_HitAnalyzer(pmove_t* pm, pml_t* pml)
{
	//if (!v::mod_hitanalyzer.isEnabled() && !v::mod_jumpanalyzer.isEnabled() && !v::mod_rpg_timing.isEnabled() && !v::mod_rpg_angle.isEnabled())
	//	return;

	

	static bool wait_ground = NULL;

	if (GROUND) {
		wait_ground = false;

		if (v::mod_jumpanalyzer.isEnabled()) {
			if (cg::jumpanalyzer.hasJumped && cg::jumpanalyzer.hasBounced && !analyzer.isPreviewing()) {
				Com_Printf(CON_CHANNEL_OBITUARY, "^6jump velocity: ^2%i\n", cg::jumpanalyzer.jumpVelocity);
				Com_Printf(CON_CHANNEL_OBITUARY, "^6bounce velocity: ^2%i\n", cg::jumpanalyzer.bounceVelocity);
			}

		}
		memset(&cg::jumpanalyzer, 0, sizeof(cg::jumpanalyzer_s));

	}
	if (pml->groundTrace.normal[2] > .3f && pml->groundTrace.normal[2] < .7f) {
		jumpanalyzer.hugging_bounce = true;
		if ((pm->ps->pm_flags & PMF_JUMPING) == 0 && NOT_GROUND && pm->ps->jumpTime > 500) {

			if (!wait_ground) {
				jumpanalyzer.bounceTime = pm->ps->commandTime;

				const int32_t hit_velocity = (int32_t)glm::length(glm::vec2(pm->ps->velocity[0], pm->ps->velocity[1]));
				const int32_t old_vel = (int32_t)glm::length(glm::vec2(pm->ps->oldVelocity[0], pm->ps->oldVelocity[1]));
				jumpanalyzer.bounceVelocity = old_vel;
				jumpanalyzer.hasBounced = true;
				wait_ground = true;

				const int32_t difference = hit_velocity - old_vel;

				if (v::mod_hitanalyzer.isEnabled() && !analyzer.isPreviewing())
					Com_Printf(CON_CHANNEL_OBITUARY, "^2%i\n", difference);
			}


		}
	}else
		jumpanalyzer.hugging_bounce = false;

}
void cg::Mod_JumpAnalyzer(pmove_t* pm, pml_t* pml)
{

	static bool wait_ground = NULL;

	if (GROUND && wait_ground) {
		wait_ground = false;

	}

	if ((pm->cmd.buttons & 1024) && !wait_ground) {
		jumpanalyzer.jumpVelocity = (int32_t)glm::length(glm::vec2(pm->ps->velocity[0], pm->ps->velocity[1]));
		jumpanalyzer.hasJumped = true;
		wait_ground = true;
	}
}
void cg::Mod_RPGAnalyzer(pmove_t* pm, pml_t* pml)
{
	const bool timing_enabled = v::mod_rpg_timing.isEnabled();

	if (!timing_enabled && !v::mod_rpg_angle.isEnabled())
		return;

	static bool wait_until_fired = false, wait_ground;
	static bool check_fire_state_next_frame(0);

	if (GROUND) {
		wait_ground = false;
		check_fire_state_next_frame = false;
	}
	if ((pm->cmd.buttons & 1) && (pm->oldcmd.buttons & 1) == 0 && !wait_until_fired && !wait_ground && NOT_GROUND) {

		int32_t rpg = BG_FindWeaponIndexForName("rpg_mp");


		if (pm->ps->weapon != rpg)
			rpg = BG_FindWeaponIndexForName("rpg_sustain_mp");

		if (pm->ps->weapon == rpg) {
			wait_until_fired = true;
			wait_ground = true;
		}
	} else if (wait_until_fired && jumpanalyzer.weapon_cant_fire) {
		if (check_fire_state_next_frame) {
			if (jumpanalyzer.hasBounced) {
				const bool timing_enabled = v::mod_rpg_timing.isEnabled();
				const int time_since_bounced = pm->ps->commandTime - jumpanalyzer.bounceTime;
				if (time_since_bounced > 0 && timing_enabled)
					Com_Printf(CON_CHANNEL_OBITUARY, "rpg: +%i\n", time_since_bounced);

				if(v::mod_rpg_angle.isEnabled())
					Com_Printf(CON_CHANNEL_OBITUARY, "^3pitch: %.3f\n", pm->ps->viewangles[PITCH]);
		

			}
			else {
				if(timing_enabled)
					Com_Printf(CON_CHANNEL_OBITUARY, "^1pre-bounce (+%i)\n", (int)(pm->cmd.buttons - pm->ps->jumpTime));


				wait_until_fired = false;
			}
			wait_until_fired = false;

		}
		check_fire_state_next_frame = !check_fire_state_next_frame;

	}

}
int32_t cg::Mod_RecommendedFPS(float yaw, char forwardmove, char rightmove)
{
	static bool _rightmove{};

	if (rightmove > 0)
		_rightmove = true;
	else if (rightmove < 0)
		_rightmove = false;

	yaw = yaw > 0 ? yaw : 180.f - yaw * -1; //mirror the yaw

	float aa = atan2(-(int)rightmove, (int)forwardmove) * 57.2957795f;
	const dvar_s* _fov = Dvar_FindMalleableVar("cg_fov");
	const dvar_s* fovscale = Dvar_FindMalleableVar("cg_fovscale");

	const float fov = _fov->current.value * fovscale->current.value * v::mod_fps_transferz.evar->arrayValue[3];

	aa > 0 ? aa -= 45 : aa += 45;

	vec2_t zone125 = { fps_zones.fps125, 90.f + fps_zones.fps125 };
	vec2_t zone200 = { fps_zones.fps200, 90.f + fps_zones.fps200 };
	vec2_t zone250 = { fps_zones.fps250, 90.f + fps_zones.fps250 };
	vec2_t zone333 = { fps_zones.fps333, 90.f + fps_zones.fps333 };

	if (_rightmove) {
		zone125[0] = 180.f - zone125[0] - fps_zones.length125;
		zone125[1] = 180.f - zone125[1] - fps_zones.length125;
		zone200[0] = 180.f - zone200[0] - fps_zones.length200;
		zone200[1] = 180.f - zone200[1] - fps_zones.length200;
		zone250[0] = 180.f - zone250[0] - fps_zones.length250;
		zone250[1] = 180.f - zone250[1] - fps_zones.length250;
		//yaw -= 10;
	}

	yaw = AngleNormalize180(yaw += aa);
	if (yaw < 0)
		yaw = 180.f - fabs(yaw);


	const bool isLong125 = v::mod_autoFPS_long125.isEnabled();

	range_t ranges, ranges2;

	if (!isLong125) {
		ranges = AnglesToRange(DEG2RAD(zone333[0]), DEG2RAD(zone333[0] + fps_zones.length333), DEG2RAD(fmodf(yaw, 90)), fov);
		ranges2 = AnglesToRange(DEG2RAD(zone333[1]), DEG2RAD(zone333[1] + fps_zones.length333), DEG2RAD(fmodf(yaw, 90)), fov);
	}
	else {
		ranges = AnglesToRange(DEG2RAD(zone125[0]), DEG2RAD(zone125[0] + fps_zones.length125), DEG2RAD(fmodf(yaw, 90)), fov);
		ranges2 = AnglesToRange(DEG2RAD(zone125[1]), DEG2RAD(zone125[1] + fps_zones.length125), DEG2RAD(fmodf(yaw, 90)), fov);
	}

	if (ranges.x1 <= 960 && ranges.x2 > 960 || ranges2.x1 <= 960 && ranges2.x2 > 960) {
		jumpanalyzer.recommendedFPS = isLong125 == false ? 333 : 125;
		return isLong125 == false ? 333 : 125;
	}

	if (!isLong125) {
		ranges = AnglesToRange(DEG2RAD(zone125[0]), DEG2RAD(zone125[0] + fps_zones.length125), DEG2RAD(fmodf(yaw, 90)), fov);
		ranges2 = AnglesToRange(DEG2RAD(zone125[1]), DEG2RAD(zone125[1] + fps_zones.length125), DEG2RAD(fmodf(yaw, 90)), fov);
	}
	else {
		ranges = AnglesToRange(DEG2RAD(zone333[0]), DEG2RAD(zone333[0] + fps_zones.length333), DEG2RAD(fmodf(yaw, 90)), fov);
		ranges2 = AnglesToRange(DEG2RAD(zone333[1]), DEG2RAD(zone333[1] + fps_zones.length333), DEG2RAD(fmodf(yaw, 90)), fov);
	}

	if (ranges.x1 <= 960 && ranges.x2 > 960 || ranges2.x1 <= 960 && ranges2.x2 > 960) {
		jumpanalyzer.recommendedFPS = isLong125 == false ? 125 : 333;
		return  isLong125 == false ? 125 : 333;
	}

	ranges = AnglesToRange(DEG2RAD(zone200[0]), DEG2RAD(zone200[0] + fps_zones.length200), DEG2RAD(fmodf(yaw, 90)), fov);
	ranges2 = AnglesToRange(DEG2RAD(zone200[1]), DEG2RAD(zone200[1] + fps_zones.length200), DEG2RAD(fmodf(yaw, 90)), fov);

	if (ranges.x1 <= 960 && ranges.x2 > 960 || ranges2.x1 <= 960 && ranges2.x2 > 960) {
		jumpanalyzer.recommendedFPS = 200;
		return 200;
	}

	ranges = AnglesToRange(DEG2RAD(zone250[0]), DEG2RAD(zone250[0] + fps_zones.length250), DEG2RAD(fmodf(yaw, 90)), fov);
	ranges2 = AnglesToRange(DEG2RAD(zone250[1]), DEG2RAD(zone250[1] + fps_zones.length250), DEG2RAD(fmodf(yaw, 90)), fov);

	if (ranges.x1 <= 960 && ranges.x2 > 960 || ranges2.x1 <= 960 && ranges2.x2 > 960) {
		jumpanalyzer.recommendedFPS = 250;
		return 250;
	}
	return 500;
}
void cg::Mod_BounceCalculator_Create()
{
	trace_t trace;
	vec3_t end;

	if (!v::mod_bounce_calc.isEnabled()) {
		Com_PrintError(CON_CHANNEL_OBITUARY, "Calculator usage is disabled!\n");
		return;
	}

	const auto isBounce = [](vec3_t normals) -> bool {
		return normals[2] >= 0.3f && normals[2] <= 0.7f;

	};

	AnglesToForward(clients->cgameViewangles, rg->viewOrg, 99999, end);

	CG_TracePoint(vec3_t{ 1,1,1 }, &trace, rg->viewOrg, vec3_t{ -1,-1,-1 }, end, cgs->clientNum, MASK_PLAYERSOLID, 1, 1);

	if (!isBounce(trace.normal)) {
		Com_PrintError(CON_CHANNEL_OBITUARY, "This surface cannot be bounced!\n");
		return;
	}

	VectorCopy(trace.normal, bcalc.normal);

	bcalc.origin[0] = rg->viewOrg[0] + trace.fraction * (end[0] - rg->viewOrg[0]);
	bcalc.origin[1] = rg->viewOrg[1] + trace.fraction * (end[1] - rg->viewOrg[1]);
	bcalc.origin[2] = rg->viewOrg[2] + trace.fraction * (end[2] - rg->viewOrg[2]);

	Com_Printf(CON_CHANNEL_OBITUARY, "marked normals ^2{%.3f, %.3f, %.3f}\n", bcalc.normal[0], bcalc.normal[1], bcalc.normal[2]);

	bcalc.exists = true;
}
void cg::Mod_BounceCalculator()
{
	if (!bcalc.exists)
		return;

	Material* fxMaterial = r::R_RegisterMaterial("decode_characters");
	Material* fxMaterialGlow = r::R_RegisterMaterial("decode_characters_glow");

	const float bounce_percentage = PM_CanBeBounced(bcalc.normal, clients->cgameVelocity);
	bool const canBounce = (bounce_percentage > 0 && bounce_percentage <= 100) && !jumpanalyzer.walking && jumpanalyzer.jumpOriginZ != NULL;

	vec2_t xy;

	char buff[64];
	sprintf_s(buff, canBounce == true ? (char*)"BOUNCE (%.1f'/.)" : (char*)"NOT BOUNCE (%.1f'/.)", bounce_percentage);
	if (v::mod_bounce_calcw2s.isEnabled()) {
		if (r::WorldToScreen(bcalc.origin, xy)) {

			r::R_AddCmdDrawTextWithEffects(buff, "fonts/objectivefont", r::X(xy[0]), r::Y(xy[1]), 1.f, 1.f, 0.f, canBounce == true ? vec4_t{ 0,1,0,1 } : vec4_t{ 1,0,0,1 }, 3, v::mod_velometer_glow.evar->vecValue, fxMaterial, fxMaterialGlow, 0, 500, 1000, 2000);
		}
		return;
	}
	r::R_AddCmdDrawTextWithEffects(buff, "fonts/objectivefont", r::X(900), r::Y(800), 1.3f, 1.3f, 0.f, canBounce == true ? vec4_t{ 0,1,0,1 } : vec4_t{ 1,0,0,1 }, 3, v::mod_velometer_glow.evar->vecValue, fxMaterial, fxMaterialGlow, 0, 500, 1000, 2000);

}
void cg::Mod_DisallowHalfbeat()
{
	if (!v::mod_disallow_hb.isEnabled())
		return;

	static DWORD hb_start_time(0), hb_current_time(0);
	float delta;
	const float opt = getOptAngle(delta, true);

	if (jumpanalyzer.walking || opt == -400) {
		hb_start_time = 0;
		hb_current_time = 0;
		return;
	}
	const float dist2opt = DistanceToOpt(opt, clients->cgameViewangles[YAW]);
	//char buff[24];
	//sprintf_s(buff, "d2opt: %.3f", dist2opt);
	//Material* fxMaterial = r::R_RegisterMaterial("decode_characters");
	//Material* fxMaterialGlow = r::R_RegisterMaterial("decode_characters_glow");
	//r::R_AddCmdDrawTextWithEffects(buff, "fonts/objectivefont", r::X(900), r::Y(800), 1.3f, 1.3f, 0.f, vec4_t{ 1,0,0,1 }, 3, v::mod_velometer_glow.evar->vecValue, fxMaterial, fxMaterialGlow, 0, 500, 1000, 2000);

	const usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);

	if (!cmd)
		return;

	const bool isEasyMode = cmd->forwardmove == NULL && (cmd->rightmove < 0 || cmd->rightmove > 0);
	const int velocity = (int32_t)glm::length(glm::vec2(ps_loc->velocity[0], ps_loc->velocity[1]));
	const int old_velocity = (int32_t)glm::length(glm::vec2(ps_loc->oldVelocity[0], ps_loc->oldVelocity[1]));

	if (dist2opt < 5) {
		
		if (!isEasyMode) {
			hb_start_time = Sys_MilliSeconds();
			hb_current_time = hb_start_time;
		}
		else if(old_velocity < velocity)
			hb_current_time = Sys_MilliSeconds();
		
		if (hb_start_time + 300 < hb_current_time) {
			Cbuf_AddText("openscriptmenu cj load\n", cgs->clientNum);
			ps_loc->velocity[0] = 0;
			ps_loc->velocity[1] = 0;
			ps_loc->velocity[2] = 0;
			Com_Printf(CON_CHANNEL_OBITUARY, "^1Easy mode detected!\n");
			hb_start_time = Sys_MilliSeconds();
			hb_current_time = hb_start_time;
			
		}

	}

}