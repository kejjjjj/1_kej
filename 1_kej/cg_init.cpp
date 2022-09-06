
#include "pch.h"

void cg::cod4x()
{
	if (!(DWORD)GetModuleHandleA("cod4x_021.dll"))
		return;

	BG_WeaponNames = reinterpret_cast<WeaponDef**>(cod4x_entry + 0x443DDE0); 
}
#define MAX_PLAYERCMD_METHODS 84
void cg::CG_Init()
{
	hook* a = nullptr;
	cod4x();
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "^21_kej extension has been loaded!\n");
	Scr_Init();
	Dvar_Init();

	while (true) {
		//if(GetAsyncKeyState(VK_MENU)&1)
		//	Dvar_Init();

		//	cg::BuiltinMethodDef* methods_2 = reinterpret_cast<cg::BuiltinMethodDef*>(0x6BC880);

		//	for (int i = 0; i < 84; i++) {
		//		methods_2 = (cg::BuiltinMethodDef*)(0x6BC880 + (i * 0xC));
		//		if (!methods_2)
		//			continue;	

		//		if(methods_2->actionString)
		//			Com_Printf(CON_CHANNEL_CONSOLEONLY, "[%i]: %s\n", i, methods_2->actionString);
		//		else Com_Printf(CON_CHANNEL_CONSOLEONLY, "[%i]: NULL (%s)\n", i, std::format("{:#x}", (int)methods_2).c_str());
		//	}
		//}
		Sleep(1000);
	}
}