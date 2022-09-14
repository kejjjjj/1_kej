
#include "pch.h"

void cg::Mod_HitAnalyzer(pmove_t* pm, pml_t* pml)
{
	if (!v::mod_hitanalyzer.isEnabled() && !v::mod_jumpanalyzer.isEnabled())
		return;

	static bool wait_ground = NULL;

	if (GROUND) {
		wait_ground = false;

		if (v::mod_jumpanalyzer.isEnabled()) {
			if (cg::jumpanalyzer.hasJumped && cg::jumpanalyzer.hasBounced) {
				Com_Printf(CON_CHANNEL_OBITUARY, "^6jump velocity: ^2%i\n", cg::jumpanalyzer.jumpVelocity);
				Com_Printf(CON_CHANNEL_OBITUARY, "^6bounce velocity: ^2%i\n", cg::jumpanalyzer.bounceVelocity);
			}

			memset(&cg::jumpanalyzer, 0, sizeof(cg::jumpanalyzer_s));
		}
	}
	if (pml->groundTrace.normal[2] > .3f && pml->groundTrace.normal[2] < .7f) {
		if ((pm->ps->pm_flags & PMF_JUMPING) == 0 && NOT_GROUND && pm->ps->jumpTime > 500 && !wait_ground) {
			const int32_t hit_velocity = (int32_t)glm::length(glm::vec2(pm->ps->velocity[0], pm->ps->velocity[1]));
			const int32_t old_vel = (int32_t)glm::length(glm::vec2(pm->ps->oldVelocity[0], pm->ps->oldVelocity[1]));
			jumpanalyzer.bounceVelocity = old_vel;
			jumpanalyzer.hasBounced = true;

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