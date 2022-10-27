#include "pch.h"


void r::R_JumpBuilder_ConstructKey(char& direction, char value, const char* buttonName)
{

	if (ImGui::Button(buttonName)) {

		if (direction == value)
			direction = NULL;
		else
			direction = value;

		jbuilder.OnUpdateAllPositions();

	}

	if (direction == value) {
		ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImColor(0.f, 0.f, 0.f, 0.7f));
	}
}

void r::R_JumpBuilder_Main()
{

	dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");


	if (g_gravity) {
		g_gravity->current.value = 0;
	}

	if (ImGui::BeginTabBar("##jumpbuilder_view", ImGuiTabBarFlags_None)) {
		if (ImGui::BeginTabItem("Main view##02")) {
			R_JumpBuilder_Builder();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Preferences##02")) {
			R_JumpBuilder_Preferences();
			ImGui::EndTabItem();
		}
	}
}
void r::R_JumpBuilder_Preferences()
{
	ImGui::Text("Create Project\t\t\t\t");
	UI_DrawGradientZone(ImVec2(220, 150));

	ImGui::Text("\t");
	ImGui::SameLine();

	ImGui::BeginGroup();

	if (ImGui::Checkbox("Force Position##01", &v::mod_jbuild_forcepos.evar->enabled))
		v::mod_jbuild_forcepos.SetValue(v::mod_jbuild_forcepos.isEnabled());

	if (ImGui::Checkbox("Draw Hitbox##01", &v::mod_jbuild_hitbox.evar->enabled))
		v::mod_jbuild_hitbox.SetValue(v::mod_jbuild_hitbox.isEnabled());

	if (ImGui::Checkbox("Draw WASD##01", &v::mod_jbuild_wasd.evar->enabled))
		v::mod_jbuild_wasd.SetValue(v::mod_jbuild_wasd.isEnabled());

	ImGui::NewLine();
	ImGui::Text("Movement");
	ImGui::Separator();

	if (ImGui::Checkbox("Use Sprint", &v::mod_jbuild_sprint.evar->enabled)) {
		v::mod_jbuild_sprint.SetValue(v::mod_jbuild_sprint.isEnabled());
		jbuilder.OnUpdateOffsets();
		jbuilder.OnUpdateAllPositions();
	}

	ImGui::PushItemWidth(100);
	if (ImGui::DragFloat("Jump Velocity", &v::mod_jbuild_jvel.evar->floatValue, 1.f, 0, 362)) {
		jbuilder.OnUpdateOffsets();
		jbuilder.OnUpdateAllPositions();
	}

	ImGui::EndGroup();
}

