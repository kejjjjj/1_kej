
#include "pch.h"

void Scr_ObjectError(const char* msg, ...)
{
	char v2[0x3FFu];
	va_list va;

	va_start(va, msg);
	_vsnprintf_s(v2, 0x3FFu, msg, va);
	v2[0x3FFu-1] = 0;

	return ((void(*)(const char* msg))0x0523F90)(v2);
}
int Scr_GetInt(uint32_t param)
{
	return ((int(*)(uint32_t _prm))0x5231F0)(param);
}
float Scr_GetFloat(uint32_t param)
{
	return ((float(*)(uint32_t _prm))0x523360)(param);
}
char* Scr_GetString(uint32_t parameter)
{
	int numstr{};
	char* str;
	
	__asm {
		mov eax, parameter;
		push eax;
		mov esi, 0x523400;
		call esi;
		add esp, 0x4;
		mov numstr, eax;
	}

	if (numstr) 
		str = (char*)((((int)0x14E8A04) + (12 * numstr + 4)) + 0x2187C);
	else str = 0;
	
	return str;
}
void Scr_AddString(char* string)
{
	const static DWORD fnc = 0x523C00;
	__asm
	{
		mov esi, string;
		call fnc;
	}

	return;
}
float __cdecl Scr_GetVector(uint32_t param, float* vector)
{

	__asm
	{
		mov edx, vector;
		push edx;
		mov eax, param;
		push param;
		mov esi, 0x5236E0;
		call esi;
		add esp, 0x8;
	}
	return 0.f;
}
int Scr_GetNumParam()
{
	return *(int*)0x1794074;
}
int Scr_AddInt(int val)
{
	return ((int(__cdecl*)(int32_t _prm))0x523AB0)(val);
}
int Scr_AddFloat(float val)
{
	return ((int(__cdecl*)(float _prm))0x523AB0)(val);
}
float* Scr_AddVector(float* vector)
{
	const DWORD fnc = 0x523D10;
	_asm {
		mov esi, vector;
		push esi;
		mov eax, 0x523D10;
		call eax;
		pop esi;
	}
	return 0;

}
cg::gentity_s* Scr_GetEntity(scr_entref_t entref)
{
	return ((cg::gentity_s* (__cdecl*)(scr_entref_t))0x4CB260)(entref);
}