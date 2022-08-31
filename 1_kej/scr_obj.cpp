
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
float Scr_GetVector(uint32_t param, float* vector)
{
	return ((float(__cdecl*)(uint32_t _prm, float* vector))0x5236E0)(param, vector);
}
int Scr_GetNumParam()
{
	return *(int*)0x1794074;
}
int Scr_AddInt(int val)
{
	return ((int(__cdecl*)(uint32_t _prm))0x523AB0)(val);
}
int Scr_AddFloat(float val)
{
	return ((int(__cdecl*)(float _prm))0x523AB0)(val);
}
float* Scr_AddVector(float* vector)
{
	return ((float* (__cdecl*)(float* _prm))0x523D10)(vector);

}