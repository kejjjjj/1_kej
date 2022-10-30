#include "pch.h"


XAssetHeader __cdecl Material_Register_FastFile(const char* a1)
{
	return ((XAssetHeader(*)(const char* a1))0x489570)(a1);
}
HRESULT __stdcall r::draw_func(IDirect3DDevice9* pDevice)
{
	r::device_needs_reset = false;

	if (mglobs.isUsing) {
		if (!R_ImGui(pDevice)) {
			fs::Log_Write(LOG_FATAL, "Unable to initialize imgui\n");
		}
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
			//	BG_AddPredictableEventToPlayerstate(ps_loc, EV_FIRST_RAISE_WEAPON, 0);

			//}
			Mod_DrawFPSHelpers();
			Mod_A_500FPS();
			//cg::CMod_HighlightSelected();



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
		/*Mod_DrawFPSHelpers();*/
		Mod_DrawAngleHelper();
		Mod_DrawCurveSpeed();
		Mod_A_Strafebot();
		Mod_A_AutoFPS();
		Mod_DrawEvents();
		Mod_BounceCalculator();
		//if(jumpanalyzer.hugging_bounce && !jumpanalyzer.walking)
		//	r::R_AddCmdDrawTextWithEffects((char*)"hugging", "fonts/objectivefont", r::X(300), r::Y(300), v::mod_velometer.GetArray(3), v::mod_velometer.GetArray(3), 0.f, vec4_t{255,255,0,255}, 3, v::mod_velometer_glow.evar->vecValue, 0, 0, 0, 500, 1000, 2000);

	
	}



	return CG_DrawActive_f();
}