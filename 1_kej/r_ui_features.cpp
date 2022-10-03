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
		if (ImGui::CollapsingHeader("Transfer Zone & FPS")) {

			if (ImGui::Checkbox("Show FPS", &v::mod_showFPS.evar->enabled)) {
				v::mod_showFPS.SetValue(v::mod_showFPS.isEnabled());

			} ImGui::SameLine(); r::MetricsHelpMarker("Draw recommended FPS");

			if (ImGui::Checkbox("horizontal bar", &v::mod_fps_transferz.evar->enabled)) {
				float val = (float)v::mod_fps_transferz.evar->enabled;
				v::mod_fps_transferz.SetValue(&val, 1, 0);
			}ImGui::SameLine(); r::MetricsHelpMarker("draws a bar on the screen that indicates what FPS you should use");

			if (!v::mod_fps_transferz.evar->arrayValue[0])
				ImGui::BeginDisabled();

			ImGui::Text("\t"); ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("y", &v::mod_fps_transferz.evar->arrayValue[1], 1.f, 0.f, 1080.f, "%.0f");

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("height", &v::mod_fps_transferz.evar->arrayValue[2], 1.f, 0.f, 1080.f, "%.0f");

			ImGui::PushItemWidth(100);
			ImGui::DragFloat("fovscale", &v::mod_fps_transferz.evar->arrayValue[3], 0.25f, 0.f, 10.f, "%.2f");
			
			if (ImGui::Checkbox("Long 125", &v::mod_autoFPS_long125.evar->enabled)) {
				v::mod_autoFPS_long125.SetValue(v::mod_autoFPS_long125.isEnabled());
			} ImGui::SameLine(); r::MetricsHelpMarker("Don't let 333fps overwrite most of the 125fps angle");

			ImGui::NewLine();
			ImGui::Text("colors");
			ImGui::Separator();
			static bool 
				t125	= v::mod_125col.evar->vecValue[3], 
				t200	= v::mod_200col.evar->vecValue[3], 
				t250	= v::mod_250col.evar->vecValue[3], 
				t333	= v::mod_333col.evar->vecValue[3], 
				tmarker = v::mod_markercol.evar->vecValue[3];
			

			ImGui::ColorEdit3("125fps", v::mod_125col.evar->vecValue, ImGuiColorEditFlags_NoInputs); 
			ImGui::SameLine(); ImGui::Text("\t "); ImGui::SameLine(); if (ImGui::Button(t125 == true ?	"hide##0" : "show##0")) { t125 = !t125; v::mod_125col.evar->vecValue[3] = (float)t125;}

			ImGui::ColorEdit3("200fps", v::mod_200col.evar->vecValue, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine(); ImGui::Text("\t "); ImGui::SameLine(); if (ImGui::Button(t200 == true ? "hide##01" : "show##01")) { t200 = !t200; v::mod_200col.evar->vecValue[3] = (float)t200; }

			ImGui::ColorEdit3("250fps", v::mod_250col.evar->vecValue, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine(); ImGui::Text("\t "); ImGui::SameLine(); if (ImGui::Button(t250 == true ? "hide##02" : "show##02")) { t250 = !t250; v::mod_250col.evar->vecValue[3] = (float)t250; }

			ImGui::ColorEdit3("333fps", v::mod_333col.evar->vecValue, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine(); ImGui::Text("\t "); ImGui::SameLine(); if (ImGui::Button(t333 == true ? "hide##03" : "show##03")) { t333 = !t333; v::mod_333col.evar->vecValue[3] = (float)t333; }

			ImGui::ColorEdit3("transfer", v::mod_markercol.evar->vecValue, ImGuiColorEditFlags_NoInputs); ImGui::SameLine(); r::MetricsHelpMarker("indicates when your velocity direction starts to shift");
			ImGui::SameLine(); if (ImGui::Button(tmarker == true ? "hide##04" : "show##04")) { tmarker = !tmarker; v::mod_markercol.evar->vecValue[3] = (float)tmarker; }

			ImGui::EndGroup();
			


			if (!v::mod_fps_transferz.evar->arrayValue[0])
				ImGui::EndDisabled();


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

			if (!v::mod_show_worldaxes.isEnabled())
				ImGui::BeginDisabled();

			ImGui::Text("\t"); ImGui::SameLine();

			if (ImGui::Checkbox("Include optimal angle", &v::mod_worldaxes_opt.evar->enabled)) {
				v::mod_worldaxes_opt.SetValue(v::mod_worldaxes_opt.isEnabled());

			}

			if (!v::mod_show_worldaxes.isEnabled())
				ImGui::EndDisabled();


			if (ImGui::Checkbox("Curve Speed", &v::mod_curve_speed.evar->enabled)) {
				v::mod_curve_speed.SetValue(v::mod_curve_speed.isEnabled());

			} ImGui::SameLine(); r::MetricsHelpMarker("draw the difference in angle every 50 snapshots");

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

	if (ImGui::Checkbox("RPG timing", &v::mod_rpg_timing.evar->enabled)) {
		v::mod_rpg_timing.SetValue(v::mod_rpg_timing.isEnabled());
	} ImGui::SameLine(); r::MetricsHelpMarker("prints the rpg timing (calculated in command time)");

	if (ImGui::Checkbox("RPG angle", &v::mod_rpg_angle.evar->enabled)) {
		v::mod_rpg_angle.SetValue(v::mod_rpg_angle.isEnabled());
	} ImGui::SameLine(); r::MetricsHelpMarker("prints the player's pitch angle when they shoot the rpg (and they also bounce)");
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
		} ImGui::SameLine(); r::MetricsHelpMarker("simulates a stable fps for a more consistent experience\nnote: this feature can make a big difference in your codjumping skill\nnote 2: this feature will bug out demos, so don't record demos while this is enabled!");

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

	//if (ImGui::CollapsingHeader("Jump view")) {
	//	static bool isOpen = false;


	//	ImGui::Text("\t");
	//	ImGui::SameLine();
	//	if (ImGui::Button("open editor")) {
	//		isOpen = !isOpen;
	//		dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

	//		if (g_gravity) {
	//			g_gravity->current.value = (isOpen == true) ? 0 : 800;
	//		}
	//	}

	//	r::R_JumpView(isOpen);

	//}


}

void r::R_OtherTab()
{

	ImGui::TextColored(ImVec4(0, 255, 0, 255), "These features aren't necessarily related to cj, but rather tools to analyze the game data");
	ImGui::Separator();
	ImGui::NewLine();

	static bool inMenuView(false);
	

	if (ImGui::Button("Menu Browser"))
		inMenuView = !inMenuView;

	R_GameMenuBrowser(inMenuView);

}
void r::R_Features(bool& wantsEditor)
{
	static ImVec2 childSize = ImVec2(250, ImGui::GetWindowSize().y - 30);

	ImGui::BeginGroup();
	ImGui::BeginChild("child##034", childSize, true, ImGuiWindowFlags_NoScrollbar);

	
	for (size_t i = 0; i < r::imagePairs.size(); i++) {
		ImGui::BeginGroup();
		ImGui::Image((ImTextureID)r::imagePairs[i].second, ImVec2(64, 64));
		ImGui::SameLine();
		ImGui::BeginGroup();
		ImGui::Text("\n");
		ImGui::Text(fs::removeFileExtension(r::imagePairs[i].first.c_str(), 4).c_str());
		ImGui::EndGroup();
		ImGui::Separator();
		ImGui::EndGroup();		

		if (ImGui::IsItemHovered()) {
			ImVec2 rect = ImGui::GetItemRectSize();
			ImGui::GetForegroundDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImVec2(ImGui::GetItemRectMin().x + childSize.x, ImGui::GetItemRectMax().y), IM_COL32(255, 255, 255, 170));
		}

		if (ImGui::IsItemClicked()) {
			Com_Printf(CON_CHANNEL_OBITUARY, "item clicked ^2'%s'\n", imagePairs[i].first.c_str());
		}

	}
	
	ImGui::EndGroup();
	
	

	static ImVec2 rect = ImGui::GetItemRectSize();
	ImGui::EndChild();
	

	ImGui::NewLine();


	childSize.x = rect.x;
	childSize.y = rect.y + 10;


	//ImGui::SetWindowSize(ImVec2(600, childSize.y));



	static bool jumping_tab;
	/*if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None)) {
		if (ImGui::BeginTabItem("Visual")) {
			jumping_tab = false;
			Visual_Features();
			ImGui::EndTabItem();

		}if (ImGui::BeginTabItem("Demo##06")) {
			jumping_tab = false;
			ImGui::ShowDemoWindow();
			ImGui::EndTabItem();

		}if (ImGui::BeginTabItem("RPG")) {
			jumping_tab = false;
			RPG_Features();
			ImGui::EndTabItem();

		}if (ImGui::BeginTabItem("Automation")) {
			jumping_tab = false;
			R_Automation_Features();
			ImGui::EndTabItem();

		}if (ImGui::BeginTabItem("Game")) {
			jumping_tab = false;
			R_OtherTab();
			ImGui::EndTabItem();

		}if (ImGui::BeginTabItem("Jumping")) {


			if (!jumping_tab)
				jumping_tab = true;
			ImGui::EndTabItem();
		}
		ImGui::SameLine();
		if (ImGui::Button("Jump Preview")) {
			analyzer.is_playback = false;
			analyzer.SetFreeMode(false);
			v::mod_jumpv_forcepos.evar->enabled = true;

			if (clients->snap.ps.pm_type != PM_UFO)
				Cbuf_AddText("ufo\n", 0);
			jumping_tab = false;
			dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

			if (g_gravity) {
				g_gravity->current.value = 0;
			}
			wantsEditor = !wantsEditor;
		}
		if(jumping_tab)
			Jump_Features();


	}
	ImGui::EndTabBar();*/
	

}

void r::R_JumpView_Help()
{
	ImGui::NewLine();
	ImGui::Text("Keybinds");
	ImGui::Separator();

	//ImGui::ShowDemoWindow();

	ImGui::BulletText("[SPACEBAR]	 - Toggle free mode");
	ImGui::BulletText("[P]			- Toggle playback");
	ImGui::BulletText("[C]			- Move to current frame");
	ImGui::BulletText("[->]		   - Next Frame");
	ImGui::BulletText("[<-]		   - Previous Frame");
	ImGui::BulletText("[F]		    - Toggle Force Position");
	//ImGui::BulletText("[M]		    - Toggle Menu Drawing");

}