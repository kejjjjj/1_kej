#pragma once

#ifndef rmenu
#define rmenu
#include "pch.h"

namespace r
{
	inline bool should_draw_menu;

	void R_RemoveInput(bool _true, bool save_file = true);
	bool R_OpenMenu(IDirect3DDevice9* pDevice);
	void R_EndRender();
	void R_MenuStyle();

	void R_Features();


	void R_JumpView(bool& isOpen);
	void R_JumpView_Main();
	void R_JumpView_Preferences();
	void R_JumpView_BounceButtons(int& menu_frame);
	void R_JumpView_IO();
	
}

#endif