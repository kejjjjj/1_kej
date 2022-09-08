#include "pch.h"

void Scr_Init()
{
	Scr_LoadMethods();
	hook a;
	a.install(&(PVOID&)Player_GetMethod_f, Player_GetMethod);
	a.install(&(PVOID&)Scr_GetFunction_f, Scr_GetFunction);

}