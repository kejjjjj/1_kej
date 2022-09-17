
#include "pch.h"

void cg::Mod_HitAnalyzer(pmove_t* pm, pml_t* pml)
{
	//if (!v::mod_hitanalyzer.isEnabled() && !v::mod_jumpanalyzer.isEnabled() && !v::mod_rpg_timing.isEnabled() && !v::mod_rpg_angle.isEnabled())
	//	return;

	

	static bool wait_ground = NULL;

	if (GROUND) {
		wait_ground = false;

		if (v::mod_jumpanalyzer.isEnabled()) {
			if (cg::jumpanalyzer.hasJumped && cg::jumpanalyzer.hasBounced) {
				Com_Printf(CON_CHANNEL_OBITUARY, "^6jump velocity: ^2%i\n", cg::jumpanalyzer.jumpVelocity);
				Com_Printf(CON_CHANNEL_OBITUARY, "^6bounce velocity: ^2%i\n", cg::jumpanalyzer.bounceVelocity);
			}

		}
		memset(&cg::jumpanalyzer, 0, sizeof(cg::jumpanalyzer_s));

	}
	if (pml->groundTrace.normal[2] > .3f && pml->groundTrace.normal[2] < .7f) {
		if ((pm->ps->pm_flags & PMF_JUMPING) == 0 && NOT_GROUND && pm->ps->jumpTime > 500 && !wait_ground) {
			const int32_t hit_velocity = (int32_t)glm::length(glm::vec2(pm->ps->velocity[0], pm->ps->velocity[1]));
			const int32_t old_vel = (int32_t)glm::length(glm::vec2(pm->ps->oldVelocity[0], pm->ps->oldVelocity[1]));
			jumpanalyzer.bounceVelocity = old_vel;
			jumpanalyzer.hasBounced = true;
			jumpanalyzer.bounceTime = pm->ps->commandTime;
			wait_ground = true;

			const int32_t difference = hit_velocity - old_vel;

			if(v::mod_hitanalyzer.isEnabled())
				Com_Printf(CON_CHANNEL_OBITUARY, "^2%i\n", difference);


		}
	}

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

	static bool wait_until_fired = false, wait_ground, wait_until_rpg_done;
	static DWORD shot_started(0);
	static bool check_fire_state_next_frame(0);
	static float pitch_before_shot(0);

	if (GROUND) {
		wait_ground = false;
		check_fire_state_next_frame = false;
	}
	if ((pm->cmd.buttons & 1) && (pm->oldcmd.buttons & 1) == 0 && !wait_until_fired && !wait_ground && NOT_GROUND) {

		int32_t rpg = BG_FindWeaponIndexForName("rpg_mp");


		if (pm->ps->weapon != rpg)
			rpg = BG_FindWeaponIndexForName("rpg_sustain_mp");

		if (pm->ps->weapon == rpg) {
			wait_until_rpg_done = true;
			wait_until_fired = true;

			shot_started = pm->ps->commandTime;
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
					Com_Printf(CON_CHANNEL_OBITUARY, "^1too early!\n");
				wait_until_fired = false;
			}
			wait_until_fired = false;
			//setPitch(pm->ps->viewangles[PITCH], pitch_before_shot);

		}
		check_fire_state_next_frame = !check_fire_state_next_frame;

	}
	//else if ((wait_until_fired || wait_until_rpg_done) && cg->ads_animation_state > 0.7) {
	//	setPitch(pm->ps->viewangles[PITCH], 85);
	//}
	//else {
	//	pitch_before_shot = pm->ps->viewangles[PITCH];
	//	wait_until_rpg_done = false;
	//}

}