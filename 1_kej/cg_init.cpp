
#include "pch.h"

void cg::cod4x()
{
	if (!(DWORD)GetModuleHandleA("cod4x_021.dll")) {
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "cod4x not 21.1 detected\n");
		r::WndProcAddr = 0x57BB20;
		return;
	}
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "cod4x 21.1 detected\n");

	hook* a = nullptr;

	a->write_addr(0x452C8E, "\xE8\x5D\xCB\xFD\xFF", 5); //redirect cod4x CG_DrawActive call back to iw3mp
	a->write_addr(0x56BFF0, "\x51\x53\x8B\x5C\x24", 5); //redirect cod4x Dvar_Reregister hook back to iw3mp
	a->write_addr(0x56B1B0, "\x55\x8B\xEC\x83\xE4", 5); //redirect cod4x Dvar_SetVariant hook back to iw3mp

	r::WndProcAddr = (DWORD)a->find_pattern("cod4x_021.dll", "55 89 E5 53 81 EC 84 00 00 00 C7 04 24 02");
	BG_WeaponNames = reinterpret_cast<WeaponDef**>(cod4x_entry + 0x443DDE0); 
	cmd_functions = reinterpret_cast<cmd_function_s*>(cod4x_entry + 0x227A28);
	Cmd_AddCommand_fnc = (void*)(cod4x_entry + 0x2116C);

}
void cg::CG_Init()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "CG_Init() loading..\n");

	cod4x();
	CG_InitForeverHooks();
	Scr_Init();
	Evar_Setup();
	Evar_LoadFromFile(v::cfg::cfgDirectory);

	hook* a = nullptr;

	stub = (void(*)())(0x54DE59);

	a->install(&(PVOID&)stub, Script_ScriptMenuResponse);

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "^21_kej extension has been loaded!\n");

}
void cg::CG_PrepareHooks()
{
	r::CG_DrawActive_f			= (void(__cdecl*)())								(0x42F7F0); //r_init.cpp
	r::CL_ShutdownRenderer_f	= (void*(__stdcall*)())								(0x46CA40);
	r::R_RecoverLostDevice_f	= (char(__stdcall*)())								(0x5F5360);
	r::oWndProc					= (LRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM))	(r::WndProcAddr);
	PM_AirMove_f				= (void(__cdecl*)(pmove_t*, pml_t*))				(0x40F680);
	Pmove_f						= (void(*)(pmove_t * pmove))						(0x414D10);
}
void cg::CG_InitForeverHooks()
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to load perma hooks\n");

	CG_PrepareHooks();
	CL_Disconnect_f				= (void(*)(int))				(0x4696B0);
	SV_Map_f					= (void(*)())					(0x527670);

	hook* a = nullptr;


	a->install(&(PVOID&)CL_Disconnect_f, CL_Disconnect);
	a->install(&(PVOID&)SV_Map_f, SV_Map);
}
void cg::CG_InitHooks()
{
	std::cout << "calling cg::CG_InitHooks()\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to load hooks... ");
	if (mglobs.initialized)
		return;

	CG_PrepareHooks();

	hook* a = nullptr;

	if (!r::oWndProc) {
		fs::Log_Write(LOG_FATAL, "failed to hook WndProc because it was NULL\n");
		return;
	}

	a->install(&(PVOID&)r::CL_ShutdownRenderer_f, r::CL_ShutdownRenderer);
	a->install(&(PVOID&)r::R_RecoverLostDevice_f, r::R_RecoverLostDevice);
	a->install(&(PVOID&)r::oWndProc, r::WndProc);
	a->install(&(PVOID&)PM_AirMove_f, PM_AirMove);
	a->install(&(PVOID&)r::CG_DrawActive_f, r::CG_DrawActive); 
	a->install(&(PVOID&)Pmove_f, Pmove);

	Com_Printf(CON_CHANNEL_CONSOLEONLY, " done!\n");


	mglobs.initialized = true;
}
void cg::CG_RemoveHooks()
{
	std::cout << "calling cg::CG_RemoveHooks()\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "preparing to remove hooks...");

	if (!mglobs.initialized)
		return;

	hook* a = nullptr;

	r::R_RemoveInput(false);

	a->remove(&(PVOID&)r::CL_ShutdownRenderer_f, r::CL_ShutdownRenderer);
	a->remove(&(PVOID&)r::R_RecoverLostDevice_f, r::R_RecoverLostDevice);
	a->remove(&(PVOID&)r::oWndProc, r::WndProc);
	a->remove(&(PVOID&)PM_AirMove_f, PM_AirMove);
	a->remove(&(PVOID&)r::CG_DrawActive_f, r::CG_DrawActive);
	a->remove(&(PVOID&)Pmove_f, Pmove);

	if (r::pEndScene) {
		a->remove(&(PVOID&)r::pEndScene, r::draw_func);

	}
	Com_Printf(CON_CHANNEL_CONSOLEONLY, " done!\n");

	if (ImGui::GetCurrentContext()) {
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "also removing imgui context\n");

		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

	}

	mglobs.initialized = false;

}