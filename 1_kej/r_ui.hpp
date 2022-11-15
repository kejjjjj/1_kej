#pragma once

#ifndef rmenu
#define rmenu
#include "pch.h"

namespace r
{
	inline bool should_draw_menu;
	inline vec3_t angles_before_menu;

	void IN_ActiveMouse(int active);
	void R_RemoveInput(bool _true, bool save_file = true);
	bool R_OpenMenu(IDirect3DDevice9* pDevice);
	void R_EndRender();
	void R_MenuStyle(float transparencyScale = 1.f);

	void R_Features(bool& wantsEditor);

	void R_DrawMenuByName(const char* category, const bool JustClicked, bool& wantsEditor);

	void R_JumpView(bool& isOpen);
	void R_JumpView_Main(std::vector<jump_data>& container);
	void R_JumpView_KeyEvents();
	void R_JumpView_Preferences();
	void R_JumpView_BounceButtons(int& menu_frame);
	void R_JumpView_IO();
	void R_JumpView_Help();
	void R_JumpView_ToggleFreeMode();
	void R_JumpView_HandleWeapons(int& menu_frame, int min_frame, int max_frame);
	bool R_JumpView_EventButtons(std::set<int>& eventV, int& menu_frame, const char* prevBut, const char* nextBut);


	void R_Automation_Features();

	void R_OtherTab();
	void R_GameMenuBrowser(bool& isOpen);
	void R_GameMenuBrowser_ItemDef(itemDef_s* item);
	void R_GameMenuBrowser_WindowProperties(windowDef_t& wnd);
	

}

#endif