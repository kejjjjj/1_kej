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
	style->FrameBorderSize = 1.0f;
	style->TabBorderSize = 0.0f;

	// Rounding
	style->WindowRounding = 2.0f;
	style->ChildRounding = 2.0f;
	style->FrameRounding = 2.0f;
	style->ScrollbarRounding = 2.0f;
	style->GrabRounding = 2.0f;
	style->TabRounding = 2.0f;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.84f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 0.64f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.90f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 0.99f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.93f);
	colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 0.55f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.56f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 0.60f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 1.00f, 0.98f, 0.20f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.66f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.11f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.24f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.99f, 1.00f, 1.00f, 0.24f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.55f, 0.39f, 0.69f);
	colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.55f, 0.39f, 0.69f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.55f, 0.39f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.24f, 0.24f, 0.24f, 0.55f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.39f, 0.39f, 0.39f, 0.73f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.55f, 0.55f, 0.55f, 0.74f);
	colors[ImGuiCol_Header] = ImVec4(0.34f, 0.34f, 0.34f, 0.21f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.36f);
	colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 0.09f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.09f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.16f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.39f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.39f);
	colors[ImGuiCol_Tab] = ImVec4(0.27f, 0.27f, 0.27f, 0.54f);
	colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 0.53f, 0.36f, 0.48f);
	colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.55f, 0.39f, 0.69f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.80f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(1.00f, 0.66f, 0.53f, 0.61f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.70f, 0.62f, 0.30f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.27f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.34f);
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

	if (r::should_draw_menu) {
		R_MenuStyle();

		static bool wantsEditor = false;

		if (!wantsEditor) {
			ImGui::Begin("1_kej_v2 - github.com/kejjjjj/", &r::should_draw_menu);

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

		if (!r::should_draw_menu) {
			std::cout << "calling R_RemoveInput() from R_OpenMenu()\n";
			R_RemoveInput(r::should_draw_menu);
			analyzer.setPreviewState(false);

			dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

			if (g_gravity) {
				g_gravity->latched.value = 800;
				g_gravity->current.value = 800;
			}
			CG_SetPlayerAngles(clients->viewangles, r::angles_before_menu);

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