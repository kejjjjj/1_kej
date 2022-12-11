#include "pch.h"

bool jump_builder_s::isEditing()
{
	return this->is_editing && !this->segments.empty();
}
void jump_builder_s::SetEditMode(bool mode)
{
	this->is_editing = mode;
}

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

	VectorCopy(pm_copy.ps->viewangles, this->new_start_angles);
	VectorCopy(pm_copy.ps->origin, this->new_start_origin);

	this->OnUpdateOffsets();
	this->OnUpdateAllPositions();
	//bData.pm->ps->velocity[0] = 3000;
}
void jump_builder_s::OnDeleteProject()
{
	this->builder_data.run_created = false;
	this->ClearData();

	Com_Printf(CON_CHANNEL_OBITUARY, "^1Project deleted!\n");


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
	this->current_segment = NULL;
	this->total_frames = NULL;
	this->preview_frame = NULL;

	jbuilder.segment_frameCount = 0;
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
void jump_builder_s::SaveFrameData(std::vector<jump_data>& container, jump_data& jData)
{
	if (container.size() + 1 < container.max_size())
		container.push_back(jData);
	else {
		Com_PrintError(CON_CHANNEL_ERROR, "exceeded maximum amount of frames!\n");
		this->OnStopGenerating();
	}
	//Com_Printf(CON_CHANNEL_OBITUARY, "container size: %i\n", container.size());
}
size_t jump_builder_s::GetTotalFrames()
{
	size_t total(0);
	
	if (this->segments.size() < 1)
		return 0;

	for (const auto& i : this->segments)
		total += i.jData.size() - 1;

	return total;

	//return this->segments[this->segments.size()-1].end;

}
void jump_builder_s::OnGetSegmentData()
{
	if (this->segments.empty())
		return;

	builder_data_s& bData = this->builder_data;

	if (this->current_segment == NULL) {
		memcpy_s(&pm_copy, sizeof(pmove_t), &cg::h_pm, sizeof(pmove_t));
		memcpy_s(&pml_copy, sizeof(pml_t), &cg::h_pml, sizeof(pml_t));
		memcpy_s(&ps_copy, sizeof(playerState_s), &cg::h_ps, sizeof(playerState_s));

		VectorCopy(this->new_start_angles, ps_copy.viewangles);
		VectorCopy(this->new_start_origin, ps_copy.origin);

	}
	else {
		const segment_data_s prev_segment = this->segments[this->current_segment - 1];

		memcpy_s(&pm_copy, sizeof(pmove_t), &prev_segment.end_pm, sizeof(pmove_t));
		memcpy_s(&pml_copy, sizeof(pml_t), &prev_segment.end_pml, sizeof(pml_t));
		memcpy_s(&ps_copy, sizeof(playerState_s), &prev_segment.end_ps, sizeof(playerState_s));
	}

	bData.pm = reinterpret_cast<pmove_t*>(&pm_copy);
	bData.pml = reinterpret_cast<pml_t*>(&pml_copy);
	bData.pm->ps = reinterpret_cast<playerState_s*>(&ps_copy);

}
void jump_builder_s::OnUpdateAllPositions()
{
	const int tmp_save = jbuilder.current_segment;

	for (size_t i = 0; i < jbuilder.segments.size(); i++) {
		jbuilder.current_segment = i;
		jbuilder.OnUpdatePosition(true);
	}
	jbuilder.current_segment = tmp_save;
}

void Sys_SnapVector(float* v)
{
	int i;
	float f;

	f = *v;
	__asm	fld		f;
	__asm	fistp	i;
	*v = i;
	v++;
	f = *v;
	__asm	fld		f;
	__asm	fistp	i;
	*v = i;
	v++;
	f = *v;
	__asm	fld		f;
	__asm	fistp	i;
	*v = i;
	/*
	*v = fastftol(*v);
	v++;
	*v = fastftol(*v);
	v++;
	*v = fastftol(*v);
	*/
}


void jump_builder_s::OnUpdatePosition(const bool erase)
{
	//if (!this->isGeneratingMovement())
	//	return;

	

	if (this->segments.empty())
		return;

	builder_data_s& bData = this->builder_data;
	pmove_t* pm = bData.pm;
	pml_t* pml = bData.pml;
	segment_data_s& segment = this->segments[this->current_segment];

	if (erase || !pm || !pml) {

		segment.jData.erase(segment.jData.begin(), segment.jData.begin());
		segment.jData.clear();
		segment.jData.resize(0);
		
		this->OnGetSegmentData();

		pm = bData.pm;
		pml = bData.pml;

		current_frame = NULL;
	}
	hook* a = nullptr;

	a->write_addr(0x405360, "\xC3",  1); //stop an animation related crash

	for (size_t i = 0; i < segment.framecount; i++) {

		pm->cmd.forwardmove = segment.forwardmove;
		pm->cmd.rightmove = segment.rightmove;
		pm->ps->clientNum = cgs->clientNum;
		//pm->oldcmd.forwardmove = 127;

		//VectorCopy(clients->cgameViewangles, pm->ps->viewangles);
		//pm->ps->viewangles[YAW] += 90;
		//AngleVectors(pm->ps->viewangles, pml->right, pml->forward, pml->up);

		//if (move->jump)
		//	pm->cmd.buttons |= 1024;

		jump_data jData;

		VectorCopy(pm->ps->viewangles, jData.angles);
		VectorCopy(pm->ps->origin, jData.origin);
		VectorCopy(pm->ps->velocity, jData.velocity);
		jData.forwardmove = pm->cmd.forwardmove;
		jData.rightmove = pm->cmd.rightmove;
		

		if (pml->walking) {
			if(v::mod_jbuild_sprint.isEnabled())
				pm->cmd.buttons |= 8194;
			jData.FPS = 125;
		}

		((void(__cdecl*)(pmove_t*))0x40E6A0)(pm); //update sprint

		if (glm::length(glm::vec2(pm->ps->velocity[0], pm->ps->velocity[1])) >= 224 || !pml->walking)
			pm->ps->viewangles[YAW] = getOptForAnalyzer(&jData, pml->walking);

		AngleVectors(pm->ps->viewangles, pml->forward, pml->right, pml->up);
		if(!pml->walking)
			jData.FPS = cg::Mod_RecommendedFPS(pm->ps->viewangles[YAW], pm->cmd.forwardmove, pm->cmd.rightmove);

		if (jData.FPS == NULL)
			jData.FPS = 125; 

		pml->msec = 1000 / jData.FPS;
		pml->frametime = (float)pml->msec / 1000.f;

		dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

		if (g_gravity) {
			if (g_gravity->current.value == 0)
				pm->ps->gravity = 800;
		}

		if (pml->walking) {
			

			if (glm::length(glm::vec2(pm->ps->velocity[0], pm->ps->velocity[1])) >= v::mod_jbuild_jvel.GetFloat()) {
				pm->cmd.buttons |= 1024;
			}

			PM_WalkMove_f(pm, pml);
		}
		else
			PM_AirMove_f(pm, pml);

		((void(__cdecl*)(pmove_t*, pml_t*))0x410660)(pm, pml); //call groundtrace after 

		PM_OverBounce(pm, pml);
		Sys_SnapVector(pm->ps->velocity); //Sys_SnapVector

		if (pm && pml) {
		

			//jump_data jData;

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
			jData.FPS = 1000 / pml->msec;

			memcpy(&pm->oldcmd, &pm->cmd, sizeof(pm->oldcmd));
			pm->cmd.buttons = 0;
			this->SaveFrameData(segment.jData, jData);
			this->OnFrameUpdate();
		}
	}
	//Com_Printf(CON_CHANNEL_OBITUARY, "orgZ: %.3f\n", segment.jData[segment.jData.size()-1].origin[2]);
	memcpy_s(&segment.end_pm, sizeof(pmove_t), pm, sizeof(pmove_t));
	memcpy_s(&segment.end_pml, sizeof(pml_t), pml, sizeof(pml_t));
	memcpy_s(&segment.end_ps, sizeof(playerState_s), pm->ps, sizeof(playerState_s));

	a->write_addr(0x405360, "\x53", 1);
	//Com_Printf(CON_CHANNEL_OBITUARY, "velocity %.1f\npml->walking: %i\n", glm::length(glm::vec2(pm->ps->velocity[0], pm->ps->velocity[1])), pml->walking);
	
}
jump_data* jump_builder_s::FetchFrameData(int32_t frame)
{
	const auto SegmentFromFrame = [frame](std::vector<segment_data_s>& seg) -> segment_data_s*
	{
		for (auto& i : seg) {
			if (i.begin <= frame && i.end >= frame)
				return &i;
		}
		return nullptr;
	};

	if (this->segments.empty())
		return nullptr;

	segment_data_s* seg = SegmentFromFrame(this->segments);
	
	if (!seg)
		return nullptr;

	return &seg->jData[frame - seg->begin];
}


void jump_builder_s::OnAddSegment()
{
	segment_data_s seg;

	seg.framecount = 100;

	if (this->segments.size() > 0) {
		seg.begin = this->segments[this->segments.size() - 1].end+1;
		seg.end = seg.begin + seg.framecount;
	}else {
		seg.begin = 0;
		seg.end = seg.framecount;
	}
	this->segments.push_back(seg);

}
void jump_builder_s::OnDeleteSegment()
{
	if (this->segments.size() == 1) {
		this->OnDeleteProject();
		//this->OnCreateNew();
		return;
	}

	this->segments.erase(this->segments.begin() + this->current_segment);
	this->OnUpdateOffsets();
	this->OnUpdateAllPositions();
	if(this->segments.size() > 1 && this->current_segment > 0)
		this->current_segment -= 1;

	Com_Printf(CON_CHANNEL_OBITUARY, "^1Segment deleted!\n");
}
void jump_builder_s::OnInsertSegment()
{
	segment_data_s seg;

	seg.framecount = 100;

	if(this->current_segment == NULL || this->segments.empty()) {
		seg.begin = 0;
		seg.end = seg.framecount;
	}
	else {
		seg.begin = this->segments[this->current_segment-1].end + 1;
		seg.end = seg.begin + seg.framecount;
	}
	this->segments.insert(this->segments.begin() + this->current_segment, seg);

	this->OnUpdateOffsets();
	this->OnUpdateAllPositions();
	Com_Printf(CON_CHANNEL_OBITUARY, "^2Segment inserted!\n");
}
//fix all frame gaps/overlaps in-between segments
//called when changing the framecount of a segment
void jump_builder_s::OnUpdateOffsets()
{
	if (this->segments.size() < 1)
		return;

	const auto FixLength = [](segment_data_s& seg) -> void {
	
		const float difference = fabs(seg.end - seg.begin);

		if (difference != seg.framecount-1) {
			seg.end = seg.begin + seg.framecount-1;
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

		shiftForward = (i.end > nextSeg.end);


		if (dist > 1) {
			if (!shiftForward) {
				//Com_Printf(CON_CHANNEL_OBITUARY, "[%i] was shifted ^2%i ^7frames ^1back\n", indx, dist);
				nextSeg.begin -= dist;
				nextSeg.end -= dist;
			}else {
				//Com_Printf(CON_CHANNEL_OBITUARY, "[%i] was shifted ^2%i ^7frames ^2forward\n", indx, dist);
				nextSeg.begin += dist;
				nextSeg.end += dist;
			}

		}
		

		++indx;
	}

}
bool jump_builder_s::InFreeMode()
{
	return in_free_mode;
}
void jump_builder_s::SetFreeMode(bool isTrue)
{
	in_free_mode = isTrue;
}