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

			if (jbuilder.isEditing() && !jbuilder.segments.empty()) {
				Mod_B_DrawPath();


			}
			//if (GetAsyncKeyState(VK_NUMPAD9) & 1) {
			//	for (size_t i = 0; i < 2047; i++) {

			//		Material* mtl = rgp->sortedMaterials[i];

			//		if (mtl) {
			//			Com_Printf(CON_CHANNEL_OBITUARY, "[%i]: ^5%s\n", i, mtl->info.name);
			//		}

			//	}
			//}
			//if (jbuilder.MovementExists()) {
			//	jump_data* jData = jbuilder.FetchFrameData(jbuilder.current_frame-1);

			//	if (jData) {

			//		//VectorCopy(jData->origin, ps_loc->origin);

			//		r::box_s box = r::R_ConstructBoxFromBounds(jData->origin, jData->mins, jData->maxs);

			//		r::R_DrawConstructedBoxEdges(box, vec4_t{ 255,0,0,255 });
			//		r::R_DrawConstructedBox(box, vec4_t{ 255,0,0,50 });

			//	}

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