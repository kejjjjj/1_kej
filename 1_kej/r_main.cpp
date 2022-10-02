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
		Mod_DrawAngleHelper();
		Mod_DrawCurveSpeed();
		Mod_A_Strafebot();
		Mod_A_AutoFPS();
		Mod_DrawEvents();

		
		if (GetAsyncKeyState(VK_NUMPAD7) & 1) {

			//Material* fxMaterial = reinterpret_cast<Material*>(0x84F2D0);
			//Material* fxMaterialGlow = reinterpret_cast<Material*>(0x84F2D4);

			//if (fxMaterial) {
			//	std::cout << "fxMaterial->techniqueSet->name: " << fxMaterial->techniqueSet->name << '\n';
			//}
			//if (fxMaterialGlow) {
			//	std::cout << "fxMaterialGlow->techniqueSet->name: " << fxMaterial->techniqueSet->name << '\n';
			//}

			R_AddCmdDrawTextWithEffects((char*)"hello", "fonts/normalfont", 0, 400, 2, 2, 0.f, vec4_t{ 1,1,0,1 }, 0, vec4_t{ 1,1,1,1 }, 0, 0, 0, 0, 0, 0);
		}


	
	}



	return CG_DrawActive_f();
}