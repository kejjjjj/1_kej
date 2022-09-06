#include "pch.h"

bool r::R_Init()
{
	if (!cg::dx->device)
		return false;

	PVOID* vTable = *reinterpret_cast<PVOID**>(cg::dx->device);

	hook a;


	pEndScene = (endScene)vTable[42];
	
	if (a.install(&(PVOID&)pEndScene, draw_func) != S_OK || a.install(&(PVOID&)CG_DrawActive_f, CG_DrawActive) != S_OK) {
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "failed to hook endscene or cg_Drawactive\n");
		return false;
	}



	return true;
}
bool r::R_ImGui(IDirect3DDevice9* pDevice)
{
	static bool once = true;

	if (!once)
		return true;

	once = false;

	hook a;

	ImGui::CreateContext();

	const char* window_name = (cod4x_entry != NULL) ? "Call Of Duty 4 X" : "Call Of Duty 4";

	if (!ImGui_ImplWin32_Init(FindWindowA(NULL, window_name)))
		return false;

	if (!ImGui_ImplDX9_Init(pDevice)) {
		return false;
	}


	r::oWndProc = (WNDPROC)(r::WndProcAddr);
	a.install(&(PVOID&)r::oWndProc, WndProc);

	return true;
}