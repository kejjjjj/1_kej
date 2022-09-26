
#include "pch.h"



void r::R_Automation_Features()
{
	if (ImGui::CollapsingHeader("Strafing")) {
		if (ImGui::Checkbox("strafebot", &v::mod_strafebot.evar->enabled)) {
			v::mod_strafebot.SetValue(v::mod_strafebot.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("Automatically uses the optimal angle depending on your strafing keys");

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (!v::mod_strafebot.isEnabled())
			ImGui::BeginDisabled();

		if (ImGui::Checkbox("All techniques", &v::mod_strafebot_all.evar->enabled)) {
			v::mod_strafebot_all.SetValue(v::mod_strafebot_all.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("Strafing is not only limited to holding the WA/WD keys if this feature is enabled" 
			"\nWQ/WE -> W only strafing"
			"\nSQ/SE -> S only strafing");

		if (!v::mod_strafebot.isEnabled())
			ImGui::EndDisabled();

		ImGui::EndGroup();
	}
	if (ImGui::CollapsingHeader("FPS")) {

		if (ImGui::Checkbox("autoFPS", &v::mod_autoFPS.evar->enabled)) {
			v::mod_autoFPS.SetValue(v::mod_autoFPS.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("Automatically change FPS\nNote: Only focuses on speed and not height, so this can be worse for height bounces");

		ImGui::Text("\t"); 
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (!v::mod_autoFPS.isEnabled())
			ImGui::BeginDisabled();


		if (ImGui::Checkbox("Long 125##01", &v::mod_autoFPS_long125.evar->enabled)) {
			v::mod_autoFPS_long125.SetValue(v::mod_autoFPS_long125.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("Don't let 333fps overwrite most of the 125fps angle");


		if (ImGui::Checkbox("Spacebar 333FPS", &v::mod_autoFPS_space333.evar->enabled)) {
			v::mod_autoFPS_space333.SetValue(v::mod_autoFPS_space333.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("Holding spacebar sets FPS to 333\nthis can be useful for height bounces and curving while long 125 is enabled");

		if (!v::mod_autoFPS.isEnabled())
			ImGui::EndDisabled();

		if (v::mod_autoFPS_long125.isEnabled())
			ImGui::TextColored(ImVec4(0, 255, 0, 255), "Long 125 tip: use spacebar 333fps whenever you need to curve earlier in the 125fps zone");

		ImGui::EndGroup();
	}
	if (ImGui::CollapsingHeader("RPG##02")) {
		if (ImGui::Checkbox("RPG lookdown", &v::mod_autoanglerpg.evar->enabled)) {
			v::mod_autoanglerpg.SetValue(v::mod_autoanglerpg.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("Automatically aim down as you fire the rpg");
	}
}