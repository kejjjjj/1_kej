#include "pch.h"


XAssetHeader __cdecl Material_Register_FastFile(const char* a1)
{
	return ((XAssetHeader(*)(const char* a1))0x489570)(a1);
}
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

			if (jbuilder.isEditing() && !jbuilder.segments.empty()) {
				Mod_B_DrawPath();


			}
			
			//if (GetAsyncKeyState(VK_NUMPAD9) & 1) {
			//	dmaterial_t* frstMat = nullptr;
			//	
			//	for (int i = 0; i < cm->numMaterials; i++) {
			//		cm->materials[i].contentFlags = 0;
			//		cm->materials[i].surfaceFlags = 0;
			//		memcpy(cm->materials[i].material, cm->materials[0].material, 64);



			//	}
			//

			//}
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