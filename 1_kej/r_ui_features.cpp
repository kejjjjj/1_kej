#include "pch.h"

void Visual_Features();
void RPG_Features();
void Jump_Features();
void Visual_Features()
{
	//ImGui::Text("Basic");
	//ImGui::Separator();
	static ImVec2 childSize = ImVec2(250, ImGui::GetWindowSize().y - 30);

	//ImGui::BeginChild("ah#001", childSize);
	ImGui::BeginGroup();

	ImGui::Text("Basic\t"); 
	{
		r::UI_DrawGradientZone(ImVec2(300, 100));

		ImGui::Text("\t"); ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::Checkbox("velometer   \t", &v::mod_velometer.evar->enabled)) {
			float val = (float)v::mod_velometer.evar->enabled;
			v::mod_velometer.SetValue(&val, 1, 0);
		}

		if (v::mod_velometer.evar->arrayValue[0]) {
			ImGui::SameLine();
			static bool editing;

			r::UI_CreateSettings(editing);

			if (editing) {
				ImGui::Begin("Modify velometer", &editing, ImGuiWindowFlags_AlwaysAutoResize);

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("x", &v::mod_velometer.evar->arrayValue[1], 1.f, 0.f, 1920.f, "%.0f");

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("y", &v::mod_velometer.evar->arrayValue[2], 1.f, 0.f, 1080.f, "%.0f");

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("font scale", &v::mod_velometer.evar->arrayValue[3], 0.25f, 0.f, 10.f, "%.2f");

				ImGui::ColorEdit4("glow color", v::mod_velometer_glow.evar->vecValue, ImGuiColorEditFlags_NoInputs);

				ImGui::End();
			}
		}
		


		if (ImGui::Checkbox("coordinates\t", &v::mod_coordinates.evar->enabled)) {
			float val = (float)v::mod_coordinates.evar->enabled;
			v::mod_coordinates.SetValue(&val, 1, 0);

		}if (v::mod_coordinates.evar->arrayValue[0]) {
			ImGui::SameLine();
			static bool editing;

			r::UI_CreateSettings(editing);

			if (editing) {
				ImGui::Begin("Modify Coordinates", &editing, ImGuiWindowFlags_AlwaysAutoResize);

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("x", &v::mod_coordinates.evar->arrayValue[1], 1.f, 0.f, 1920.f, "%.0f");

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("y", &v::mod_coordinates.evar->arrayValue[2], 1.f, 0.f, 1080.f, "%.0f");

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("font scale", &v::mod_coordinates.evar->arrayValue[3], 0.25f, 0.f, 10.f, "%.2f");
				ImGui::End();
			}
		}
		ImGui::EndGroup();
	}
	//ImGui::NewLine();
	ImGui::Text("\nCrosshair\t"); {

	//	ImGui::BeginChild("crosshairchild##02", ImVec2(300, 150));
		r::UI_DrawGradientZone(ImVec2(300, 100));

		ImGui::Text("\t"); ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::ColorEdit3("crosshair color", v::mod_crosshair.evar->vecValue, ImGuiColorEditFlags_NoInputs);
		ImGui::PushItemWidth(70);
		ImGui::SliderFloat("Min Alpha", &v::mod_crosshair.evar->vecValue[3], 0, 1, "%.2f"); ImGui::SameLine();  r::MetricsHelpMarker("Minimum amount of transparency the crosshair can have");
	//	ImGui::EndChild();

		ImGui::EndGroup();

	}
	ImGui::Text("\nWorld\t"); {

		r::UI_DrawGradientZone(ImVec2(300, 100));

		//ImGui::GradientButton(&grad);

		ImGui::Text("\t"); ImGui::SameLine();
		ImGui::BeginGroup();

		if (ImGui::Checkbox("bounceable surface", &v::mod_bounceable_surf.evar->enabled)) {
			v::mod_bounceable_surf.SetValue(v::mod_bounceable_surf.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("notify if you are looking at a bounce");
		if (ImGui::Checkbox("elevatable surface", &v::mod_elevatable_surf.evar->enabled)) {
			v::mod_elevatable_surf.SetValue(v::mod_elevatable_surf.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("notify if you are looking at an elevatable wall");

		ImGui::EndGroup();

	}
	ImGui::Text("\nViewhands\t"); {

		r::UI_DrawGradientZone(ImVec2(300, 150));

		//ImGui::GradientButton(&grad);

		ImGui::Text("\t"); ImGui::SameLine();
		ImGui::BeginGroup();

		if (ImGui::Checkbox("Chams", &v::mod_chams.evar->enabled))
			v::mod_chams.SetValue(v::mod_chams.isEnabled());

		ImGui::SameLine();
		ImGui::ColorEdit3("##aaaa", v::mod_chams_col.evar->vecValue, ImGuiColorEditFlags_NoInputs);

		if (!v::mod_chams.isEnabled())
			ImGui::BeginDisabled();

		if (ImGui::Checkbox("use Z buffer", &v::mod_chams_z.evar->enabled))
			v::mod_chams.SetValue(v::mod_chams_z.isEnabled());

		ImGui::SameLine();
		ImGui::ColorEdit3("##aaaab", v::mod_chams_zcol.evar->vecValue, ImGuiColorEditFlags_NoInputs);

		if (ImGui::Checkbox("Wireframe", &v::mod_chams_wireframe.evar->enabled))
			v::mod_chams_wireframe.SetValue(v::mod_chams_wireframe.isEnabled());

		if (!v::mod_chams.isEnabled())
			ImGui::EndDisabled();

		ImGui::EndGroup();

		ImGui::Text("\n\n");
	}
	ImGui::EndGroup();

	
	//ImGui::EndChild();


	//right side of the menu starts here
	ImGui::SameLine(); ImGui::Text("\t\t"); ImGui::SameLine();
	ImGui::BeginGroup();
	ImGui::Text("Anglehelper");
	{
		r::UI_DrawGradientZone(ImVec2(315, 380));

		//ImGui::Text("\t"); ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Text(" Main\t"); {

			ImGui::Text("\t"); ImGui::SameLine();
			if (ImGui::Checkbox("HUD\t", &v::mod_anglehelper.evar->enabled)) {
				float val = (float)v::mod_anglehelper.evar->enabled;
				v::mod_anglehelper.SetValue(&val, 1, 0);
			}
			if (v::mod_anglehelper.evar->arrayValue[0]) {
				ImGui::SameLine();
				static bool editing;

				r::UI_CreateSettings(editing);


				if (editing) {
					ImGui::Begin("Modify AH HUD", &editing, ImGuiWindowFlags_AlwaysAutoResize);

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
		
		ImGui::Text(" Transfer Zone & FPS\t"); {
			ImGui::Text("\t"); ImGui::SameLine();
			
			ImGui::BeginGroup();
			if (ImGui::Checkbox("Show FPS", &v::mod_showFPS.evar->enabled)) {
				v::mod_showFPS.SetValue(v::mod_showFPS.isEnabled());

			} ImGui::SameLine(); r::MetricsHelpMarker("Draw recommended FPS");

			if (ImGui::Checkbox("horizontal bar", &v::mod_fps_transferz.evar->enabled)) {
				float val = (float)v::mod_fps_transferz.evar->enabled;
				v::mod_fps_transferz.SetValue(&val, 1, 0);
			}ImGui::SameLine(); /*r::MetricsHelpMarker("draws a bar on the screen that indicates what FPS you should use");*/

			static bool editing;

			r::UI_CreateSettings(editing);

			if (editing) {
				ImGui::Begin("Configure FPS UI", &editing, ImGuiWindowFlags_AlwaysAutoResize);

				ImGui::Text("draws a bar on the screen that indicates what FPS you should use");


				ImGui::PushItemWidth(100);
				ImGui::DragFloat("y", &v::mod_fps_transferz.evar->arrayValue[1], 1.f, 0.f, 1080.f, "%.0f");

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("height", &v::mod_fps_transferz.evar->arrayValue[2], 1.f, 0.f, 1080.f, "%.0f");

				ImGui::PushItemWidth(100);
				ImGui::DragFloat("fovscale", &v::mod_fps_transferz.evar->arrayValue[3], 0.25f, 0.f, 10.f, "%.2f");
				
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("width offset", &v::mod_fps_transferz.evar->arrayValue[5], 1.f, 0.f, 1920.f, "%.0f");

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
				ImGui::SameLine(); ImGui::Text("\t  "); ImGui::SameLine(); if (ImGui::Button(t125 == true ?	"hide##0" : "show##0")) { t125 = !t125; v::mod_125col.evar->vecValue[3] = (float)t125;}

				ImGui::ColorEdit3("200fps", v::mod_200col.evar->vecValue, ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine(); ImGui::Text("\t  "); ImGui::SameLine(); if (ImGui::Button(t200 == true ? "hide##01" : "show##01")) { t200 = !t200; v::mod_200col.evar->vecValue[3] = (float)t200; }

				ImGui::ColorEdit3("250fps", v::mod_250col.evar->vecValue, ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine(); ImGui::Text("\t  "); ImGui::SameLine(); if (ImGui::Button(t250 == true ? "hide##02" : "show##02")) { t250 = !t250; v::mod_250col.evar->vecValue[3] = (float)t250; }

				ImGui::ColorEdit3("333fps", v::mod_333col.evar->vecValue, ImGuiColorEditFlags_NoInputs);
				ImGui::SameLine(); ImGui::Text("\t  "); ImGui::SameLine(); if (ImGui::Button(t333 == true ? "hide##03" : "show##03")) { t333 = !t333; v::mod_333col.evar->vecValue[3] = (float)t333; }

				ImGui::ColorEdit3("transfer", v::mod_markercol.evar->vecValue, ImGuiColorEditFlags_NoInputs); ImGui::SameLine(); r::MetricsHelpMarker("indicates when your velocity direction starts to shift");
				ImGui::SameLine(); if (ImGui::Button(tmarker == true ? "hide##04" : "show##04")) { tmarker = !tmarker; v::mod_markercol.evar->vecValue[3] = (float)tmarker; }

				ImGui::NewLine();
				static bool dummy = v::mod_fps_transferz.evar->arrayValue[4] != NULL;
				if (ImGui::Checkbox("Change crosshair color", &dummy)) {
					v::mod_fps_transferz.evar->arrayValue[4] = (float)dummy;
				} ImGui::SameLine(); r::MetricsHelpMarker("Crosshair color changes to green when you should strafe change and changes to red if you go past a transfer zone");

			
				ImGui::End();

			}
			ImGui::EndGroup();

			ImGui::Text(" Miscellaneous\t"); {
				ImGui::Text("\t"); ImGui::SameLine();
				ImGui::BeginGroup();



	

				if (ImGui::Checkbox("Velocity direction", &v::mod_veldirection.evar->enabled)) {
					v::mod_veldirection.SetValue(v::mod_veldirection.isEnabled());

				} ImGui::SameLine(); r::MetricsHelpMarker("Draw a line underneath the player indicating the velocity direction");

				if (ImGui::Checkbox("Show world axes", &v::mod_show_worldaxes.evar->enabled)) {
					v::mod_show_worldaxes.SetValue(v::mod_show_worldaxes.isEnabled());

				} ImGui::SameLine(); r::MetricsHelpMarker("Draw the XY world axes underneath the player to give an understanding of current angles (useful with angled jumps)");

				if (!v::mod_show_worldaxes.isEnabled())
					ImGui::BeginDisabled();

				ImGui::Text("\t"); ImGui::SameLine();

				if (ImGui::Checkbox("Include optimal angle\t", &v::mod_worldaxes_opt.evar->enabled)) {
					v::mod_worldaxes_opt.SetValue(v::mod_worldaxes_opt.isEnabled());

				}

				if (!v::mod_show_worldaxes.isEnabled())
					ImGui::EndDisabled();


				if (ImGui::Checkbox("Curve Speed", &v::mod_curve_speed.evar->enabled)) {
					v::mod_curve_speed.SetValue(v::mod_curve_speed.isEnabled());

				} ImGui::SameLine(); r::MetricsHelpMarker("draw the difference in angle every 50 snapshots");

				ImGui::EndGroup();
			}
			ImGui::EndGroup();

		}
		ImGui::EndGroup();

		
	ImGui::EndGroup();

	//if (ImGui::CollapsingHeader("Crosshair")) {
	//	//ImGui::Text("crosshair color"); ImGui::SameLine();
	//	ImGui::ColorEdit3("crosshair color", v::mod_crosshair.evar->vecValue, ImGuiColorEditFlags_NoInputs);
	//	ImGui::PushItemWidth(70);
	//	ImGui::SliderFloat("Min Alpha", &v::mod_crosshair.evar->vecValue[3], 0, 1, "%.2f"); ImGui::SameLine();  r::MetricsHelpMarker("Minimum amount of transparency the crosshair can have");
	//}
	//if (ImGui::CollapsingHeader("World")) {
	//	//ImGui::Text("Advanced");
	//	//ImGui::Separator();

	//	if (ImGui::Checkbox("bounceable surface", &v::mod_bounceable_surf.evar->enabled)) {
	//		v::mod_bounceable_surf.SetValue(v::mod_bounceable_surf.isEnabled());
	//	} ImGui::SameLine(); r::MetricsHelpMarker("notify if you are looking at a bounce");
	//	if (ImGui::Checkbox("elevatable surface", &v::mod_elevatable_surf.evar->enabled)) {
	//		v::mod_elevatable_surf.SetValue(v::mod_elevatable_surf.isEnabled());
	//	} ImGui::SameLine(); r::MetricsHelpMarker("notify if you are looking at an elevatable wall");
	}
}
void RPG_Features()
{
	static int rpg_mode;
	static const char* items[] = { "default", "switch", "sustain" };

	ImGui::Text(" RPG\t"); 
	r::UI_DrawGradientZone(ImVec2(245, 130));

	ImGui::Text("\t");
	ImGui::SameLine();
	ImGui::BeginGroup();

	ImGui::PushItemWidth(150);

	if(ImGui::Combo("Mode\t", &rpg_mode, items, 3))
		v::mod_rpg_mode.SetValue(items[rpg_mode]);

	if (ImGui::Checkbox("RPG timing", &v::mod_rpg_timing.evar->enabled)) {
		v::mod_rpg_timing.SetValue(v::mod_rpg_timing.isEnabled());
	} ImGui::SameLine(); r::MetricsHelpMarker("prints the rpg timing (calculated in command time)");

	if (ImGui::Checkbox("RPG angle", &v::mod_rpg_angle.evar->enabled)) {
		v::mod_rpg_angle.SetValue(v::mod_rpg_angle.isEnabled());
	} ImGui::SameLine(); r::MetricsHelpMarker("prints the player's pitch angle when they shoot the rpg (and they also bounce)");

	ImGui::EndGroup();

}
void Jump_Features()
{
	//ImGui::Text("Utilities");
	//ImGui::Separator();
	ImGui::BeginGroup();
	ImGui::Text("Utilities\t"); {
		r::UI_DrawGradientZone(ImVec2(295, 100));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();
		if (ImGui::Checkbox("hit analyzer", &v::mod_hitanalyzer.evar->enabled)) {
			v::mod_hitanalyzer.SetValue(v::mod_hitanalyzer.evar->enabled);
		} ImGui::SameLine(); r::MetricsHelpMarker("print the difference in velocity before and after bounce");
		if (ImGui::Checkbox("jump analyzer", &v::mod_jumpanalyzer.evar->enabled)) {
			v::mod_jumpanalyzer.SetValue(v::mod_jumpanalyzer.evar->enabled);
		} ImGui::SameLine(); r::MetricsHelpMarker("print the jump velocity and velocity on bounce hit");
		ImGui::EndGroup();



	}
	ImGui::Text("Bounces\t"); {
		r::UI_DrawGradientZone(ImVec2(295, 100));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (ImGui::Checkbox("Terrain Bouncing", &v::mod_terrain_bounces.evar->enabled)) {
			v::mod_terrain_bounces.SetValue(v::mod_terrain_bounces.evar->enabled);
		} ImGui::SameLine(); r::MetricsHelpMarker("Allows bouncing from terrain edges\nVertical terrain edge support will be added soon... maybe");

		if (ImGui::Checkbox("Unlimited Bouncing", &v::mod_unlim_bounces.evar->enabled)) {
			v::mod_unlim_bounces.SetValue(v::mod_unlim_bounces.evar->enabled);
		} ImGui::SameLine(); r::MetricsHelpMarker("Bounce flags do not reset when you bounce");

		ImGui::EndGroup();

	}

	ImGui::EndGroup();

	ImGui::SameLine(); ImGui::Text("\t\t"); ImGui::SameLine();

	ImGui::BeginGroup();

	ImGui::Text("Movement\t"); 
	{


		r::UI_DrawGradientZone(ImVec2(220, 140));

		ImGui::Text("\t");
		ImGui::SameLine();
		ImGui::BeginGroup();
		if (ImGui::Checkbox("fixed fps", &v::mod_pmove_fixed.evar->enabled)) {
			v::mod_pmove_fixed.SetValue(v::mod_pmove_fixed.isEnabled());
		} ImGui::SameLine(); r::MetricsHelpMarker("simulates a stable fps for a more consistent experience\nnote: this feature can make a big difference in your codjumping skill\nnote 2: this feature will bug out demos, so don't record demos while this is enabled!");

		if (ImGui::Checkbox("Bunnyhopping\t", &v::mod_bhop.evar->enabled)) {
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

		ImGui::EndGroup();
	}
	ImGui::EndGroup();

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

	ImGui::TextColored(ImVec4(0, 255, 0, 255), "These features aren't necessarily related to cj,\nbut rather tools to analyze/modify the game data");
	ImGui::Separator();
	ImGui::NewLine();

	static bool inMenuView(false), inAssMan(false);
	
	ImGui::Text("Game\t");
	r::UI_DrawGradientZone(ImVec2(225, 120));

	ImGui::Text("\t");
	ImGui::SameLine();
	ImGui::BeginGroup();

	if (ImGui::Button("Menu Browser"))
		inMenuView = !inMenuView;
	if (ImGui::Button("Asset Manager"))
		inAssMan = !inAssMan;
	ImGui::EndGroup();

	R_GameMenuBrowser(inMenuView);
	R_AssMan_Main(inAssMan);

}
void r::R_DrawMenuByName(const char* category, bool justPressed, bool& wantsEditor)
{
	ImGui::SameLine();
	ImGui::BeginGroup();
	if (!strcmp("Automation", category)) {
		R_Automation_Features();
		
	}
	else if (!strcmp("Game", category)) {
		R_OtherTab();
	}
	else if (!strcmp("Jump Builder", category)) {
		r::R_MenuStyle(0.5f);
		R_JumpBuilder_Main();
	}
	else if (!strcmp("Jump Preview", category)) {
		if (justPressed) {
			analyzer.is_playback = false;
			analyzer.SetFreeMode(false);
			v::mod_jumpv_forcepos.evar->enabled = true;

			if (clients->snap.ps.pm_type != PM_UFO)
				Cbuf_AddText("ufo\n", 0);
			dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

			if (g_gravity) {
				g_gravity->current.value = 0;
			}
			wantsEditor = !wantsEditor;
		}
		
	}
	else if (!strcmp("Jumping", category)) {
		Jump_Features();
	}
	else if (!strcmp("Rpg", category)) {
		RPG_Features();
	}
	else if (!strcmp("Visuals", category)) {
		Visual_Features();
	}
	else {
		if (justPressed)
			Com_PrintError(CON_CHANNEL_OBITUARY, "Unrecognized category '%s'\n", category);
	}
	ImGui::EndGroup();
}
void r::R_Features(bool& wantsEditor)
{
	static ImVec2 childSize = ImVec2(250, ImGui::GetWindowSize().y - 30);

	ImGui::BeginGroup();
	ImGui::BeginChild("child##034", childSize, true, ImGuiWindowFlags_NoScrollbar);

	static int ActiveIndex(0);
	
	bool justPressed(false);

	size_t indx(0);

	for (const auto& i : r::imagePairs) {

		if (i.first.find("_no_load") != std::string::npos) {
			++indx;
			continue;
		}

		ImGui::BeginGroup();
		ImGui::Image((ImTextureID)i.second, ImVec2(64, 64));
		ImGui::SameLine();
		ImGui::BeginGroup();
		ImGui::Text("\n");
		ImGui::Text(fs::removeFileExtension(i.first.c_str(), 4).c_str());
		ImGui::EndGroup();
		ImGui::Separator();
		ImGui::EndGroup();		

		if (ImGui::IsItemHovered()) {
			ImVec2 rect = ImGui::GetItemRectSize();
			ImGui::GetForegroundDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImVec2(ImGui::GetItemRectMin().x + childSize.x - 10, ImGui::GetItemRectMax().y), IM_COL32(255, 255, 255, 170));
		}

		if (ImGui::IsItemClicked()) {
			justPressed = true;

			ActiveIndex = indx;

		}
		++indx;

	}
	
	ImGui::EndGroup();

	static ImVec2 rect = ImGui::GetItemRectSize();
	ImGui::EndChild();
	
	ImGui::SameLine();

	ImGradient grad;
	//grad.addMark(0, ImColor(0.10f, 0.09f, 0.12f, 1.00f));
	grad.addMark(0.f, ImColor(255, 175, 0, 255/2));
	grad.addMark(0.5f, ImColor(0.06f, 0.05f, 0.07f, 0.f));
	grad.addMark(1.f, ImColor(0.06f, 0.05f, 0.07f, 0.f));

	const ImVec2 sp = ImGui::GetCursorScreenPos();


	ImGui::DrawGradientBar(&grad, ImVec2(sp.x-10, sp.y), 20, childSize.y);
	ImGui::SameLine();  ImGui::Text(" ");
	ImGui::SameLine();

	std::string category = fs::removeFileExtension(r::imagePairs[ActiveIndex].first, 4);

	R_DrawMenuByName(category.c_str(), justPressed, wantsEditor);

	if (r::imagePairs[ActiveIndex].first.find("Preview") != std::string::npos)
		ActiveIndex = UI_GetImageIndex("Automation");


	const bool isMenu = !category.compare("Jump Builder");
	if (jbuilder.isEditing() && !isMenu)
		jbuilder.SetEditMode(false);

	else if (!jbuilder.isEditing() && isMenu)
		jbuilder.SetEditMode(true);

	childSize.x = rect.x + 10;
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