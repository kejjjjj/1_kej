
#include "pch.h"



void r::R_Automation_Features()
{
	ImGui::Text("Strafing\t");
	r::UI_DrawGradientZone(ImVec2(300, 100));

	ImGui::Text("\t");
	ImGui::SameLine();
	ImGui::BeginGroup();


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
	ImGui::EndGroup();

	ImGui::Text("\nRPG\t");
	r::UI_DrawGradientZone(ImVec2(300, 60));

	ImGui::Text("\t");
	ImGui::SameLine();
	ImGui::BeginGroup();

	if (ImGui::Checkbox("RPG lookdown", &v::mod_autoanglerpg.evar->enabled)) {
		v::mod_autoanglerpg.SetValue(v::mod_autoanglerpg.isEnabled());
	} ImGui::SameLine(); r::MetricsHelpMarker("Automatically aim down as you fire the rpg");

	ImGui::EndGroup();


	ImGui::EndGroup();
	
	ImGui::SameLine();
	ImGui::Text("\t\t");
	ImGui::SameLine();

	//right side starts here
	ImGui::BeginGroup(); {

		ImGui::Text("FPS");
		r::UI_DrawGradientZone(ImVec2(300, 140));
		
		ImGui::Text("\t");
		ImGui::SameLine();
		ImGui::BeginGroup();
		{

			if (ImGui::Checkbox("autoFPS", &v::mod_autoFPS.evar->enabled)) {
				v::mod_autoFPS.SetValue(v::mod_autoFPS.isEnabled());
			} ImGui::SameLine(); r::MetricsHelpMarker("Automatically change FPS\nNote: Only focuses on speed and not height, so this can be worse for height bounces");

			ImGui::Text("\t");
			ImGui::SameLine();

			ImGui::BeginGroup();
			{
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


				ImGui::EndGroup();
			}
		}
		ImGui::EndGroup();

		ImGui::Text("500FPS");
		r::UI_DrawGradientZone(ImVec2(300, 190));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();
		{
			const char* hugfps[3] = {"Disabled", "500", "1000"};
			ImGui::PushItemWidth(100.f);
			if (ImGui::Combo("Bounce FPS", &v::mod_autoFPS_hug500.evar->intValue, hugfps, 3)) {
				v::mod_autoFPS_hug500.SetValue(v::mod_autoFPS_hug500.GetInt());
			} ImGui::SameLine(); r::MetricsHelpMarker("Use this FPS whenever you are touching a bounce");

			ImGui::PushItemWidth(100.f);  ImGui::DragFloat("X Bounds##01", &box500.bounds[0], 4.f, 0, 10000, "%.2f");
			ImGui::PushItemWidth(100.f);  ImGui::DragFloat("Y Bounds##01", &box500.bounds[1], 4.f, 0, 10000, "%.2f");
			ImGui::PushItemWidth(100.f);  ImGui::DragFloat("Z Bounds##01", &box500.bounds[2], 4.f, 0, 10000, "%.2f");

		}
		ImGui::EndGroup();

		

		ImGui::TextColored(ImVec4(255, 255, 0, 255), "\nnote: long 125fps should be disabled for jumps\nwhere you need to do a 125-333 flick in mid-air!"
			"\nit is useful to recognize when you should use\nlong 125 and when you shouldn't");

		if (v::mod_autoFPS_long125.isEnabled())
			ImGui::TextColored(ImVec4(0, 255, 0, 255), "Long 125 tip: use spacebar 333fps whenever\nyou need to curve earlier in the 125fps zone");
		ImGui::EndGroup();
	}

	//
	//if (ImGui::CollapsingHeader("Other##01")) {
	//	ImGui::TextColored(ImVec4(255, 255, 0, 255), "All other features can be found from Esc/Controls/Multiplayer controls");

	//}
}