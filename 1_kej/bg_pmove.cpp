#include "pch.h"

BOOL cg::PM_SlideMove(pmove_t* pm, pml_t* pml, int gravity)
{
	BOOL clipped = PM_SlideMove_f(pm, pml, gravity);

	jumpanalyzer.velocity_clipped = clipped > 0;

	return clipped;
}
void cg::PM_AirMove(pmove_t* pm, pml_t* pml)
{
	
	PM_AirMove_f(pm, pml);

	Mod_HitAnalyzer(pm, pml);
	Mod_JumpAnalyzer(pm, pml);

}
void cg::PM_Weapon(pml_t* pmll, pmove_t* pmm)
{
	static pml_t* pml;
	static pmove_t* pm;
	__asm	mov pml, eax;
	__asm	mov pm, ebp;

	PM_Weapon_f(pml, pm);

	if (pm && pml) {
		Mod_RPGAnalyzer(pm, pml);
	}

	return;
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
void cg::Mod_JumpView(pmove_t* pm, pml_t* pml)
{
	
	if (!analyzer.isRecording() || !pm || !pml)
		return;



	static int32_t old_cmdTime = pm->cmd.serverTime;
	static bool hasBounced = false, hasShotRPG;

	if (analyzer.current_frame == 0) {
		hasBounced = false;
		hasShotRPG = false;
	}
	else if (!hasBounced)
		hasBounced = jumpanalyzer.bounceTime == pm->ps->commandTime;

	if (!hasShotRPG) {
		hasShotRPG = jumpanalyzer.weapon_cant_fire && (pm->ps->weapon == BG_FindWeaponIndexForName("rpg_mp") || pm->ps->weapon == BG_FindWeaponIndexForName("rpg_sustain_mp"));
	}
	

	if (pm->cmd.serverTime > old_cmdTime + 3) {
		old_cmdTime = pm->cmd.serverTime;
		jump_data jData;

		VectorCopy(pm->ps->viewangles, jData.angles);
		VectorCopy(pm->ps->origin, jData.origin);
		VectorCopy(pm->ps->velocity, jData.velocity);
		jData.forwardmove = pm->cmd.forwardmove;
		jData.rightmove = pm->cmd.rightmove;
		VectorCopy(pm->mins, jData.mins);
		VectorCopy(pm->maxs, jData.maxs);
		jData.rpg_fired = hasShotRPG;
		jData.bounced = hasBounced;
		jData.colliding = jumpanalyzer.velocity_clipped;

		if (hasShotRPG) hasShotRPG = false;
		if (hasBounced) hasBounced = false;

		jData.FPS = (int)(1000.f / (cgs->frametime == NULL ? 1 : cgs->frametime));

		analyzer.SaveFrameData(jData); 
		analyzer.OnFrameUpdate();
	}
}
void cg::PM_ModCode(pml_t* pml, pmove_t* pm)
{
	//this part of the code is called after PM_Weapon()

	Mod_JumpView(pm, pml);

	return;
}
__declspec(naked) void cg::PmoveSingle_stub()
{
	const static DWORD _jmp = 0x414BBB;
	__asm
	{

		push ebx;
		lea ecx, [esp + 0x28]; 
		push ecx;
		call PM_ModCode;
		add esp, 0x8;
		mov eax, ebx;
		mov esi, 0x412390;
		call esi;
		jmp _jmp;

	}
}