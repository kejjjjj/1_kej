#pragma once

#ifndef uibuilder
#define uibuilder

#include "pch.h"

namespace r
{
	void R_JumpBuilder_ConstructKey(char &direction, char value, const char* buttonName);
	void R_JumpBuilder_Main();
	void R_JumpBuilder_Builder();
	void R_JumpBuilder_Preferences();
	void R_JumpBuilder_Hotkeys();
	void R_JumpBuilder_ToggleFreeMode();


}


#endif