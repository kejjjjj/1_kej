#include "pch.h"


void jump_builder_s::OnCreateNew()
{
	builder_data_s& bData = this->builder_data;

	bData.pm = reinterpret_cast<pmove_t*>(&cg::h_pm);
	bData.pml = reinterpret_cast<pml_t*>(&cg::h_pml);
	bData.pm->ps = reinterpret_cast<playerState_s*>(&cg::h_ps); //redirect the playerstate pointer elsewhere so that it doesn't do stuff with the actual client

	this->OnStopGenerating();
	this->ClearData();

	Com_Printf(CON_CHANNEL_OBITUARY, "^2Data Created!\n");

	this->builder_data.run_created = true;

	//bData.pm->ps->velocity[0] = 3000;
}
bool jump_builder_s::isGeneratingMovement()
{
	return this->is_generating_movement;
}
bool jump_builder_s::MovementExists()
{
	return this->jData.size() > 0;
}
void jump_builder_s::OnStartGenerating()
{
	this->ClearData();
	this->is_generating_movement = true;
}
void jump_builder_s::OnStopGenerating()
{
	this->is_generating_movement = false;
}
void jump_builder_s::ClearData()
{
	this->jData.erase(this->jData.begin(), this->jData.end());
	this->jData.clear();
	this->jData.resize(0);

	this->builder_data.run_created = false;

	this->current_frame = NULL;
}
void jump_builder_s::OnFrameUpdate()
{
	this->current_frame++;
}
void jump_builder_s::SaveFrameData(jump_data& jData)
{
	if (this->jData.size() + 1 < this->jData.max_size())
		this->jData.push_back(jData);
	else {
		Com_PrintError(CON_CHANNEL_ERROR, "exceeded maximum amount of frames!\n");
		this->OnStopGenerating();
	}
}
int32_t jump_builder_s::GetTotalFrames()
{
	return this->jData.size();
}
void jump_builder_s::OnUpdatePosition()
{
	if (!this->isGeneratingMovement())
		return;


	builder_data_s& bData = this->builder_data;
	pmove_t* pm = bData.pm;
	pml_t* pml = bData.pml;


	static int32_t old_cmdTime = jumpanalyzer.serverTime;

	if (glm::distance((float)old_cmdTime, (float)jumpanalyzer.serverTime) > 100) //true on map restart
		old_cmdTime = jumpanalyzer.serverTime;

	pm->cmd.forwardmove = 127;
	pm->oldcmd.forwardmove = 127;

	//pm->cmd.angles[0] = ANGLE2SHORT(clients->cgameViewangles[0]);
	//pm->cmd.angles[1] = ANGLE2SHORT(clients->cgameViewangles[1]);
	//pm->cmd.angles[2] = ANGLE2SHORT(clients->cgameViewangles[2]);


	VectorCopy(clients->cgameViewangles, pm->ps->viewangles);
	pm->ps->viewangles[YAW] += 90;
	//((void(*)(playerState_s*, usercmd_s*))0x412980)(pm->ps, &pm->cmd); //call groundtrace after 
	AngleVectors(pm->ps->viewangles, pml->right, pml->forward, pml->up);

	if (move->jump)
		pm->cmd.buttons |= 1024;

	if (pml->walking)
		PM_WalkMove_f(pm, pml);
	else
		PM_AirMove_f(pm, pml);

	((void(__cdecl*)(pmove_t * pm, pml_t * pml))0x410660)(pm, pml); //call groundtrace after 

	const float difference = (float)(1000.f / (cls->frametime == NULL ? 1 : cls->frametime)) / 125.f;


	dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");
	com_maxfps->current.integer = 60;

	if (jumpanalyzer.serverTime > old_cmdTime + 3 * difference) {
		old_cmdTime = jumpanalyzer.serverTime;
		jump_data jData;

		VectorCopy(pm->ps->viewangles, jData.angles);
		VectorCopy(pm->ps->origin, jData.origin);
		VectorCopy(pm->ps->velocity, jData.velocity);
		jData.forwardmove = pm->cmd.forwardmove;
		jData.rightmove = pm->cmd.rightmove;
		VectorCopy(pm->mins, jData.mins);
		VectorCopy(pm->maxs, jData.maxs);
		jData.rpg_fired = false;
		jData.bounced = false;
		jData.colliding = false;
		jData.jumped = false;

		memcpy(&pm->oldcmd, &pm->cmd, sizeof(pm->oldcmd));
		pm->cmd.buttons = 0;
		this->SaveFrameData(jData);
		this->OnFrameUpdate();
	}
}
jump_data* jump_builder_s::FetchFrameData(int32_t frame)
{
	if (this->jData.size() > frame)
		return &this->jData[frame];

	return nullptr;
}