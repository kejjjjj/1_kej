#include "pch.h"

bool r::R_Init()
{
	if (!cg::dx->device)
		return false;

	PVOID* vTable = *reinterpret_cast<PVOID**>(cg::dx->device);

	hook a;

	pEndScene = (endScene)vTable[42];
	
	if (a.install(&(PVOID&)pEndScene, draw_func) != S_OK) {
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "failed to hook endscene\n");
		return false;
	}
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "renderer successfully hooked\n");

	return true;
}
bool r::R_ImGui(IDirect3DDevice9* pDevice)
{
	if (ImGui::GetCurrentContext())
		return true;

	std::cout << "creating new imgui context!\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "creating new imgui context!\n");


	ImGui::CreateContext();

	const char* window_name = (cod4x_entry != NULL) ? "Call Of Duty 4 X" : "Call Of Duty 4";

	if (!ImGui_ImplWin32_Init(FindWindowA(NULL, window_name))) {
		fs::Log_Write(LOG_FATAL, "ImGui_ImplWin32_Init(%s) return false\n", window_name);
		return false;
	}

	if (!ImGui_ImplDX9_Init(pDevice)) {
		fs::Log_Write(LOG_FATAL, "ImGui_ImplDX9_Init() return false.. possibly null directx device\n");
		return false;
	}
	
	return true;
}
LRESULT CALLBACK r::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {


	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return 1l;
	}

	switch (uMsg) {
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		r::should_draw_menu = false;
		std::cout << "calling R_RemoveInput() from WndProc() -> WM_Destroy\n";
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "destroying game window\n");
		R_RemoveInput(r::should_draw_menu);
	}

	if (r::should_draw_menu && !analyzer.InFreeMode() && VID_ACTIVE) { //possible cause for a freeze when imgui menu is open (wndproc might not get called ever)
		cg::move->forward = false;
		cg::move->back = false;
		cg::move->jump = false;
		cg::move->right = false;
		cg::move->left = false;
		cg::move->leanright = false;
		cg::move->leanleft = false;
		return 1;
	}

	return oWndProc(hWnd, uMsg, wParam, lParam);
}
void* r::CL_ShutdownRenderer()
{
	r::should_draw_menu = false;
	CL_ShutdownRenderer_f();
	std::cout << "shutdown renderer!\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "shutting down renderer\n");
	if (ImGui::GetCurrentContext()) {
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

	}
	return 0;
}
char r::R_RecoverLostDevice()
{
	if (!r::device_needs_reset) {
		if (analyzer.isPreviewing()) {
			analyzer.setPreviewState(false);

			dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

			if (g_gravity) {
				g_gravity->latched.value = 800;
				g_gravity->current.value = 800;
			}

		}
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "R_RecoverLostDevice(): restoring input\n");
		r::device_needs_reset = true;
		r::should_draw_menu = false;
		r::R_RemoveInput(false);
		ImGui_ImplDX9_InvalidateDeviceObjects();
		std::cout << "R_RecoverLostDevice(): restoring input\n";
	}
	//if (ImGui::GetCurrentContext()) {
	//	ImGui_ImplDX9_InvalidateDeviceObjects();
	//	r::should_draw_menu = false;
	//	//std::cout << "calling R_RemoveInput() from R_RecoverLostDevice()\n";
	//	//R_RemoveInput(r::should_draw_menu);

	//}

	return R_RecoverLostDevice_f();
}