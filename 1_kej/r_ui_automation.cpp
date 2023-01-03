
#include "pch.h"



void r::R_Automation_Features()
{
	ImGui::Text("Strafing\t");
	r::UI_DrawGradientZone(ImVec2(360, 250));

	ImGui::Text("\t");
	ImGui::SameLine();
	ImGui::BeginGroup();


	if (ImGui::Checkbox("strafebot", &v::mod_strafebot.evar->enabled)) {
		v::mod_strafebot.SetValue(v::mod_strafebot.isEnabled());
	} ImGui::SameLine(); r::MetricsHelpMarker("Automatically uses the optimal angle depending on your strafing keys");

	ImGui::Text("\t");
	ImGui::SameLine();

	ImGui::BeginGroup();

	static bool editing_keybind = false;

	if (!v::mod_strafebot.isEnabled() && !editing_keybind)
		ImGui::BeginDisabled();

	if (ImGui::Checkbox("All techniques", &v::mod_strafebot_all.evar->enabled)) {
		v::mod_strafebot_all.SetValue(v::mod_strafebot_all.isEnabled());
	} ImGui::SameLine(); r::MetricsHelpMarker("Strafing is not only limited to holding the WA/WD keys if this feature is enabled" 
		"\nWQ/WE -> W only strafing"
		"\nSQ/SE -> S only strafing");

	if (ImGui::Checkbox("Engine Acceleration", &v::mod_strafebot_accel.evar->enabled)) {
		v::mod_strafebot_accel.SetValue(v::mod_strafebot_accel.isEnabled());
	} ImGui::SameLine(); r::MetricsHelpMarker("Strafebot is disabled whenever velocity < g_speed and not on the ground");

	ImGui::PushItemWidth(75);
	ImGui::DragFloat("Smoothing Scale", &v::mod_strafebot_smooth.evar->floatValue, 0.5f, 1, 45, "%.2f");

	ImGui::PushItemWidth(75);
	ImGui::DragFloat("Bhop Smoothing Scale", &v::mod_strafebot_bhop_s.evar->floatValue, 0.5f, 1, 100, "%.2f");

	if (ImGui::Button("Bind Overwrite")) 
		editing_keybind = !editing_keybind;

	ImGui::SameLine();
	ImGui::Text("key: (%c)", (BYTE)v::mod_strafebot_ow.GetInt());

	if (editing_keybind) {
		ImGui::Begin("Press a key", &editing_keybind, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Text("Press a key to bind...");
		ImGui::NewLine();
		ImGui::Separator();
		if (ButtonCentered("Unbind")) {
			v::mod_strafebot_ow.SetValue((float)0);
			editing_keybind = false;
			Com_Printf(CON_CHANNEL_OBITUARY, "key unbound\n");

		}
		const BYTE key = KeyPressed();

		if (key && !ImGui::IsItemClicked()) {
			v::mod_strafebot_ow.SetValue(key);
			Com_Printf(CON_CHANNEL_OBITUARY, "bound to '^2%c^7'\n", (BYTE)key);
			editing_keybind = false;
		}


		ImGui::End();
	}

	if (!v::mod_strafebot.isEnabled() && !editing_keybind)
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

	ImGui::Text("\nSliding\t");
	r::UI_DrawGradientZone(ImVec2(300, 110));

	ImGui::Text("\t");
	ImGui::SameLine();
	ImGui::BeginGroup();

	const int keyBind = GetKeyBinding("openscriptmenu cj autoslide");

	if (keyBind == 0) {
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "key unbound!");
		ImGui::BeginDisabled();
		v::mod_autoslide.SetValue((float)0);
	}
	static bool methodA = v::mod_autoslide.GetInt() == 1, methodB = v::mod_autoslide.GetInt() == 2;


	if (ImGui::Checkbox("Engine Slide", &methodA)) {
		methodB = !methodA;
		v::mod_autoslide.SetValue((float)1);
	} ImGui::SameLine(); r::MetricsHelpMarker("Game forces a 100ms slide after landing (no fps switching required)");

	if (ImGui::Checkbox("FPS slide", &methodB)) {
		methodA = !methodB;
		v::mod_autoslide.SetValue((float)2);
	} ImGui::SameLine(); r::MetricsHelpMarker("Switches to 15fps when you get close to the ground");

	if (keyBind == 0)
		ImGui::EndDisabled();
	ImGui::EndGroup();

	ImGui::EndGroup();
	
	ImGui::SameLine();
	ImGui::Text("\t\t");
	ImGui::SameLine();

	//right side starts here
	ImGui::BeginGroup(); {

		ImGui::Text("FPS");
		r::UI_DrawGradientZone(ImVec2(330, 180));
		
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
				} ImGui::SameLine(); r::MetricsHelpMarker("Don't let 333fps overwrite most of the 125fps angle\nnote: long 125fps should be disabled for jumps\nwhere you need to do a 125-333 flick in mid-air!"
			"\nit is useful to recognize when you should use\nlong 125 and when you shouldn't");


				if (ImGui::Checkbox("Spacebar 333FPS", &v::mod_autoFPS_space333.evar->enabled)) {
					v::mod_autoFPS_space333.SetValue(v::mod_autoFPS_space333.isEnabled());
				} ImGui::SameLine(); r::MetricsHelpMarker("Holding spacebar sets FPS to 333\nthis can be useful for height bounces and curving while long 125 is enabled");



				if (!v::mod_autoFPS.isEnabled())
					ImGui::EndDisabled();


				ImGui::EndGroup();
			}
		}
		const char* hugfps[4] = { "Disabled", "333", "500", "1000" };
		ImGui::PushItemWidth(120.f);
		if (ImGui::Combo("Bounce FPS", &v::mod_autoFPS_hug500.evar->intValue, hugfps, 4)) {
			v::mod_autoFPS_hug500.SetValue(v::mod_autoFPS_hug500.GetInt());
		} ImGui::SameLine(); r::MetricsHelpMarker("Use this FPS whenever you are touching a bounce");
		ImGui::EndGroup();

		ImGui::NewLine();
		ImGui::Text("500FPS"); ImGui::SameLine(); 
		MetricsHelpMarker("Spawns a bounding box and while you are inside of the bounds, your fps is set to 500");
		r::UI_DrawGradientZone(ImVec2(330, 240));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();
		{
			if (ImGui::Checkbox("Enable spawning", &v::mod_auto500_enabled.evar->enabled)) {
				v::mod_auto500_enabled.SetValue(v::mod_auto500_enabled.isEnabled());

				if (!v::mod_auto500_enabled.isEnabled()) {
					memset(&box500, 0, sizeof(area500_s));
					box500.bounds[0] = 32;
					box500.bounds[1] = 32;
					box500.bounds[2] = 32;
				}

			} ImGui::SameLine(); r::MetricsHelpMarker("Allow 500fps zone spawning");

			if (!v::mod_auto500_enabled.isEnabled())
				ImGui::BeginDisabled();

			if (!box500.boxExists) {
				ImGui::TextColored(ImVec4(255, 255, 0, 255), "Spawn an area with the keybind");
				ImGui::BeginDisabled();
			}
			ImGui::PushItemWidth(100.f);  ImGui::DragFloat("X Bounds##01", &box500.bounds[0], 4.f, 0, 10000, "%.2f");
			ImGui::PushItemWidth(100.f);  ImGui::DragFloat("Y Bounds##01", &box500.bounds[1], 4.f, 0, 10000, "%.2f");
			ImGui::PushItemWidth(100.f);  ImGui::DragFloat("Z Bounds##01", &box500.bounds[2], 4.f, 0, 10000, "%.2f");

			if (ImGui::Button("Delete Area")) {
				memset(&box500, 0, sizeof(area500_s));
				box500.bounds[0] = 32;
				box500.bounds[1] = 32;
				box500.bounds[2] = 32;
			}
			if (!box500.boxExists)
				ImGui::EndDisabled();

			if (!v::mod_auto500_enabled.isEnabled())
				ImGui::EndDisabled();
		}
		ImGui::EndGroup();

		

		//ImGui::TextColored(ImVec4(255, 255, 0, 255), "\nnote: long 125fps should be disabled for jumps\nwhere you need to do a 125-333 flick in mid-air!"
		//	"\nit is useful to recognize when you should use\nlong 125 and when you shouldn't");

		if (v::mod_autoFPS_long125.isEnabled())
			ImGui::TextColored(ImVec4(0, 255, 0, 255), "Long 125 tip: use spacebar 333fps whenever\nyou need to curve earlier in the 125fps zone");
		ImGui::EndGroup();
	}

	//
	//if (ImGui::CollapsingHeader("Other##01")) {
	//	ImGui::TextColored(ImVec4(255, 255, 0, 255), "All other features can be found from Esc/Controls/Multiplayer controls");

	//}
}