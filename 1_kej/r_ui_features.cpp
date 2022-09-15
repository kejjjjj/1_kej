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
	if (ImGui::CollapsingHeader("Anglehelper")) {

		ImGui::Text("\t"); ImGui::SameLine();
		ImGui::BeginGroup();

		if (ImGui::CollapsingHeader("Main")) {
			if (ImGui::Checkbox("enable HUD", &v::mod_anglehelper.evar->enabled)) {
				float val = (float)v::mod_anglehelper.evar->enabled;
				v::mod_anglehelper.SetValue(&val, 1, 0);
			}
			if (v::mod_anglehelper.evar->arrayValue[0]) {
				ImGui::SameLine();
				static bool editing;
				if (ImGui::Button("modify##04"))
					editing = !editing;


				if (editing) {
					ImGui::Begin("Modify AH HUD", &editing);

					const ImGuiViewport* viewport = ImGui::GetMainViewport();

					ImGui::SetWindowSize(ImVec2(viewport->Size.x / 3.f, viewport->Size.y / 3.5f), ImGuiCond_FirstUseEver);

					ImGui::PushItemWidth(100);
					ImGui::DragFloat("y", &v::mod_anglehelper.evar->arrayValue[1], 1.f, 0.f, 1080.f, "%.0f");

					ImGui::PushItemWidth(100);
					ImGui::DragFloat("height", &v::mod_anglehelper.evar->arrayValue[2], 1.f, 0.f, 1080.f, "%.0f");

					ImGui::PushItemWidth(100);
					ImGui::DragFloat("fovscale", &v::mod_anglehelper.evar->arrayValue[3], 0.25f, 0.f, 10.f, "%.2f");
					ImGui::End();
				}
			}
		}

		ImGui::EndGroup();

		ImGui::Text("\t"); ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::CollapsingHeader("Transfer Zone")) {
			if (ImGui::Checkbox("horizontal bar", &v::mod_fps_transferz.evar->enabled)) {
				float val = (float)v::mod_fps_transferz.evar->enabled;
				v::mod_fps_transferz.SetValue(&val, 1, 0);
			}

			if(v::mod_fps_transferz.evar->arrayValue[0]){
				ImGui::SameLine();
				static bool editing;
				if (ImGui::Button("modify##03"))
					editing = !editing;


				if (editing) {
					ImGui::Begin("Modify Transfer Zone UI", &editing);

					const ImGuiViewport* viewport = ImGui::GetMainViewport();

					ImGui::SetWindowSize(ImVec2(viewport->Size.x / 3.f, viewport->Size.y / 3.5f), ImGuiCond_FirstUseEver);

					ImGui::PushItemWidth(100);
					ImGui::DragFloat("y", &v::mod_fps_transferz.evar->arrayValue[1], 1.f, 0.f, 1080.f, "%.0f");

					ImGui::PushItemWidth(100);
					ImGui::DragFloat("height", &v::mod_fps_transferz.evar->arrayValue[2], 1.f, 0.f, 1080.f, "%.0f");

					ImGui::PushItemWidth(100);
					ImGui::DragFloat("fovscale", &v::mod_fps_transferz.evar->arrayValue[3], 0.25f, 0.f, 10.f, "%.2f");
					ImGui::End();
				}
			}
			static bool dummy = v::mod_fps_transferz.evar->arrayValue[4] != NULL;
			if (ImGui::Checkbox("Change crosshair color", &dummy)) {
				v::mod_fps_transferz.evar->arrayValue[4] = (float)dummy;
			} ImGui::SameLine(); r::MetricsHelpMarker("Crosshair color changes to green when you should strafe change and changes to red if you go past a transfer zone");
		}
		ImGui::EndGroup();
		ImGui::Text("\t"); ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::CollapsingHeader("Miscellaneous")) {
			if (ImGui::Checkbox("Velocity direction", &v::mod_veldirection.evar->enabled)) {
				v::mod_veldirection.SetValue(v::mod_veldirection.isEnabled());

			} ImGui::SameLine(); r::MetricsHelpMarker("Draw a line underneath the player indicating the velocity direction");

			if (ImGui::Checkbox("Show world axes", &v::mod_show_worldaxes.evar->enabled)) {
				v::mod_show_worldaxes.SetValue(v::mod_show_worldaxes.isEnabled());

			} ImGui::SameLine(); r::MetricsHelpMarker("Draw the XY world axes underneath the player to give an understanding of current angles (useful with angled jumps)");
		}	
		ImGui::EndGroup();
	}
	if (ImGui::CollapsingHeader("Crosshair")) {
		//ImGui::Text("crosshair color"); ImGui::SameLine();
		ImGui::ColorEdit3("crosshair color", v::mod_crosshair.evar->vecValue, ImGuiColorEditFlags_NoInputs);
		ImGui::PushItemWidth(70);
		ImGui::SliderFloat("Min Alpha", &v::mod_crosshair.evar->vecValue[3], 0, 1, "%.2f"); ImGui::SameLine();  r::MetricsHelpMarker("Minimum amount of transparency the crosshair can have");
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
		if (ImGui::Checkbox("jump analyzer", &v::mod_jumpanalyzer.evar->enabled)) {
			v::mod_jumpanalyzer.SetValue(v::mod_jumpanalyzer.evar->enabled);
		} ImGui::SameLine(); r::MetricsHelpMarker("print the jump velocity and velocity on bounce hit");
	}
	//ImGui::Text("Movement");
	//ImGui::Separator();

	if (ImGui::CollapsingHeader("Movement")) {

		if (ImGui::Checkbox("fixed fps", &v::mod_pmove_fixed.evar->enabled)) {
			v::mod_pmove_fixed.SetValue(v::mod_pmove_fixed.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("simulates a stable fps for a more consistent experience\nnote: this feature can make a big difference in your codjumping skill");

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