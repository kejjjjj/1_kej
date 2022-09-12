#include "pch.h"

HRESULT __stdcall r::draw_func(IDirect3DDevice9* pDevice)
{
	if (mglobs.isUsing) {
		R_ImGui(pDevice);
		if (R_OpenMenu(pDevice)) {
			R_EndRender();
		}
	}
	return pEndScene(pDevice);
}
void __cdecl r::CG_DrawActive()
{
	if (mglobs.isUsing) {
		Mod_DrawVelocity();
		Mod_DrawCoordinates();
		Mod_DrawSurfaceInfo();
	}

	return CG_DrawActive_f();
}