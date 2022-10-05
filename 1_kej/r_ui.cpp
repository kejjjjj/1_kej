#include "pch.h"

void r::R_MenuStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	style->AntiAliasedLines = true;
	style->AntiAliasedFill = true;

	// Main
	style->WindowPadding.x = 5.0f;
	style->WindowPadding.y = 5.0f;
	style->PopupRounding = 2.0f;
	style->FramePadding.x = 10.0f;
	style->FramePadding.y = 5.0f;
	style->ItemSpacing.x = 10.0f;
	style->ItemSpacing.y = 5.0f;
	style->ItemInnerSpacing.x = 10.0f;
	style->ItemInnerSpacing.y = 4.0f;
	style->TouchExtraPadding.x = 0.0f;
	style->TouchExtraPadding.y = 0.0f;
	style->IndentSpacing = 30.0f;
	style->ScrollbarSize = 14.0f;
	style->GrabMinSize = 10.0f;

	// Borders
	style->WindowBorderSize = 1.0f;
	style->ChildBorderSize = 1.0f;
	style->PopupBorderSize = 1.0f;
	//style->FrameBorderSize = 1.0f;
	style->TabBorderSize = 0.0f;

	// Rounding
	style->WindowRounding = 2.0f;
	style->ChildRounding = 2.0f;
	style->FrameRounding = 2.0f;
	style->ScrollbarRounding = 2.0f;
	style->GrabRounding = 2.0f;
	style->TabRounding = 2.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Tab] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.03f, 0.02f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.3f, 0.3f, 0.80f);

	//style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	//style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	//style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	//style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	//style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	//style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void r::R_RemoveInput(bool _true, bool save_file)
{

	if (!ImGui::GetCurrentContext()) {
		std::cout << "R_RemoveInput(" << _true << "): called without imgui context!\n";
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "R_RemoveInput(): called without imgui context!\n");
		return;
	}

	static const DWORD MouseInput = (cod4x_entry != NULL) ? (cg::cod4x_entry + 0x4480E01) : (DWORD)&s_wmv->mouseInitialized;
	static const DWORD KeyInput = 0x4631B0; //CL_KeyMove
	ImGuiIO& io = ImGui::GetIO();
	hook* a = nullptr;


	if (_true) {

		io.MouseDrawCursor = true;
		io.WantCaptureMouse = true;
		
		a->write_addr(MouseInput, "\x00", 1);
		a->write_addr(KeyInput, "\xC3", 1);
		return;
	}

	io.MouseDrawCursor = false;
	io.WantCaptureMouse = false;
	
	a->write_addr(MouseInput, "\x01", 1);
	a->write_addr(KeyInput, "\x51", 1);

	if(save_file)
		Evar_SaveToFile(v::cfg::cfgDirectory);

}
bool r::R_OpenMenu(IDirect3DDevice9* pDevice)
{

	if (!ImGui::GetCurrentContext()) 
		return false;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	static bool once = true;
	if (once || ResetImFont) {
		fs::Log_Write(LOG_NONE, "setting imFont\n");
		ImFont* font = ImGui::GetFont();
		font->Scale = 1.5f;
		ImGui::SetCurrentFont(font);
		ResetImFont = false;

		once = false;
	}
	if (r::should_draw_menu) {
		
		static bool wantsEditor = false;

		if (!wantsEditor) {
			ImGui::Begin("[ALPHA] 1_kej_v2 - github.com/kejjjjj/", &r::should_draw_menu, ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::SetWindowFontScale(1.2f);

			const ImGuiViewport* viewport = ImGui::GetMainViewport();

			ImGui::SetWindowSize(ImVec2(viewport->Size.x / 3.f, viewport->Size.y / 3.5f), ImGuiCond_FirstUseEver);
			if (r::should_draw_menu)
				R_Features(wantsEditor);

			ImGui::End();
		}
		else {
			//wantsEditor = true;



			R_JumpView(wantsEditor);

			if (!wantsEditor)
				r::should_draw_menu = false;



		}

		if (!r::should_draw_menu || ImGui::GetIO().KeysDownDuration[VK_ESCAPE] >= 0.0 && should_draw_menu) {
			if (clients->snap.ps.pm_type == PM_UFO && analyzer.isPreviewing())
				Cbuf_AddText("ufo\n", 0);

			should_draw_menu = false;
			wantsEditor = false;
			std::cout << "calling R_RemoveInput() from R_OpenMenu()\n";
			R_RemoveInput(r::should_draw_menu);
			analyzer.setPreviewState(false);

			dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

			if (g_gravity) {
				g_gravity->latched.value = 800;
				g_gravity->current.value = 800;
			}
			//CG_SetPlayerAngles(clients->viewangles, r::angles_before_menu);

		}
	}

	return true;
}
void r::R_EndRender()
{
	ImGui::EndFrame();
	ImGui::Render();
	ImDrawData* data = ImGui::GetDrawData();
	ImGui_ImplDX9_RenderDrawData(data);
}