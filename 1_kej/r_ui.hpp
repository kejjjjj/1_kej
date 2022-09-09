#pragma once

#ifndef rmenu
#define rmenu
#include "pch.h"

namespace r
{
	inline bool should_draw_menu;

	void R_RemoveInput(bool _true);
	bool R_OpenMenu(IDirect3DDevice9* pDevice);
	void R_EndRender();
	void R_MenuStyle();

	void R_Features();
}

#endif