
#include "pch.h"

void cg::Mod_HitAnalyzer(pmove_t* pm, pml_t* pml)
{
	if (!v::mod_hitanalyzer.isEnabled())
		return;

	static int32_t hit_velocity;
	static bool wait_ground = NULL;

	if (GROUND)
		wait_ground = false;

	if (pml->groundTrace.normal[2] > .3f && pml->groundTrace.normal[2] < .7f) {
		if ((pm->ps->pm_flags & PMF_JUMPING) == 0 && NOT_GROUND && pm->ps->jumpTime > 500 && !wait_ground) {
			hit_velocity = (int32_t)glm::length(glm::vec2(pm->ps->velocity[0], pm->ps->velocity[1]));
			const int32_t old_vel = (int32_t)glm::length(glm::vec2(pm->ps->oldVelocity[0], pm->ps->oldVelocity[1]));


			wait_ground = true;

			const int32_t difference = hit_velocity - old_vel;

			Com_Printf(CON_CHANNEL_OBITUARY, "^2%i\n", difference);


		}
	}

}