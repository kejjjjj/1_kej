#include "pch.h"

int cg::BG_FindWeaponIndexForName(const char* name)
{
	return ((int(__cdecl*)(const char*))0x416610)(name);
}
//int cg::PM_Weapon_WeaponTimeAdjust(pml_t* pml, pmove_t* pm) //can't really call this because this function also sets animations
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
//}
void _test(int delay)
{
	//if (delay)
	//	Com_Printf(CON_CHANNEL_OBITUARY, "hello world\n");
	jumpanalyzer.weapon_cant_fire = delay;
}
__declspec(naked) void cg::PM_Weapon_WeaponTimeAdjust()
{
	static int delayedAction;
	static DWORD _retn = 0x41A4E7;
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
		call _test;
		add esp, 0x4;
		//mov[jumpanalyzer + 18], eax;
		jmp _retn;
	}
}
void __cdecl cg::G_SelectWeaponIndex(int iWeaponIndex, int clientNum)
{
	const DWORD G_SelectWeaponIndex_f = 0x4EA470;
	__asm
	{
		mov iWeaponIndex, eax;
		mov clientNum, esi;
		call G_SelectWeaponIndex_f;
	}
}
size_t cg::G_GetWeaponsList(int* weapons)
{
	size_t count(0);
	for (int i = 1; i < *bg_lastParsedWeaponIndex + 1; i++) {

		if (((1 << (i & 0x1F)) & clients->snap.ps.weapons[i >> 5]) != 0) {
			weapons[count] = i;
			count++;
		}

	}
	return count;
}
uint32_t cg::CG_SelectWeaponIndex(uint32_t weaponIndex, int localClientNum)
{
	uint32_t out = 0;
	__asm
	{
		mov eax, weaponIndex;
		mov ecx, localClientNum;
		mov esi, 0x458F10;
		call esi;
		mov out, eax;

	}

	return out;
}