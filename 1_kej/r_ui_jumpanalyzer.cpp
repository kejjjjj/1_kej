#include "pch.h"


void r::R_JumpView_Main()
{
	//this function might need some cleanup

	static int& menu_frame = analyzer.preview_frame;
	static DWORD ms = Sys_MilliSeconds();
	static bool isPlayback;
	const ImGuiIO& io = ImGui::GetIO();

	if (!VID_ACTIVE) {
		ImGui::Text("WINDOW NOT ACTIVE\n");
		return;
	}

	ImGui::BeginGroup();

	if (!analyzer.InFreeMode())
		cgs->snap->ps.velocity[2] = 0;

	ImGui::Text("press [spacebar] to toggle free mode");

	if (GetAsyncKeyState(VK_SPACE) & 1 && VID_ACTIVE) {
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
	//else if (GetAsyncKeyState('F') & 1) {
	//	v::mod_jumpv_forcepos.SetValue(!v::mod_jumpv_forcepos.isEnabled());

	//	if (v::mod_jumpv_forcepos.isEnabled() && analyzer.InFreeMode())
	//		analyzer.SetFreeMode(false);
	//}
	ImGui::NewLine();

	ImGui::PushItemWidth(100);
	ImGui::SliderInt("Frame", &menu_frame, 0, analyzer.GetTotalFrames(), "%u", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput);

	//ImGui::SameLine();
	if (ImGui::Button("R") || GetAsyncKeyState('R') & 1) {
		isPlayback = false;
		menu_frame = 0;
	}
	dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");


	if (g_gravity) {
		g_gravity->current.value = 0;
	}

	const char* character = isPlayback == false ? ">" : "P";

	ImGui::SameLine();
	if (ImGui::Button(character) || GetAsyncKeyState('P') & 1) {
		if (!isPlayback)
			isPlayback = true;
		else isPlayback = false;
	}
	if (isPlayback) {
		static int32_t oldServerTime = jumpanalyzer.serverTime;

		if (glm::distance((float)oldServerTime, (float)jumpanalyzer.serverTime) > 100) //true on map restart
			oldServerTime = jumpanalyzer.serverTime;

		dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");
		jump_data* jData = analyzer.FetchFrameData(menu_frame);
		if (com_maxfps && g_gravity && jumpanalyzer.serverTime > oldServerTime + 3 && jData) {
			com_maxfps->current.integer = jData->FPS;
			g_gravity->current.value = 0;
			oldServerTime = jumpanalyzer.serverTime;

			if (menu_frame < analyzer.GetTotalFrames())
				menu_frame++;
			else isPlayback = false;
		}


	}

	ImGui::SameLine();
	ImGui::Button("+");
	if (ImGui::IsItemActive()) {
		if (menu_frame + 1 <= analyzer.GetTotalFrames() && ms + 200 < Sys_MilliSeconds()) {
			menu_frame++;
			ms = Sys_MilliSeconds();
		}
	}
	ImGui::SameLine();
	ImGui::Button("-");
	if (ImGui::IsItemActive()) {
		if (menu_frame - 1 > 0 && ms + 200 < Sys_MilliSeconds()) {
			menu_frame--;
			ms = Sys_MilliSeconds();
		}
	}

	menu_frame += GetAsyncKeyState(VK_RIGHT) & 1 == true;
	menu_frame -= GetAsyncKeyState(VK_LEFT) & 1 == true;

	ImGui::Text("Jump Data");
	ImGui::Separator();

	jump_data* jData = analyzer.FetchFrameData(menu_frame);

	if (jData) {

		const int32_t velocity = (int32_t)glm::length(glm::vec2(jData->velocity[0], jData->velocity[1]));

		const float opt = getOptForAnalyzer(jData);

		ImGui::Text("fps: %i", jData->FPS);
		ImGui::Text("velocity: %i", velocity);
		ImGui::Text("origin: %.3f, %.3f, %.3f", jData->origin[0], jData->origin[1], jData->origin[2]);
		ImGui::Text("angles: %.3f, %.3f", jData->angles[0], jData->angles[1]);
		ImGui::Text("rpg fired: %i", jData->rpg_fired);
		ImGui::Text("bounced: %i", jData->bounced);
		ImGui::Text("keys: %s", r::R_UserCmdKeysPressed(jData->forwardmove, jData->rightmove).c_str());

		if(jData->rightmove != NULL)
			ImGui::Text("strafe accuracy: %.3f", DistanceToOpt(opt, jData->angles[YAW]));
		else
			ImGui::Text("strafe accuracy: N/A");

		ImGui::Text("colliding: %i", jData->colliding);
		ImGui::Text("jumped: %i", jData->jumped);
		const vec3_t empty = { 0,0,0 };

		if (!analyzer.InFreeMode() && v::mod_jumpv_forcepos.isEnabled() || GetAsyncKeyState('C') & 1) {
			CG_SetPlayerAngles(clients->cgameViewangles, jData->angles);
			VectorCopy(jData->origin, ps_loc->origin);
			VectorCopy(empty, ps_loc->velocity);
		}
	}
	else {
		ImGui::Text("ERROR: invalid frame data\n");
	}

	ImGui::NewLine();
	ImGui::Text("Events");
	ImGui::Separator();

	static int32_t bounce_indx(0);

	R_JumpView_BounceButtons(menu_frame);

	if (ImGui::Button("highest point"))
		menu_frame = analyzer.FindHighestPoint();

	
	ImGui::EndGroup();
	R_JumpView_IO();

}
void r::R_JumpView_BounceButtons(int& menu_frame)
{

	static std::set<int>::iterator it = analyzer.bounceFrames.begin(), it_rpg = analyzer.rpgFrames.begin();
	static DWORD end_recording_time = analyzer.LastRecordingStoppedTime();

	if (analyzer.LastRecordingStoppedTime() != end_recording_time) { // a way to track if this is a new run
		it = analyzer.bounceFrames.begin();
		end_recording_time = analyzer.LastRecordingStoppedTime();
	}

	if (analyzer.bounceFrames.size() > 0) {
		ImGui::Text("bounce");


		ImGui::SameLine();
		if (!R_JumpView_EventButtons(analyzer.bounceFrames, menu_frame, "<##01", ">##01")) {
			if (ImGui::Button("Go##00")) {
				menu_frame = *it;
			}
		}
	}
	if (analyzer.rpgFrames.size() > 0) {
		ImGui::Text("rpg  ");

		ImGui::SameLine();
		if (!R_JumpView_EventButtons(analyzer.rpgFrames, menu_frame, "<##02", ">##02")) {
			if (ImGui::Button("Go##01")) {
				menu_frame = *it_rpg;
			}
		}
	}
	if (analyzer.jumpFrame.size() > 0) {
		ImGui::Text("jump ");

		ImGui::SameLine();
		if (!R_JumpView_EventButtons(analyzer.jumpFrame, menu_frame, "<##03", ">##03")) {
			if (ImGui::Button("Go##02")) {
				menu_frame = *it_rpg;
			}
		}
	}

}
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

				const int32_t dist = glm::distance((float)i, (float)menu_frame);

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
	ImGui::Separator();

	static bool is_saving, is_loading;
	static std::vector<std::string> existingRuns;
	static std::vector<const char*> existingRuns_c;

	if (analyzer.RecordingExists()) {
		if (ImGui::Button("Save Run"))
			is_saving = !is_saving;
	}

	if (ImGui::Button("Load Run")) {
		is_loading = !is_loading;

		if (is_loading) {
			dvar_s* mapname = Dvar_FindMalleableVar("mapname");

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

	if (is_loading && existingRuns.size() > 0) {

		ImGui::Begin("Select a run", &is_loading, ImGuiWindowFlags_AlwaysAutoResize);

		static int selected_map(0);



		if (existingRuns_c.size() == NULL) {
			for (int i = 0; i < existingRuns.size(); i++)
				existingRuns_c.push_back(existingRuns[i].c_str());
		}
		ImGui::PushItemWidth(50 + 7 * strlen(existingRuns_c[selected_map]));
		ImGui::Combo("Available Runs", &selected_map, existingRuns_c.data(), existingRuns_c.size());


		if (ButtonCentered("Load Run##02")) {
			if (!analyzer.IO_ReadData(existingRuns_c[selected_map])) {
				Com_PrintError(CON_CHANNEL_OBITUARY, "See console or log file for more information\n");
			}
			is_loading = false;
		}
	


		ImGui::End();


	}

	//static char buff2[MAX_PATH];
	//ImGui::PushItemWidth(150);
	//ImGui::InputText("file name##01", buff2, MAX_PATH, ImGuiTextFlags_None);
	//if (ImGui::Button("Read Data")) {
	//	if (!analyzer.IO_ReadData(buff2)) {
	//		Com_PrintError(CON_CHANNEL_OBITUARY, "See console or log file for more information\n");
	//	}
	//}


}
void r::R_JumpView(bool& isOpen)
{
	analyzer.setPreviewState(isOpen);
	if (!isOpen)
		return;

	static ImVec2 old_size;

	ImGui::Begin("Jump View", &isOpen);
	ImGui::SetWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);

	static bool transparent;

	if (GetAsyncKeyState(VK_MENU) & 1) {
		transparent = !transparent;

		if (transparent) {
			old_size = ImGui::GetWindowSize();
			ImGui::SetWindowSize(ImVec2(1, 1));
		}else
			ImGui::SetWindowSize(old_size);

	}

	if (!analyzer.RecordingExists()) {
		ImGui::Text("nothing has been recorded yet!\nYou can load existing recordings however (if there are any)");
		R_JumpView_IO();
	}
	else {


		if (ImGui::BeginTabBar("##jumpview_tabs", ImGuiTabBarFlags_None)) {
			if (ImGui::BeginTabItem("Main view")) {
				R_JumpView_Main();
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