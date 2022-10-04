#include "pch.h"



HRESULT __stdcall r::draw_func(IDirect3DDevice9* pDevice)
{
	r::device_needs_reset = false;

	if (mglobs.isUsing) {
		R_ImGui(pDevice);
		if (R_OpenMenu(pDevice)) {
			//ImGui::GetBackgroundDrawList()->Addline
			//CMod_HighlightSelected(); 
			Mod_DrawVelocityDirection();
			Mod_DrawWorldAxes();

			if (analyzer.RecordingExists() && !analyzer.isRecording() && analyzer.isPreviewing()) {
				Mod_DrawJumpPath();
				Mod_DrawJumpHitbox();
				Mod_DrawJumpDirection();
				
			}
			Mod_DrawFPSHelpers();

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
		/*Mod_DrawFPSHelpers();*/
		Mod_DrawAngleHelper();
		Mod_DrawCurveSpeed();
		Mod_A_Strafebot();
		Mod_A_AutoFPS();
		Mod_DrawEvents();


	
	}



	return CG_DrawActive_f();
}