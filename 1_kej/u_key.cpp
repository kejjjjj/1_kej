#include "pch.h"

BYTE cg::KeyHeld(BYTE key)
{
	return GetAsyncKeyState(key) < 0;
}
BYTE cg::KeyPressed(BYTE key)
{
	return GetAsyncKeyState(key) & 1;
}
BYTE cg::KeyHeld()
{
	for (BYTE i = 1; i < 0xFE; i++) {
		if (GetAsyncKeyState(i) < 0)
			return i;
	}
	return 0;
}
BYTE cg::KeyPressed()
{	
	for (BYTE i = 1; i < 0xFE; i++) {
		if (GetAsyncKeyState(i) & 1)
			return i;
	}
	return 0;
}