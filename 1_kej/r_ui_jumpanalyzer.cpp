#include "pch.h"


void r::R_JumpView_ToggleFreeMode()
{
	if (!analyzer.InFreeMode())
		cgs->snap->ps.velocity[2] = 0;

	ImGui::Text("press [spacebar] to toggle free mode");
	const ImGuiIO& io = ImGui::GetIO();

	if (io.KeysDownDuration['F'] == 0.f && VID_ACTIVE) {
		v::mod_jumpv_forcepos.SetValue(!v::mod_jumpv_forcepos.isEnabled());

		if (v::mod_jumpv_forcepos.isEnabled() && analyzer.InFreeMode())
			analyzer.SetFreeMode(false);
	}
	else if (io.KeysDownDuration[VK_SPACE] == 0.f && VID_ACTIVE) {
		analyzer.SetFreeMode(!analyzer.InFreeMode());

		const bool isUFO = clients->snap.ps.pm_type == PM_UFO;

		r::R_RemoveInput(!analyzer.InFreeMode(), false);

		dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

		if (g_gravity && !analyzer.InFreeMode())
			if (g_gravity->current.value == 0) {
				g_gravity->current.value = 800;
				g_gravity->latched.value = 800;
			}

		if (analyzer.InFreeMode() && !isUFO) {
			Cbuf_AddText("ufo\n", cgs->clientNum);
		}
		else if (!analyzer.InFreeMode() && isUFO)
			Cbuf_AddText("ufo\n", cgs->clientNum);

	}
}
void r::R_JumpView_Main(std::vector<jump_data>& container)
{
	//this function might need some cleanup

	static int& menu_frame = analyzer.preview_frame;
	static DWORD ms = Sys_MilliSeconds();
	static bool& isPlayback = analyzer.is_playback;
	const ImGuiIO& io = ImGui::GetIO();
	static float timeScale = 1.f;

	ImGui::BeginGroup();

	R_JumpView_ToggleFreeMode();


	ImGui::NewLine();

	r::UI_DrawGradientZone(ImVec2(330, 80));
	ImGui::PushItemWidth(100);
	ImGui::SliderInt("Frame", &menu_frame, 0, analyzer.GetTotalFrames(container), "%u", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput);

	//ImGui::SameLine();
	if (ImGui::Button("R") || io.KeysDownDuration['R'] == 0.f && VID_ACTIVE) {
		isPlayback = false;
		menu_frame = 0;
	}
	dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");


	if (g_gravity) {
		g_gravity->current.value = 0;
	}

	ImGui::SameLine();
	if (ImGui::Button(isPlayback == false ? ">" : "P") || io.KeysDownDuration['P'] == 0.f) {
		if (!isPlayback)
			isPlayback = true;
		else isPlayback = false;
	}
	if (analyzer.isPlayback()) {
		static int wait_incr(0);
		//static int32_t oldServerTime = jumpanalyzer.serverTime;

		//if (glm::distance((float)oldServerTime, (float)jumpanalyzer.serverTime) > 100) //true on map restart
		//	oldServerTime = jumpanalyzer.serverTime;

		dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");
		const jump_data* jData = analyzer.FetchFrameData(container, menu_frame);
		

		if (wait_incr > timeScale - 1 && jData && com_maxfps&& g_gravity) {
			com_maxfps->current.integer = 125.f;
			g_gravity->current.value = 0;
			wait_incr = 0;
			if (menu_frame < analyzer.GetTotalFrames(container))
				menu_frame++;
			else isPlayback = false;
		}
		wait_incr++;

	}


	ImGui::SameLine();
	ImGui::Button("-");
	if (ImGui::IsItemActive()) {
		if (menu_frame - 1 > 0 && ms + 200 < Sys_MilliSeconds()) {
			menu_frame--;
			ms = Sys_MilliSeconds();
		}
	}
	ImGui::SameLine();
	ImGui::Button("+");
	if (ImGui::IsItemActive()) {
		if (menu_frame + 1 <= analyzer.GetTotalFrames(container) && ms + 200 < Sys_MilliSeconds()) {
			menu_frame++;
			ms = Sys_MilliSeconds();
		}
	}

	ImGui::SameLine();
	ImGui::PushItemWidth(50);
	ImGui::DragFloat("Slow-mo Scale", &timeScale, 0.1f, 1.f, 10.f, "%.3f", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput);

	if (VID_ACTIVE) {
		if (menu_frame + 1 <= analyzer.GetTotalFrames())
			menu_frame += ((GetAsyncKeyState(VK_RIGHT) & 1) == true);
		if (menu_frame - 1 > 0)
			menu_frame -= ((GetAsyncKeyState(VK_LEFT) & 1) == true);
	}

	ImGui::Text("Jump Data");
	r::UI_DrawGradientZone(ImVec2(330, 270));
	ImGui::Text("\t");
	ImGui::SameLine();

	ImGui::BeginGroup();
	//ImGui::Separator();

	jump_data* jData = analyzer.FetchFrameData(container, menu_frame);


	//rpg prediction
	const int maxAllowedPrediction = analyzer.GetTotalFrames(container) - menu_frame;
	int futureFrame = maxAllowedPrediction;
	static int rpg_frames_min, rpg_frames_max;
	if (futureFrame >= 200)
		futureFrame = 200;

	jump_data* jPredictedData = analyzer.FetchFrameData(container, menu_frame + futureFrame);

	bool RPGprePrediction = false;
	const std::set<int>::iterator it_rpg = analyzer.Segmenter_RecordingExists() ? analyzer.s_rpgFrames.begin() : analyzer.rpgFrames.begin();

	if (analyzer.rpgFrames.size() > 0)
		if (*it_rpg < 200)
			RPGprePrediction = true;

	if(jPredictedData->rpg_fired || RPGprePrediction)
	{
		rpg_frames_min = menu_frame;
		rpg_frames_max = menu_frame + 400;
	
	}
	//rpg prediction ends



	if (jData) {

		const int32_t velocity = (int32_t)glm::length(glm::vec2(jData->velocity[0], jData->velocity[1]));

		const float opt = getOptForAnalyzer(jData);

		ImGui::Text("fps: %i", jData->FPS);
		ImGui::Text("velocity: %i (Z: %.3f)", velocity, jData->velocity[2]);
		ImGui::Text("origin: %.3f, %.3f, %.3f", jData->origin[0], jData->origin[1], jData->origin[2]);
		ImGui::Text("angles: %.3f, %.3f", jData->angles[0], jData->angles[1]);
		ImGui::Text("rpg fired: %i", jData->rpg_fired);
		ImGui::Text("bounced: %i", jData->bounced);
		ImGui::Text("keys: %s", r::R_UserCmdKeysPressed(jData->forwardmove, jData->rightmove).c_str());

		if(jData->rightmove != NULL)
			ImGui::Text("strafe accuracy: %.3f", DistanceToOpt(opt, jData->angles[YAW]));
		else 
			ImGui::Text("strafe accuracy: N/A"); //would require additional data to be saved

		ImGui::Text("colliding: %i", jData->colliding);
		ImGui::Text("jumped: %i", jData->jumped);

		ImGui::EndGroup();
		const vec3_t empty = { 0,0,0 };

		if (!analyzer.InFreeMode() && v::mod_jumpv_forcepos.isEnabled() || GetAsyncKeyState('C') & 1 && VID_ACTIVE) {
			CG_SetPlayerAngles(clients->cgameViewangles, jData->angles);
			VectorCopy(jData->origin, ps_loc->origin);
			ps_loc->origin[2] -= (70.f - jData->maxs[2]);
			VectorCopy(empty, ps_loc->velocity);
		}
		
		R_JumpView_HandleWeapons(menu_frame, rpg_frames_min, rpg_frames_max);

		static ImVec2 size = ImGui::GetItemRectSize();

		ImGui::NewLine();
		ImGui::Text("Events");
		r::UI_DrawGradientZone(ImVec2(330, size.y + 20));
		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		static int32_t bounce_indx(0);

		R_JumpView_BounceButtons(menu_frame);

		if (ImGui::Button("highest point"))
			menu_frame = analyzer.FindHighestPoint(container);

		ImGui::EndGroup();

		size = ImGui::GetItemRectSize();

		ImGui::NewLine();
		ImGui::Text("Segmenting");
		r::UI_DrawGradientZone(ImVec2(330, 100));
		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (ImGui::Button("Mark segment")) {
			Com_Printf(CON_CHANNEL_OBITUARY, "^2Segment has been marked!\n");
			analyzer.segment_frame = menu_frame;
		}

		if (!analyzer.Segmenter_RecordingExists())
			ImGui::BeginDisabled();

		static bool confirm(false);

		if (ImGui::Button("Merge")) {
			confirm = !confirm;


		}ImGui::SameLine(); r::MetricsHelpMarker("Merges the original run and the segment\nWarning: This action cannot be undone");


		if (confirm) {

			ImGui::Begin("Confirmation##01", &confirm, ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::Text("Are you sure? This action will overwrite your original save.");

			ImGui::NewLine();
			ImGui::Separator();

			if (r::ButtonCentered("yes##01")) {
			//	std::vector<jump_data> tmp = analyzer.data;

				std::cout << "result.size before: " << analyzer.data.size() << '\n';


				analyzer.data.erase(analyzer.data.begin() + analyzer.segment_frame, analyzer.data.end());
				

		/*		for (int i = analyzer.segment_frame; i < tmp.size(); i++) {

					analyzer.data.push_back(tmp[i]);
				}*/

				std::cout << "result.size before2: " << analyzer.data.size() << '\n';

				analyzer.data.insert(analyzer.data.end(), analyzer.segData.begin(), analyzer.segData.end());

				std::cout << "result.size after: " << analyzer.data.size() << '\n';
				std::cout << "segment offset: " << analyzer.segmenterData.mergeFrame << '\n';
				//std::cout << "tmp.size: " << tmp.size() << '\n';
				if (analyzer.data.size() > 0) {
					//std::cout << "result[0].angles[1]: " << tmp[0].angles[1] << '\n';
					std::cout << "data[0].angles[1]  : " << analyzer.data[0].angles[1] << '\n';
				}

				analyzer.OnEndSegment();
				analyzer.segData.erase(analyzer.segData.begin(), analyzer.segData.end());
				analyzer.segData.clear();
				analyzer.segData.resize(0);
			}

			else if (r::ButtonCentered("no##01"))
				confirm = false;

			ImGui::End();

		}

		if (!analyzer.Segmenter_RecordingExists())
			ImGui::EndDisabled();

		ImGui::EndGroup();
		ImGui::EndGroup();
		R_JumpView_IO();

		if (v::mod_pmove_fixed.isEnabled()) {
			ImGui::Text("\n\n\n");
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "Warning: fixed fps can cause playback issues!");
		}
		

	}
	else {
		ImGui::Text("ERROR: invalid frame data\n");
	}

	

}
void r::R_JumpView_HandleWeapons(int& menu_frame, int min_frame, int max_frame)
{
	const int rpg = BG_FindWeaponIndexForName("rpg_mp");
	const int rpg_sustain = BG_FindWeaponIndexForName("rpg_sustain_mp");
	const playerState_s ps = clients->snap.ps;
	static bool rpg_used;

	if (menu_frame > min_frame && menu_frame < max_frame && (ps.weapon != rpg && ps.weapon != rpg_sustain) && !rpg_used) {
		//switch to rpg if it used during the frame
		int weapons[64];
		size_t count = G_GetWeaponsList(weapons);

		for (size_t i = 0; i < count; i++) {


			if (!strcmp(BG_WeaponNames[weapons[i]]->szInternalName, "rpg_mp")) {
				rpg_used = true;
				Cbuf_AddText("+actionslot 4\n", cgs->clientNum);
				//G_SelectWeaponIndex(rpg, -1); //apparently doesn't work with custom maps
			}
			else if (!strcmp(BG_WeaponNames[weapons[i]]->szInternalName, "rpg_sustain_mp")) {
				rpg_used = true;

				Cbuf_AddText("+actionslot 4\n", cgs->clientNum);
				//G_SelectWeaponIndex(rpg_sustain, -1); //apparently doesn't work with custom maps
			}
		}
	}
	else if ((menu_frame < min_frame || menu_frame > max_frame) && (ps.weapon == rpg || ps.weapon == rpg_sustain)) {
		rpg_used = false;
		Cbuf_AddText("weapnext\n", cgs->clientNum);

	}
}
void r::R_JumpView_BounceButtons(int& menu_frame)
{

	static std::set<int>::iterator 
		it		= analyzer.Segmenter_RecordingExists() ? analyzer.s_bounceFrames.begin()	: analyzer.bounceFrames.begin(),
		it_rpg	= analyzer.Segmenter_RecordingExists() ? analyzer.s_rpgFrames.begin()		: analyzer.rpgFrames.begin(),
		it_jump = analyzer.Segmenter_RecordingExists() ? analyzer.s_jumpFrame.begin()		: analyzer.jumpFrame.begin();

	static DWORD end_recording_time = analyzer.LastRecordingStoppedTime();

	std::set<int>& rpg = analyzer.isSegmenting() ? analyzer.s_rpgFrames : analyzer.rpgFrames;
	std::set<int>& jump = analyzer.isSegmenting() ? analyzer.s_jumpFrame : analyzer.jumpFrame;
	std::set<int>& bounce = analyzer.isSegmenting() ? analyzer.s_bounceFrames : analyzer.bounceFrames;

	if (analyzer.LastRecordingStoppedTime() != end_recording_time) { // a way to track if this is a new run
		it = bounce.begin();
		end_recording_time = analyzer.LastRecordingStoppedTime();
	}

	if (bounce.size() > 0) {
		ImGui::Text("bounce");


		ImGui::SameLine();
		if (!R_JumpView_EventButtons(bounce, menu_frame, "<##01", ">##01")) {
			//if (ImGui::Button("Go##00")) {
			//	menu_frame = *it;
			//}
		}
	}
	if (rpg.size() > 0) {
		ImGui::Text("rpg   ");

		ImGui::SameLine();
		if (!R_JumpView_EventButtons(rpg, menu_frame, "<##02", ">##02")) {
			//if (ImGui::Button("Go##01")) {
			//	menu_frame = *it_rpg;
			//}
		}
	}
	if (jump.size() > 0) {
		ImGui::Text("jump  ");

		ImGui::SameLine();
		if (!R_JumpView_EventButtons(jump, menu_frame, "<##03", ">##03")) {
			//if (ImGui::Button("Go##02")) {
			//	menu_frame = *it_jump;
			//}
		}
	}

}
//go to the closest event from current frame
bool r::R_JumpView_EventButtons(std::set<int>& eventV, int& menu_frame, const char* prevBut, const char* nextBut)
{
	if (eventV.size() > 1) {
		if (ImGui::Button(prevBut)) {


			int32_t closest_frame(menu_frame); //find the closest bounce frame from current frame 
			int32_t closest(menu_frame);

			for (auto& i : eventV) {

				if (i > menu_frame) //only want to search backwards
					break;

				if (i == menu_frame)
					continue;

				const int32_t dist = glm::distance((float)i, (float)menu_frame);

				if (closest > dist) {
					closest = dist;
					closest_frame = i;
				}
			}

			menu_frame = closest_frame;
		}

		ImGui::SameLine();

		if (ImGui::Button(nextBut)) {

			int32_t closest_frame(analyzer.GetTotalFrames()); //find the closest bounce frame from current frame 
			int32_t closest(analyzer.GetTotalFrames());

			for (auto& i : eventV) {

				if (i <= menu_frame || i == analyzer.GetTotalFrames()) //only want to search forwards
					continue;

				const int32_t dist = (int32_t)glm::distance((float)i, (float)menu_frame);

				if (closest > dist) {
					closest = dist;
					closest_frame = i;
				}
			}

			menu_frame = closest_frame;
		}
		return true;
	}
	return false;
}

