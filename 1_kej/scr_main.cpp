#include "pch.h"

void Scr_Init()
{
	Scr_LoadMethods();
	hook a;
	a.install(&(void*&)Player_GetMethod_f, Player_GetMethod);


}