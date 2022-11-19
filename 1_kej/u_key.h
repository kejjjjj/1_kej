#pragma once

#ifndef ukey
#define ukey

#include "pch.h"

namespace cg
{
	BYTE KeyPressed(BYTE key);
	BYTE KeyHeld(BYTE key);
	BYTE KeyPressed();
	BYTE KeyHeld();

}

#endif