#include "pch.h"

void cg::PM_AirMove(pmove_t* pm, pml_t* pml)
{
	
	PM_AirMove_f(pm, pml);

	Mod_HitAnalyzer(pm, pml);
	Mod_JumpAnalyzer(pm, pml);

}
void cg::Pmove(pmove_t* pm)
{
	dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");

	if (!com_maxfps) {
		Com_PrintError(CON_CHANNEL_OBITUARY, "please use com_maxfps as your dvar name\n");
		return;
	}

	int frametime = cls->frametime == 0 ? 1 : cls->frametime;
	int _msec;

	_msec = 1000.f / (com_maxfps->current.integer == 0 ? 1 : com_maxfps->current.integer);

	if (v::mod_pmove_fixed.isEnabled())
		pm->cmd.serverTime = ((pm->cmd.serverTime + (_msec < 2 ? 2 : _msec) - 1) / _msec) * _msec;

	int finalTime = pm->cmd.serverTime;

	if (finalTime < pm->ps->commandTime) {
		return; // should not happen
	}

	if (finalTime > pm->ps->commandTime + 1000) {
		pm->ps->commandTime = finalTime - 1000;
	}
	pm->numtouch = 0;

	while (pm->ps->commandTime != finalTime) {
		int msec;

		msec = finalTime - pm->ps->commandTime;

		if (v::mod_pmove_fixed.isEnabled()) {
			if (msec > _msec) {
				msec = _msec;
			}
		}
		else {
			if (msec > 66)
				msec = 66;
		}

		pm->cmd.serverTime = pm->ps->commandTime + msec;
		PmoveSingle(pm);
		memcpy(&pm->oldcmd, &pm->cmd, sizeof(pm->oldcmd));

	}
}