#include "pch.h"

HRESULT __stdcall r::draw_func(IDirect3DDevice9* pDevice)
{
	r::device_needs_reset = false;

	if (mglobs.isUsing) {
		R_ImGui(pDevice);
		if (R_OpenMenu(pDevice)) {
			//ImGui::GetBackgroundDrawList()->Addline
			Mod_DrawVelocityDirection();
			Mod_DrawWorldAxes();
			
		}
		R_EndRender();
	}
	return pEndScene(pDevice);
}
void __cdecl r::CG_DrawActive()
{
	if (mglobs.isUsing) {
		Mod_DrawVelocity();
		Mod_DrawCoordinates();
		Mod_DrawSurfaceInfo();
		Mod_DrawFPSHelpers();
		Mod_AngleHelper();
	}

	return CG_DrawActive_f();
}