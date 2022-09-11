#include "pch.h"

void Visual_Features();
void RPG_Features();
void Jump_Features();

void Visual_Features()
{
	if (ImGui::Checkbox("velometer", &v::mod_velometer.evar->enabled)) {
		float val = (float)v::mod_velometer.evar->enabled;
		v::mod_velometer.SetValue(&val, 1, 0);
	}

	if (v::mod_velometer.evar->arrayValue[0]) {
		ImGui::SameLine();
		static bool editing;
		if (ImGui::Button("modify##01"))
			editing = !editing;


		if (editing) {
			ImGui::Begin("Modify velometer", &editing);

			const ImGuiViewport* viewport = ImGui::GetMainViewport();

			ImGui::SetWindowSize(ImVec2(viewport->Size.x / 3.f, viewport->Size.y / 3.5f), ImGuiCond_FirstUseEver);

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("x", &v::mod_velometer.evar->arrayValue[1], 1.f, 0.f, 1920.f, "%.0f");

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("y", &v::mod_velometer.evar->arrayValue[2], 1.f, 0.f, 1080.f, "%.0f");

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("font scale", &v::mod_velometer.evar->arrayValue[3], 0.25f, 0.f, 10.f, "%.2f");
			ImGui::End();
		}
	}


	if (ImGui::Checkbox("coordinates", &v::mod_coordinates.evar->enabled)) {
		float val = (float)v::mod_coordinates.evar->enabled;
		v::mod_coordinates.SetValue(&val, 1, 0);

	}if (v::mod_coordinates.evar->arrayValue[0]) {
		ImGui::SameLine();
		static bool editing;
		if (ImGui::Button("modify##02"))
			editing = !editing;


		if (editing) {
			ImGui::Begin("Modify Coordinates", &editing);

			const ImGuiViewport* viewport = ImGui::GetMainViewport();

			ImGui::SetWindowSize(ImVec2(viewport->Size.x / 3.f, viewport->Size.y / 3.5f), ImGuiCond_FirstUseEver);

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("x", &v::mod_coordinates.evar->arrayValue[1], 1.f, 0.f, 1920.f, "%.0f");

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("y", &v::mod_coordinates.evar->arrayValue[2], 1.f, 0.f, 1080.f, "%.0f");

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("font scale", &v::mod_coordinates.evar->arrayValue[3], 0.25f, 0.f, 10.f, "%.2f");
			ImGui::End();
		}
	}

}
void RPG_Features()
{
	static int rpg_mode;
	static const char* items[] = { "default", "switch", "sustain" };
	ImGui::PushItemWidth(150);

	if(ImGui::Combo("Mode", &rpg_mode, items, 3))
		v::mod_rpg_mode.SetValue(items[rpg_mode]);
}
void Jump_Features()
{
	if (ImGui::Checkbox("hit analyzer", &v::mod_hitanalyzer.evar->enabled)) {
		v::mod_hitanalyzer.SetValue(v::mod_hitanalyzer.evar->enabled);
	} ImGui::SameLine(); r::MetricsHelpMarker("print the difference in velocity before and after bounce");



}
void r::R_Features()
{
	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None)) {
		if (ImGui::BeginTabItem("Visual")) {
			Visual_Features();
			ImGui::EndTabItem();

		}if (ImGui::BeginTabItem("RPG")) {
			RPG_Features();
			ImGui::EndTabItem();

		}if (ImGui::BeginTabItem("Jumping")) {
			Jump_Features();
			ImGui::EndTabItem();
		}


	}
	ImGui::EndTabBar();
}