#include "pch.h"

void Visual_Features();
void RPG_Features();

void Visual_Features()
{
	if (ImGui::Checkbox("velometer", &v::mod_velometer.evar->enabled))
		v::mod_velometer.SetValue(v::mod_velometer.evar->enabled);
}
void RPG_Features()
{
	static int rpg_mode;
	static const char* items[] = { "default", "switch", "sustain" };
	ImGui::PushItemWidth(150);

	if(ImGui::Combo("Mode", &rpg_mode, items, 3))
		v::mod_rpg_mode.SetValue(items[rpg_mode]);
}
void r::R_Features()
{
	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None)) {
		if (ImGui::BeginTabItem("Visual")) {
			Visual_Features();
			ImGui::EndTabItem();

		}
		if (ImGui::BeginTabItem("RPG")) {
			RPG_Features();
			ImGui::EndTabItem();

		}

	}
	ImGui::EndTabBar();
}