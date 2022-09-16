#include "pch.h"

int cg::BG_FindWeaponIndexForName(const char* name)
{
	return ((int(__cdecl*)(const char*))0x416610)(name);
}
//int cg::PM_Weapon_WeaponTimeAdjust(pml_t* pml, pmove_t* pm)
//{
//	if (!pml || !pm)
//		return false;
//	DWORD fnc = 0x418C80;
//	int value{};
//	__asm
//	{
//		mov edx, pml;
//		mov eax, pm;
//		push eax;
//		call fnc;
//		add esp, 0x8;
//		mov value, eax;
//
//	}
//	return value;
//	//return ((int32_t(*)(pml_t*, pmove_t*))0x418C80)(pml, pm);
//}
void test(int delay)
{
	//if (delay)
	//	Com_Printf(CON_CHANNEL_OBITUARY, "hello world\n");
	jumpanalyzer.weapon_cant_fire = delay;
}
__declspec(naked) void cg::PM_Weapon_WeaponTimeAdjust()
{
	static int delayedAction;
	static DWORD retn = 0x41A4E7;
	static DWORD fnc = 0x418C80;
	//bool& cant_fire = jumpanalyzer.weapon_cant_fire;
	__asm
	{
		push edi;
		mov edx, esi;
		call fnc;
		add esp, 4;
		mov ecx, ebp;
		mov ebx, eax;
		push eax;
		call test;
		add esp, 0x4;
		//mov[jumpanalyzer + 18], eax;
		jmp retn;
	}
}