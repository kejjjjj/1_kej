#include "pch.h"

void Scr_Init()
{
	std::cout << "Player_GetMethod: 0x" << std::hex << &Player_GetMethod << '\n';

	Scr_LoadMethods();
	hook a;
	a.install(&(PVOID&)Player_GetMethod_f, Player_GetMethod);

}