void r::R_JumpBuilder_ToggleFreeMode()
{
	const bool isUFO = clients->snap.ps.pm_type == PM_UFO;

	//dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

	//if (g_gravity) {
	//	if (!jbuilder.InFreeMode() && !isUFO) {
	//		g_gravity->current.value = 0;
	//	}
	//	else {
	//		g_gravity->current.value = 800;
	//	}
	//}

	//ImGui::Text("press [spacebar] to toggle free mode");
	const ImGuiIO& io = ImGui::GetIO();

	if (io.KeysDownDuration['F'] == 0.f && VID_ACTIVE) {
		v::mod_jbuild_forcepos.SetValue(!v::mod_jbuild_forcepos.isEnabled());

		if (v::mod_jbuild_forcepos.isEnabled() && jbuilder.InFreeMode())
			jbuilder.SetFreeMode(false);
	}
	else if (io.KeysDownDuration[VK_SPACE] == 0.f && VID_ACTIVE) {
		jbuilder.SetFreeMode(!jbuilder.InFreeMode());

		

		r::R_RemoveInput(!jbuilder.InFreeMode(), false);

		dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

		if (g_gravity && !jbuilder.InFreeMode())
			if (g_gravity->current.value == 0) {
				g_gravity->current.value = 800;
				g_gravity->latched.value = 800;
			}

		if (jbuilder.InFreeMode() && !isUFO) {
			Cbuf_AddText("ufo\n", cgs->clientNum);
		}
		else if (!jbuilder.InFreeMode() && isUFO)
			Cbuf_AddText("ufo\n", cgs->clientNum);

	}
}
void r::R_JumpBuilder_Builder()
{
	std::vector<segment_data_s> &segments = jbuilder.segments; 
	const ImGuiIO* io = &ImGui::GetIO();
	if (!jbuilder.builder_data.run_created) {
		ImGui::Text("Create Project\t\t\t\t");
		UI_DrawGradientZone(ImVec2(170, 70));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (ImGui::Button("Create New"))
			jbuilder.get_playerState = true;

		ImGui::EndGroup();
		ImGui::NewLine();
	}else{

		ImGui::Text("Segments\t\t\t\t");
		UI_DrawGradientZone(ImVec2(550, 130));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		static int old_segment = jbuilder.current_segment;

		if (ImGui::SliderInt("Segment", &jbuilder.current_segment, 0, jbuilder.segments.size() - 1, "%d")) {

			if(jbuilder.current_segment != old_segment)
				jbuilder.OnUpdateAllPositions();

			old_segment = jbuilder.current_segment;

			jbuilder.preview_frame = jbuilder.segments[jbuilder.current_segment].begin;
		}
		int total_frames = ImClamp<int>(jbuilder.GetTotalFrames(), 1, INT_MAX);

		if (ImGui::Button("Add"))
			jbuilder.OnAddSegment();

		ImGui::SameLine();

		if (ImGui::Button("Delete"))
			jbuilder.OnDeleteSegment();

		ImGui::SameLine();

		if (ImGui::Button("Insert"))
			jbuilder.OnInsertSegment();

		static bool isPlayback(false);
		static int& menu_frame = jbuilder.preview_frame;

		if (!isPlayback) {
			if (ImGui::Button(">##03") || io->KeysDownDuration['P'] == 0.f)
				isPlayback = true;
		}
		else {
			if (ImGui::Button("P##03") || io->KeysDownDuration['P'] == 0.f)
				isPlayback = false;
		}

		if (isPlayback && menu_frame < total_frames) {
			menu_frame++;
		}
		else
			isPlayback = false;


		ImGui::SameLine();
		if (ImGui::Button("R##022") || io->KeysDownDuration['R'] == 0.f)
			menu_frame = NULL;




		ImGui::EndGroup();


		ImGui::Text("\nEditing\t\t\t\t");
		UI_DrawGradientZone(ImVec2(550, 100));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (ImGui::SliderInt("Frame", &jbuilder.preview_frame, 1, total_frames-1, "%d", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput)) {

			size_t indx(0);
			for (const auto& i : jbuilder.segments) {
				if (i.end > jbuilder.preview_frame && i.begin < jbuilder.preview_frame) {
					jbuilder.current_segment = indx;
					jbuilder.OnUpdateOffsets();
				}
				indx++;
			}
		}

		static int old_count = segments[jbuilder.current_segment].framecount;

		if (ImGui::DragInt("Frame Count", &segments[jbuilder.current_segment].framecount, 5, 1, 2000, "%d", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput)) {

			//if (segments[jbuilder.current_segment].framecount < old_count) {
			//	segments[jbuilder.current_segment];
			//}

			segments[jbuilder.current_segment].end += (segments[jbuilder.current_segment].framecount - old_count);
			old_count = segments[jbuilder.current_segment].framecount;

			jbuilder.OnUpdateOffsets();
			jbuilder.OnUpdateAllPositions();

			menu_frame = ImClamp<int>(menu_frame, 0, jbuilder.GetTotalFrames());

		}

		ImVec2 rectMin, rectMax;

		ImGui::NewLine();

		ImGui::Text("\t");
		ImGui::SameLine();

		R_JumpBuilder_ConstructKey(segments[jbuilder.current_segment].forwardmove,	127,	"W##01");
		R_JumpBuilder_ConstructKey(segments[jbuilder.current_segment].rightmove,	-127,	"A##01");

		ImGui::SameLine();
		ImGui::Text("\t");
		ImGui::SameLine();

		R_JumpBuilder_ConstructKey(segments[jbuilder.current_segment].rightmove,	127,	"D##01");

		ImGui::Text("\t ");
		ImGui::SameLine();
		
		R_JumpBuilder_ConstructKey(segments[jbuilder.current_segment].forwardmove,	-127,	"S##01");

		ImGui::EndGroup();

	
		ImGui::Text("Project\t\t\t\t");
		UI_DrawGradientZone(ImVec2(200, 140));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();
		static bool editingStart(FALSE);
		jump_data* jData = jbuilder.FetchFrameData(jbuilder.preview_frame);
		if (jData) {
			if (jbuilder.current_segment == NULL) {
				if (ImGui::Button("Modify Start"))
					editingStart = !editingStart;

				ImGui::SameLine();  MetricsHelpMarker("modify the starting position in case you created the project from a bad spot");
			}
			else
				ImGui::Text("fps: %i", jData->FPS);

			if (v::mod_jbuild_forcepos.isEnabled() && !jbuilder.InFreeMode()) {
				const vec3_t null = { 0,0,0 };
				VectorCopy(jData->origin, ps_loc->origin);
				//VectorCopy(jData->angles, ps_loc->viewangles);
				CG_SetPlayerAngles(clients->cgameViewangles, jData->angles);
				VectorCopy(null, ps_loc->velocity);
			}

		}
		if (jbuilder.GetTotalFrames() > 0) {
			if (ImGui::Button("Delete Project")) {
				editingStart = false;
				jbuilder.OnDeleteProject();
			}
		}

		ImGui::EndGroup();

		R_JumpBuilder_ToggleFreeMode();

		if (editingStart) {
			static DWORD ms = Sys_MilliSeconds();
			ImGui::Begin("Edit Start", &editingStart, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text("\t");
			ImGui::SameLine();
			//ImGui::SameLine();
			ImGui::Button("W##0022");
			if (ImGui::IsItemActive()) {
				if (ms + 200 < Sys_MilliSeconds()) {
					vec3_t outDir;
					vec3_t angles = { 0, jbuilder.segments[NULL].jData[0].angles[YAW], 0 };
					AnglesToForward(angles, jbuilder.segments[NULL].jData[0].origin, 2, jbuilder.new_start_origin);
					ms = Sys_MilliSeconds();
					jbuilder.OnUpdateAllPositions();

				}
			}
			ImGui::Button("A##0022");
			if (ImGui::IsItemActive()) {
				if (ms + 200 < Sys_MilliSeconds()) {
					vec3_t outDir;
					vec3_t angles = { 0,  jbuilder.segments[NULL].jData[0].angles[YAW], 0 };
					AnglesToRight(angles, jbuilder.segments[NULL].jData[0].origin, -2, jbuilder.new_start_origin);
					ms = Sys_MilliSeconds();
					jbuilder.OnUpdateAllPositions();

				}
			}
			ImGui::SameLine();
			ImGui::Text("\t");
			ImGui::SameLine();
			ImGui::Button("D##0022");
			if (ImGui::IsItemActive()) {
				if (ms + 200 < Sys_MilliSeconds()) {
					vec3_t outDir;
					vec3_t angles = { 0, jbuilder.segments[NULL].jData[0].angles[YAW], 0 };
					AnglesToRight(angles, jbuilder.segments[NULL].jData[0].origin, 2, jbuilder.new_start_origin);
					ms = Sys_MilliSeconds();
					jbuilder.OnUpdateAllPositions();

				}
			}

			ImGui::Text("\t ");
			ImGui::SameLine();
			ImGui::Button("S##0022");
			if (ImGui::IsItemActive()) {
				if (ms + 200 < Sys_MilliSeconds()) {
					vec3_t outDir;
					vec3_t angles = { 0, jbuilder.segments[NULL].jData[0].angles[YAW], 0 };
					AnglesToForward(angles, jbuilder.segments[NULL].jData[0].origin, -2, jbuilder.new_start_origin);
					ms = Sys_MilliSeconds();
					jbuilder.OnUpdateAllPositions();

				}
			}
			if(ImGui::SliderFloat("YAW", &cg::jbuilder.new_start_angles[YAW], -180.f, 180.f, "%.3f"))
				jbuilder.OnUpdateAllPositions();


			ImGui::End();


		}

	}
	
	

}