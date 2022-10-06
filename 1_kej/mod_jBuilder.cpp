#include "pch.h"

bool jump_builder_s::isEditing()
{
	return this->is_editing;
}
void jump_builder_s::SetEditMode(bool mode)
{
	this->is_editing = mode;
}
static playerState_s ps_copy;
static pmove_t pm_copy;
static pml_t pml_copy;
void jump_builder_s::OnCreateNew()
{
	builder_data_s& bData = this->builder_data;

	//bData.pm = reinterpret_cast<pmove_t*>(&cg::h_pm);
	//bData.pml = reinterpret_cast<pml_t*>(&cg::h_pml);
	//bData.pm->ps = reinterpret_cast<playerState_s*>(&cg::h_ps; //redirect the playerstate pointer elsewhere so that it doesn't do stuff with the actual client


	memcpy_s(&pm_copy, sizeof(pmove_t), &cg::h_pm, sizeof(pmove_t));
	memcpy_s(&pml_copy, sizeof(pml_t), &cg::h_pml, sizeof(pml_t));
	memcpy_s(&ps_copy, sizeof(playerState_s), &cg::h_ps, sizeof(playerState_s));

	bData.pm = reinterpret_cast<pmove_t*>(&pm_copy);
	bData.pml = reinterpret_cast<pml_t*>(&pml_copy);
	bData.pm->ps = reinterpret_cast<playerState_s*>(&ps_copy);
	this->OnStopGenerating();
	this->ClearData();

	Com_Printf(CON_CHANNEL_OBITUARY, "^2Data Created!\n");

	this->builder_data.run_created = true;
	this->OnAddSegment();
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

	this->segments.erase(this->segments.begin(), this->segments.end());
	this->segments.clear();
	this->segments.resize(0);

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
size_t jump_builder_s::GetTotalFrames()
{
	size_t total(0);
	
	if (this->segments.size() < 1)
		return 0;

	return this->segments[this->segments.size()-1].end;

}
void jump_builder_s::OnUpdatePosition(const bool erase)
{
	//if (!this->isGeneratingMovement())
	//	return;

	if (this->segments.empty())
		return;

	builder_data_s& bData = this->builder_data;

	if (erase) {
		this->jData.erase(this->jData.begin(), this->jData.end());
		this->jData.clear();
		this->jData.resize(0);
		
		memcpy_s(&pm_copy, sizeof(pmove_t), &cg::h_pm, sizeof(pmove_t));
		memcpy_s(&pml_copy, sizeof(pml_t), &cg::h_pml, sizeof(pml_t));
		memcpy_s(&ps_copy, sizeof(playerState_s), &cg::h_ps, sizeof(playerState_s));

		bData.pm = reinterpret_cast<pmove_t*>(&pm_copy);
		bData.pml = reinterpret_cast<pml_t*>(&pml_copy);
		bData.pm->ps = reinterpret_cast<playerState_s*>(&ps_copy);

		current_frame = NULL;
	}
	pmove_t* pm = bData.pm;
	pml_t* pml = bData.pml;
	segment_data_s& segment = this->segments[this->current_segment];

	if (&segment == nullptr)
		return;

	for (size_t i = 0; i < segment.framecount; i++) {

		pm->cmd.forwardmove = segment.forwardmove;
		pm->cmd.rightmove = segment.rightmove;

		//pm->oldcmd.forwardmove = 127;

		//VectorCopy(clients->cgameViewangles, pm->ps->viewangles);
		//pm->ps->viewangles[YAW] += 90;
		//AngleVectors(pm->ps->viewangles, pml->right, pml->forward, pml->up);

		//if (move->jump)
		//	pm->cmd.buttons |= 1024;

		if (pml->walking)
			PM_WalkMove_f(pm, pml);
		else
			PM_AirMove_f(pm, pml);

		((void(__cdecl*)(pmove_t * pm, pml_t * pml))0x410660)(pm, pml); //call groundtrace after 

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
	Com_Printf(CON_CHANNEL_OBITUARY, "Generated [%i] frames\n", segment.framecount);
	
}
jump_data* jump_builder_s::FetchFrameData(int32_t frame)
{
	if (this->jData.size() > frame)
		return &this->jData[frame];

	return nullptr;
}


void jump_builder_s::OnAddSegment()
{
	segment_data_s seg;

	seg.framecount = 100;

	if (this->segments.size() > 0) {
		seg.begin = this->segments[this->segments.size() - 1].end + 1;
		seg.end = seg.begin + seg.framecount;
	}else {
		seg.begin = 0;
		seg.end = seg.framecount;
	}
	this->segments.push_back(seg);

}

//fix all frame gaps/overlaps in-between segments
//called when changing the framecount of a segment
void jump_builder_s::OnUpdateOffsets()
{
	if (this->segments.size() < 1)
		return;

	const auto FixLength = [](segment_data_s& seg) -> void {
	
		const float difference = fabs(seg.end - seg.begin);

		if (difference != seg.framecount) {
			seg.end = seg.begin + seg.framecount;
		}


	};

	size_t indx(0);
	bool shiftForward;

	for (auto& i : this->segments)
		FixLength(i);

	for (auto& i : this->segments) {
		const bool isLast = indx == this->segments.size() - 1;

		if (isLast) 
			break;

		segment_data_s& nextSeg = this->segments[indx + 1];
		const size_t dist = (size_t)fabs(nextSeg.begin - i.end);

		shiftForward = i.end > nextSeg.end;


		if (dist > 1) {
			if (!shiftForward) {
				Com_Printf(CON_CHANNEL_OBITUARY, "[%i] was shifted ^2%i ^7frames ^1back\n", indx, dist);
				nextSeg.begin -= dist;
				nextSeg.end -= dist;
			}else {
				Com_Printf(CON_CHANNEL_OBITUARY, "[%i] was shifted ^2%i ^7frames ^2forward\n", indx, dist);
				nextSeg.begin += dist;
				nextSeg.end += dist;
			}

		}
		

		++indx;
	}

}