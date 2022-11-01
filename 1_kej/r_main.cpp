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

			//const dvar_s* _fov = Dvar_FindMalleableVar("cg_fov");
			//const dvar_s* fovscale = Dvar_FindMalleableVar("cg_fovscale");

			//const float fov = _fov->current.value * fovscale->current.value * v::mod_fps_transferz.evar->arrayValue[3];
			//vec2_t zone333 = { fps_zones.fps333, 90.f + fps_zones.fps333 };

			////CG_FillAngleYaw(25, 70, clients->cgameViewangles[YAW], 700, 10, fov, vec4_t{0,255,0,170}, true, true);
			//float yaw = clients->cgameViewangles[YAW] > 0 ? clients->cgameViewangles[YAW] : 180.f - clients->cgameViewangles[YAW] * -1; //mirror the yaw
			//bool isInverted = clients->cgameViewangles[YAW] < fov || clients->cgameViewangles[YAW] > 180.f - fov;
			//
			//if (isInverted) {
			//	CG_FillAngleYaw(-180.f + zone333[0], -180.f + (zone333[0] + fps_zones.length333), yaw, 700, 10, fov, v::mod_333col.evar->vecValue, true, true);
			//	CG_FillAngleYaw(-180.f + zone333[1], -180.f + (zone333[1] + fps_zones.length333), yaw, 700, 10, fov, v::mod_333col.evar->vecValue, true, true);
			//}
			//CG_FillAngleYaw(zone333[0], (zone333[0] + fps_zones.length333), yaw, 700, 10, fov, v::mod_333col.evar->vecValue, true, true);
			//CG_FillAngleYaw(zone333[1], (zone333[1] + fps_zones.length333), yaw, 700, 10, fov, v::mod_333col.evar->vecValue, true, true);
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