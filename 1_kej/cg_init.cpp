
#include "pch.h"

void cg::cod4x()
{
	if (!(DWORD)GetModuleHandleA("cod4x_021.dll"))
		return;

	BG_WeaponNames = reinterpret_cast<WeaponDef**>(cod4x_entry + 0x443DDE0); 
}
void cg::CG_Init()
{
	cod4x();
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "^21_kej extension has been loaded!\n");
	Scr_Init();

	std::cout << "com_printf moment\n";

	while (true) {
		if(GetAsyncKeyState(VK_MENU)&1)
			*(xfunction_t*)0x725B7C = (xfunction_t)PlayerCmd_JumpButtonPressed;
		Sleep(100);
	}
}