void r::R_JumpView_Preferences()
{
	if (ImGui::Checkbox("Force Position", &v::mod_jumpv_forcepos.evar->enabled))
		v::mod_jumpv_forcepos.SetValue(v::mod_jumpv_forcepos.isEnabled());

	if (ImGui::Checkbox("Path Line", &v::mod_jumpv_path.evar->enabled))
		v::mod_jumpv_path.SetValue(v::mod_jumpv_path.isEnabled());

	if (ImGui::Checkbox("Show Hitbox", &v::mod_jumpv_hitbox.evar->enabled))
		v::mod_jumpv_hitbox.SetValue(v::mod_jumpv_hitbox.isEnabled());

}
void r::R_JumpView_IO()
{
	
	ImGui::NewLine();
	ImGui::Text("File");
	r::UI_DrawGradientZone(ImVec2(330, 100));
	ImGui::Text("\t");
	ImGui::SameLine();

	ImGui::BeginGroup();
	static bool is_saving, is_loading;
	static std::vector<std::string> existingRuns;
	static std::vector<const char*> existingRuns_c;

	if (analyzer.RecordingExists()) {
		if (ButtonCentered("Save Run"))
			is_saving = !is_saving;
	}

	if (ButtonCentered("Load Run")) {
		is_loading = !is_loading;

		if (is_loading) {
			const dvar_s* mapname = Dvar_FindMalleableVar("mapname");

			if (!mapname) {
				Com_PrintError(CON_CHANNEL_OBITUARY, "mapname dvar does not exist!\n");
				is_loading = false;
			}
			else {
				existingRuns.erase(existingRuns.begin(), existingRuns.end());
				existingRuns.clear();
				existingRuns.resize(0);

				existingRuns_c.erase(existingRuns_c.begin(), existingRuns_c.end());
				existingRuns_c.clear();
				existingRuns_c.resize(0);

				if (!analyzer.IO_FindExistingRuns(mapname->current.string, existingRuns)) {
					Com_PrintError(CON_CHANNEL_OBITUARY, "See console or log file for more information\n");
					is_loading = false;
				}



			}

		}

	}


	if (is_saving) {

		ImGui::Begin("Give the run a name", &is_saving, ImGuiWindowFlags_AlwaysAutoResize);

		static char buff[MAX_PATH];
		ImGui::PushItemWidth(300);
		ImGui::InputText("Run name", buff, MAX_PATH, ImGuiTextFlags_None);

		if (ButtonCentered("Save##02")) {
			if (!analyzer.IO_WriteData(buff, analyzer.data)) {
				Com_PrintError(CON_CHANNEL_OBITUARY, "See console or log file for more information\n");
			}
			is_saving = false;
		}

		ImGui::End();


	}
	ImGui::EndGroup();

	if (is_loading && existingRuns.size() > 0) {

		ImGui::Begin("Select a run", &is_loading, ImGuiWindowFlags_AlwaysAutoResize);

		static int selected_map(0);

		if (existingRuns_c.size() == NULL) {
			for (size_t i = 0; i < existingRuns.size(); i++)
				existingRuns_c.push_back(existingRuns[i].c_str());
		}
		ImGui::PushItemWidth(50.f + 7 * (float)strlen(existingRuns_c[selected_map]));
		ImGui::Combo("Available Runs", &selected_map, existingRuns_c.data(), existingRuns_c.size());


		if (ButtonCentered("Load Run##02")) {
			if (!analyzer.IO_ReadData(existingRuns_c[selected_map])) {
				Com_PrintError(CON_CHANNEL_OBITUARY, "See console or log file for more information\n");
			}
			is_loading = false;
		}
	


		ImGui::End();


	}



}
void r::R_JumpView(bool& isOpen)
{
	analyzer.setPreviewState(isOpen);
	if (!isOpen)
		return;

	static ImVec2 old_size;

	ImGui::Begin("Jump View", &isOpen, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);

	if (!analyzer.RecordingExists()) {
		ImGui::Text("nothing has been recorded yet!\nYou can load existing recordings however (if there are any)");
		R_JumpView_IO();
	}
	else {


		if (ImGui::BeginTabBar("##jumpview_tabs", ImGuiTabBarFlags_None)) {
			if (ImGui::BeginTabItem("Main view")) {

				if (!analyzer.Segmenter_RecordingExists())
					R_JumpView_Main(analyzer.data);
				else
					R_JumpView_Main(analyzer.segData);

				ImGui::EndTabItem();

			}if (ImGui::BeginTabItem("Preferences")) {
				R_JumpView_Preferences();
				ImGui::EndTabItem();

			}if (ImGui::BeginTabItem("Help")) {
				R_JumpView_Help();
				ImGui::EndTabItem();

			}

		}
		ImGui::EndTabBar();

		

	}


	ImGui::End();

}