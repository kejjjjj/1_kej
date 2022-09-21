#pragma once

#ifndef rmenu
#define rmenu
#include "pch.h"

namespace r
{
	inline bool should_draw_menu;
	inline vec3_t angles_before_menu;

	void R_RemoveInput(bool _true, bool save_file = true);
	bool R_OpenMenu(IDirect3DDevice9* pDevice);
	void R_EndRender();
	void R_MenuStyle();

	void R_Features(bool& wantsEditor);


	void R_JumpView(bool& isOpen);
	void R_JumpView_Main();
	void R_JumpView_KeyEvents();
	void R_JumpView_Preferences();
	void R_JumpView_BounceButtons(int& menu_frame);
	void R_JumpView_IO();
	void R_JumpView_Help();
	bool R_JumpView_EventButtons(std::set<int>& eventV, int& menu_frame, const char* prevBut, const char* nextBut);
	
}

#endif