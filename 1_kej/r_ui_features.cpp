#include "pch.h"

void Visual_Features();
void RPG_Features();
void Jump_Features();

void Visual_Features()
{
	//ImGui::Text("Basic");
	//ImGui::Separator();

	if (ImGui::CollapsingHeader("Basic")) {

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
	if (ImGui::CollapsingHeader("World")) {
		//ImGui::Text("Advanced");
		//ImGui::Separator();

		if (ImGui::Checkbox("bounceable surface", &v::mod_bounceable_surf.evar->enabled)) {
			v::mod_bounceable_surf.SetValue(v::mod_bounceable_surf.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("notify if you are looking at a bounce");
		if (ImGui::Checkbox("elevatable surface", &v::mod_elevatable_surf.evar->enabled)) {
			v::mod_elevatable_surf.SetValue(v::mod_elevatable_surf.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("notify if you are looking at an elevatable wall");
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
	//ImGui::Text("Utilities");
	//ImGui::Separator();

	if (ImGui::CollapsingHeader("Utilities")) {

		if (ImGui::Checkbox("hit analyzer", &v::mod_hitanalyzer.evar->enabled)) {
			v::mod_hitanalyzer.SetValue(v::mod_hitanalyzer.evar->enabled);
		} ImGui::SameLine(); r::MetricsHelpMarker("print the difference in velocity before and after bounce");
	}
	//ImGui::Text("Movement");
	//ImGui::Separator();

	if (ImGui::CollapsingHeader("Movement")) {
		if (ImGui::Checkbox("Bunnyhopping", &v::mod_bhop.evar->enabled)) {
			v::mod_bhop.SetValue(v::mod_bhop.evar->enabled);
			cg::Mod_EditMemory(false);

		}

		//////////////////////////////////////////
		if (!v::mod_bhop.isEnabled())
			ImGui::BeginDisabled(true);

		ImGui::Text("\t");
		ImGui::SameLine();
		if (ImGui::Checkbox("No Delay", &v::mod_bhop_nodelay.evar->enabled)) {
			v::mod_bhop_nodelay.SetValue(v::mod_bhop_nodelay.evar->enabled);
			cg::Mod_EditMemory(false);

		}

		if (!v::mod_bhop.isEnabled())
			ImGui::EndDisabled();
	}
	//////////////////////////////////////////


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