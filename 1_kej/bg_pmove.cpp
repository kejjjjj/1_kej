#include "pch.h"

BOOL cg::PM_SlideMove(pmove_t* pm, pml_t* pml, int gravity)
{
	BOOL clipped = PM_SlideMove_f(pm, pml, gravity);

	jumpanalyzer.velocity_clipped = clipped > 0;

	return clipped;
}
void cg::PM_AirMove(pmove_t* pm, pml_t* pml)
{

	memcpy_s(&h_pm, sizeof(pmove_t), pm, sizeof(pmove_t*));
	memcpy_s(&h_pml, sizeof(pml_t), pml, sizeof(pml_t*));
	
	Mod_DetermineFPS(pm, pml);

	PM_AirMove_f(pm, pml);

	Mod_HitAnalyzer(pm, pml);
	Mod_JumpAnalyzer(pm, pml);
	Mod_A_AdjustRPG(pm, pml);

}
void cg::PM_UFOMove(pmove_t* pmm, pml_t* pmll)
{
	static pml_t* pml;
	static pmove_t* pm;
	__asm	mov pml, edx;
	__asm	mov pm, eax;

	PM_UFOMove_f(pmm, pmll);

	jumpanalyzer.commandTime = pm->ps->commandTime;
	jumpanalyzer.serverTime = pm->cmd.serverTime;

	return;
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

	if (_msec == NULL)
		_msec = 1;

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

		//jumpanalyzer.commandTime = pm->ps->commandTime;
		jumpanalyzer.serverTime = pm->cmd.serverTime;
		memcpy(&pm->oldcmd, &pm->cmd, sizeof(pm->oldcmd));

	}
}
void cg::Mod_JumpView(pmove_t* pm, pml_t* pml)
{

	static DWORD afkSnapshots = Sys_MilliSeconds();

	jumpanalyzer.commandTime = pm->ps->commandTime;
	jumpanalyzer.serverTime  = pm->cmd.serverTime;


	if (analyzer.InRecordingMode() && !analyzer.isRecording()
		&& !analyzer.isPreviewing() && analyzer.LastRecordingStoppedTime() + 200 < clients->snap.ps.commandTime
		&& (pm->cmd.forwardmove != NULL || pm->cmd.rightmove != NULL) && VID_ACTIVE && !analyzer.isSegmenting()) {

		analyzer.StartRecording();
		afkSnapshots = Sys_MilliSeconds();
	}

	if (analyzer.isSegmenting()) {
		if (analyzer.Segmenter_Prepare() > 200) {

			jump_data* jData = analyzer.FetchFrameData(analyzer.segment_frame);

			if (jData) {
				const vec3_t null = { 0,0,0 };
				VectorCopy(jData->origin, ps_loc->origin);
				VectorCopy(null, ps_loc->velocity);

				//CG_SetPlayerAngles(clients->cgameViewangles, jData->angles);
			}
		}


	}

	if (!analyzer.isRecording() && analyzer.isSegmenting() && !analyzer.segmenterData.isReady || !pm || !pml || !analyzer.isRecording() && !analyzer.isSegmenting())
		return;



	static int32_t old_cmdTime = pm->cmd.serverTime;

	if (glm::distance((float)old_cmdTime, (float)pm->cmd.serverTime) > 100) //true on map restart
		old_cmdTime = pm->cmd.serverTime;

	static bool hasBounced, hasShotRPG, hasJumped;

	if (analyzer.current_frame == 0) {
		hasBounced = false;
		hasShotRPG = false;
		hasJumped  = false;
	}else if (!hasBounced)
		hasBounced = jumpanalyzer.bounceTime == pm->ps->commandTime;


	if (!hasShotRPG) {
		hasShotRPG = jumpanalyzer.weapon_cant_fire && (pm->ps->weapon == BG_FindWeaponIndexForName("rpg_mp") || pm->ps->weapon == BG_FindWeaponIndexForName("rpg_sustain_mp"));
	}else if (hasShotRPG && clients->snap.ps.weaponstate != WEAPON_FIRING) { //this check makes sure it doesn't think other animations are considered as shooting 
		hasShotRPG = false;
	}


	hasJumped = pm->cmd.serverTime - pm->ps->jumpTime < 10;

	if (/*pm->ps->velocity[0] == NULL && pm->ps->velocity[1] == NULL && GROUND && !VID_ACTIVE || NOT_GROUND && */!VID_ACTIVE)
		analyzer.PauseRecording();

	static vec3_t	prevAngles = {pm->ps->viewangles[0], pm->ps->viewangles[1] , pm->ps->viewangles[2] }, 
					prevOrigin = { pm->ps->origin[0], pm->ps->origin[1] , pm->ps->origin[2] };

	const float angDist = glm::distance(glm::vec2(pm->ps->viewangles[0], pm->ps->viewangles[1]), glm::vec2(prevAngles[0], prevAngles[1]));

	if (VectorCompare(pm->ps->origin, prevOrigin) == true && angDist < 10.f) {

		//afkSnapshots++;

		if (GetAsyncKeyState(VK_PRIOR) & 1)
			Com_Printf(CON_CHANNEL_OBITUARY, "angDist: %.6f\n", angDist/*Sys_MilliSeconds() - afkSnapshots*/);

		if (afkSnapshots + 2000 < Sys_MilliSeconds()) {
			analyzer.PauseRecording();
			afkSnapshots = Sys_MilliSeconds();
		}

	}else {
		if (VID_ACTIVE) {
			analyzer.ContinueRecording();
			
		}
		afkSnapshots = Sys_MilliSeconds();
	}

	VectorCopy(pm->ps->origin, prevOrigin);
	VectorCopy(pm->ps->viewangles, prevAngles);

	const float difference = (float)(1000.f / (cls->frametime == NULL ? 1 : cls->frametime)) / 125.f;

	if (pm->cmd.serverTime > old_cmdTime + 2 * difference && !analyzer.RecordingPaused()) {
		old_cmdTime = pm->cmd.serverTime;
		if(!analyzer.isSegmenting())
			Mod_SaveData(analyzer.data, pm, hasBounced, hasJumped, hasShotRPG);
		else
			Mod_SaveData(analyzer.segData, pm, hasBounced, hasJumped, hasShotRPG);
	}
}
void cg::Mod_SaveData(std::vector<jump_data>& storage, pmove_t* pm, bool& hasBounced, bool& hasJumped, bool& hasShotRPG)
{
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
	jData.jumped = hasJumped;

	std::set<int> &rpg = analyzer.isSegmenting() ? analyzer.s_rpgFrames : analyzer.rpgFrames;
	std::set<int> &jump = analyzer.isSegmenting() ? analyzer.s_jumpFrame : analyzer.jumpFrame;
	std::set<int> &bounce = analyzer.isSegmenting() ? analyzer.s_bounceFrames : analyzer.bounceFrames;


	if (hasShotRPG) { rpg.insert(analyzer.current_frame);			hasShotRPG = false; }
	if (hasBounced) { 
		bounce.insert(analyzer.current_frame);			hasBounced = false; }
	if (hasJumped) {  
		jump.insert(analyzer.current_frame);				hasJumped = false;  }

	//if (hasCollided) {	current->collisionFrames.insert(current->current_frame);	hasCollided = false; }

	jData.FPS = (int)(1000.f / (cls->frametime == NULL ? 1 : cls->frametime));

	analyzer.SaveFrameData(storage, jData);
	analyzer.OnFrameUpdate();
}
void cg::PM_ModCode(pml_t* pml, pmove_t* pm)
{
	//this part of the code is called after PM_Weapon()

	Mod_JumpView(pm, pml);
	Mod_A_AutoSliding(pm, pml);
	//Mod_A_Strafebot(pm);

	return;
}
void cg::Mod_DetermineFPS(pmove_t* pm, pml_t* pml)
{
	//
	//vec3_t forward, right, wishdir;
	//vec2_t wishvel;
	//vec_t commandScale;

	playerState_s* ps = pm->ps;
	//usercmd_s cmd = pm->cmd;

	//const char forwardmove = pm->cmd.forwardmove;
	//const char rightmove = pm->cmd.rightmove;

	//static const DWORD cmdscale = 0x40EE60;

	//__asm //get command scale
	//{
	//	mov edi, ps;
	//	lea esi, cmd;
	//	call cmdscale;
	//	fstp [commandScale];
	//}


	//VectorCopy(pml->forward, forward);
	//VectorCopy(pml->right, right);

	//forward[2] = 0;
	//right[2] = 0;
	//VectorNormalize(forward);
	//VectorNormalize(right);
	//
	//wishvel[0] = forward[0] * forwardmove + right[0] * rightmove;
	//wishvel[1] = forward[1] * forwardmove + right[1] * rightmove;

	//if (GetAsyncKeyState(VK_END) & 1)
	//	printf("forward[0]: %.6f\n", pml->forward[0]);

	//wishdir[0] = wishvel[0];
	//wishdir[1] = wishvel[1];
	//wishdir[2] = 0.0f;

	//float wishspeed = VectorNormalize(wishdir) * commandScale;

	//const auto Accelerate = [](vec3_t wishDir, pml_t* pml, float wishspeed, float accel, playerState_s* ps) -> void
	//{
	//	float currentSpeed = ps->velocity[1] * wishDir[1] + *wishDir * ps->velocity[0] + ps->velocity[2] * wishDir[2];
	//	float addspeed = wishspeed - currentSpeed;
	//	float _wishspeed, accelspeed;

	//	const dvar_s* stopspeed = Dvar_FindMalleableVar("stopspeed");
	//	airmove.addspeed = addspeed;

	//	if (addspeed > 0.0)
	//	{
	//		//_wishspeed = stopspeed->current.value;



	//		accelspeed = pml->frametime * accel * wishspeed;
	//		if (accelspeed > addspeed)
	//		{
	//			accelspeed = addspeed;
	//		}
	//		airmove.accelspeed = accelspeed;
	//		VectorCopy(wishDir, airmove.wishDir);


	//	}


	//};



	fps_zones.fps125 = round((float)ps->speed / 8) + 10;
	fps_zones.fps200 = round((float)ps->speed / 5) + 10;
	fps_zones.fps250 = round((float)ps->speed / 4) + 10;
	fps_zones.fps333 = round((float)ps->speed / 3) + 10;

	const float diff = ((float)ps->speed / 190.f);

	fps_zones.length125 = (90.f - fps_zones.fps125) - fps_zones.fps125; //this way around because 125 starts from < 45
	fps_zones.length200 = fps_zones.fps200 - (90.f - fps_zones.fps200) + 3.f * diff; //will fill the empty space with 200fps
	fps_zones.length250 = fps_zones.fps250 - (90.f - fps_zones.fps250);
	fps_zones.length333 = fps_zones.fps333 - (90.f - fps_zones.fps333);

	fps_zones.fps125 -= fps_zones.length125;
	fps_zones.fps250 += fps_zones.length250 - (11.f * diff);
	fps_zones.fps200 = fps_zones.fps250 + 20.f * diff;
	fps_zones.fps333 -= fps_zones.length333;

	return;
	//return Accelerate(wishdir, pml, wishspeed, 1.f, ps);

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
//not exactly overbouncing, but the bug is similar
void cg::PM_OverBounce(pmove_t* pm, pml_t* pml)
{

	//Mod_A_Strafebot(pm);

	vec3_t move;

	move[0] = pm->ps->origin[0] - pml->previous_origin[0];
	move[1] = pm->ps->origin[1] - pml->previous_origin[1];
	move[2] = pm->ps->origin[2] - pml->previous_origin[2];

	float dot = move[2] * move[2] + move[1] * move[1] + move[0] * move[0];
	float dot_div_frametime = dot / (pml->frametime * pml->frametime);
	float dot_speed = pm->ps->velocity[2] * pm->ps->velocity[2] + pm->ps->velocity[1] * pm->ps->velocity[1] + pm->ps->velocity[0] * pm->ps->velocity[0];

	if (dot_speed * 0.25 > dot_div_frametime)
	{
		//Com_Printf(CON_CHANNEL_OBITUARY, "possible overbounce!\n");
		float inGameFramesPerSecond = 1.0 / pml->frametime;
		pm->ps->velocity[0] = inGameFramesPerSecond * move[0];
		pm->ps->velocity[1] = inGameFramesPerSecond * move[1];
		pm->ps->velocity[2] = inGameFramesPerSecond * move[2];
	}

	float clampedFrametime = glm::clamp(pml->frametime, 0.f, 1.f);

	float diffX = pm->ps->velocity[0] - pm->ps->oldVelocity[0];
	float diffY = pm->ps->velocity[1] - pm->ps->oldVelocity[1];

	float frameX = clampedFrametime * diffX;
	float frameY = clampedFrametime * diffY;

	pm->ps->oldVelocity[0] = pm->ps->oldVelocity[0] + frameX;
	pm->ps->oldVelocity[1] = pm->ps->oldVelocity[1] + frameY;

	//((void(__cdecl*)(float* vec))0x578FE0)(pm->ps->velocity); //Sys_SnapVector

	return;

}
__declspec(naked) void cg::PM_OverBounce_stub()
{
	const static DWORD _jmp = 0x414BC8;

	__asm
	{
		fld     dword ptr[ebp + 1Ch];
		fsub		[esp + 0x90];
		lea     esi, [ebp + 28h];
		
		lea ecx, [esp + 0x28];
		push ecx;
		push ebx;
		call PM_OverBounce;
		add esp, 0x8;
		jmp _jmp;
		//retn;
	}
}