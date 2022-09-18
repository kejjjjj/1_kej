
#include "pch.h"

void cg::cod4x()
{
	if (!(DWORD)GetModuleHandleA("cod4x_021.dll")) {
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "cod4x not 21.1 detected\n");
		r::WndProcAddr = 0x57BB20;
		r::CG_DrawActive_fnc = 0x42F7F0;
		return;
	}
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "cod4x 21.1 detected\n");

	hook* a = nullptr;

	//a->write_addr(0x452C8E, "\xE8\x5D\xCB\xFD\xFF", 5); //redirect cod4x CG_DrawActive call back to iw3mp
	//a->write_addr(0x56BFF0, "\x51\x53\x8B\x5C\x24", 5); //redirect cod4x Dvar_Reregister hook back to iw3mp
	//a->write_addr(0x56B1B0, "\x55\x8B\xEC\x83\xE4", 5); //redirect cod4x Dvar_SetVariant hook back to iw3mp

	r::WndProcAddr = (DWORD)a->find_pattern("cod4x_021.dll", "55 89 E5 53 81 EC 84 00 00 00 C7 04 24 02");
	BG_WeaponNames = reinterpret_cast<WeaponDef**>(cod4x_entry + 0x443DDE0); 
	cmd_functions = reinterpret_cast<cmd_function_s*>(cod4x_entry + 0x227A28);
	Cmd_AddCommand_fnc = (void*)(cod4x_entry + 0x2116C);
	r::CG_DrawActive_fnc = (DWORD)a->find_pattern("cod4x_021.dll", "55 89 E5 83 EC 18 B8 38 E3 74 00 D9 80 9C F3 04 00 D9 5D F4");

	if (!r::WndProcAddr || !r::CG_DrawActive_fnc) {
		fs::Log_Write(LOG_FATAL, "Failed to find necessary cod4x 21.1 addresses! Notify the developer about this!\n");
		return;
	}

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

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "^21_kej extension has been loaded!\n");

}
void cg::CG_PrepareHooks()
{
	stub							= (void(*)())										(0x54DE59); //scriptmenusresponse
	stub2							= (void(*)())										(0x46D4CF); //openscriptmenu
	r::CG_DrawActive_f				= (void(__cdecl*)())								(r::CG_DrawActive_fnc); //r_init.cpp
	r::CL_ShutdownRenderer_f		= (void*(__stdcall*)())								(0x46CA40);
	r::R_RecoverLostDevice_f		= (char(__stdcall*)())								(0x5F5360);
	r::oWndProc						= (LRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM))	(r::WndProcAddr);
	PM_AirMove_f					= (void(__cdecl*)(pmove_t*, pml_t*))				(0x40F680);
	PM_Weapon_f						= (void(__cdecl*)(pml_t*, pmove_t*))				(0x41A470);
	Pmove_f							= (void(*)(pmove_t * pmove))						(0x414D10);
	CG_CalcCrosshairColor_f			= (char(*)())										(0x430A33);
	PM_Weapon_WeaponTimeAdjust_f	= (void(*)())										(0x41A4D8);
	PmoveSingle_stub_f				= (void(*)())										(0x414BB4);
	PM_SlideMove_f					= (BOOL(*)(pmove_t*, pml_t*, int))					(0x414F40);
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
	a->install(&(PVOID&)PM_Weapon_f, PM_Weapon);
	a->install(&(PVOID&)r::CG_DrawActive_f, r::CG_DrawActive); 
	a->install(&(PVOID&)Pmove_f, Pmove);
	a->install(&(PVOID&)stub, Script_ScriptMenuResponse);
	a->install(&(PVOID&)stub2, Script_OpenScriptMenu);
	a->install(&(PVOID&)CG_CalcCrosshairColor_f, CG_CalcCrosshairColor);
	a->install(&(PVOID&)PM_Weapon_WeaponTimeAdjust_f, PM_Weapon_WeaponTimeAdjust);
	a->install(&(PVOID&)PmoveSingle_stub_f, PmoveSingle_stub);
	a->install(&(PVOID&)PM_SlideMove_f, PM_SlideMove);


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
	a->remove(&(PVOID&)PM_Weapon_f, PM_Weapon);
	a->remove(&(PVOID&)r::CG_DrawActive_f, r::CG_DrawActive);
	a->remove(&(PVOID&)Pmove_f, Pmove);
	a->remove(&(PVOID&)stub, Script_ScriptMenuResponse);
	a->remove(&(PVOID&)stub2, Script_OpenScriptMenu);
	a->remove(&(PVOID&)CG_CalcCrosshairColor_f, CG_CalcCrosshairColor);
	a->remove(&(PVOID&)PM_Weapon_WeaponTimeAdjust_f, PM_Weapon_WeaponTimeAdjust);
	a->remove(&(PVOID&)PmoveSingle_stub_f, PmoveSingle_stub);
	a->remove(&(PVOID&)PM_SlideMove_f, PM_SlideMove);


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