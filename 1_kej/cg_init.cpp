
#include "pch.h"

void cg::cod4x()
{
	if (!(DWORD)GetModuleHandleA("cod4x_021.dll")) {
		r::WndProcAddr = 0x57BB20;
		return;
	}

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
	hook* a = nullptr;
	cod4x();

	Com_Printf(CON_CHANNEL_CONSOLEONLY, "^21_kej extension has been loaded!\n");
	Scr_Init();
	Cmd_Init();
	//Dvar_Init();
	if (!r::R_Init()){
		MessageBoxA(NULL, "failed to hook renderer", "FATAL ERROR", MB_ICONERROR);
		exit(-1);
	}
}