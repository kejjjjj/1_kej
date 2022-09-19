#include "pch.h"


void r::R_JumpView_Main()
{
	static int& menu_frame = analyzer.preview_frame;
	static DWORD ms = Sys_MilliSeconds();
	static bool isPlayback;


	if (!analyzer.InFreeMode())
		cgs->snap->ps.velocity[2] = 0;

	ImGui::Text("press [spacebar] to toggle free mode");

	if (GetAsyncKeyState(VK_SPACE) & 1) {
		analyzer.SetFreeMode(!analyzer.InFreeMode());

		const bool isUFO = clients->snap.ps.pm_type == PM_UFO;

		r::R_RemoveInput(!analyzer.InFreeMode(), false);

		if (analyzer.InFreeMode() && !isUFO) {
			Cbuf_AddText("ufo\n", cgs->clientNum);
		}
		else if (!analyzer.InFreeMode() && isUFO)
			Cbuf_AddText("ufo\n", cgs->clientNum);

	}

	ImGui::NewLine();

	ImGui::PushItemWidth(100);
	ImGui::SliderInt("Frame", &menu_frame, 0, analyzer.GetTotalFrames(), "%u", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput);

	ImGui::SameLine();
	if (ImGui::Button("R")) {
		isPlayback = false;
		menu_frame = 0;
	}
	dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");


	if (g_gravity) {
		g_gravity->current.value = 0;
	}

	const char* character = isPlayback == false ? ">" : "P";

	ImGui::SameLine();
	if (ImGui::Button(character)) {
		if (!isPlayback)
			isPlayback = true;
		else isPlayback = false;
	}
	if (isPlayback) {
		dvar_s* com_maxfps = Dvar_FindMalleableVar("com_maxfps");
		if (com_maxfps && g_gravity) {
			com_maxfps->current.integer = 1000.f / 4;
			g_gravity->current.value = 0;
		}

		if (menu_frame < analyzer.GetTotalFrames())
			menu_frame++;
		else isPlayback = false;
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
		ImGui::Text("strafe accuracy: %.3f", DistanceToOpt(opt, jData->angles[YAW]));
		ImGui::Text("colliding: %i", jData->colliding);
		const vec3_t empty = { 0,0,0 };

		if (!analyzer.InFreeMode() && v::mod_jumpv_forcepos.isEnabled()) {
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


	if (ImGui::Button("on bounce"))
		menu_frame = analyzer.FindBounceFrame();
	if (ImGui::Button("on rpg shot"))
		menu_frame = analyzer.FindRpgShot();
	if (ImGui::Button("highest point"))
		menu_frame = analyzer.FindHighestPoint();
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
void r::R_JumpView(bool& isOpen)
{
	analyzer.setPreviewState(isOpen);
	if (!isOpen)
		return;



	ImGui::Begin("Jump View", &isOpen);



	ImGui::SetWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);

	if (!analyzer.RecordingExists())
		ImGui::Text("nothing has been recorded yet!\n");

	else {


		if (ImGui::BeginTabBar("##jumpview_tabs", ImGuiTabBarFlags_None)) {
			if (ImGui::BeginTabItem("Main view")) {
				R_JumpView_Main();
				ImGui::EndTabItem();

			}if (ImGui::BeginTabItem("Preferences")) {
				R_JumpView_Preferences();
				ImGui::EndTabItem();

			}


		}
		ImGui::EndTabBar();

		

	}


	ImGui::End();

}