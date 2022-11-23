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

			Mod_DrawVelocityDirection();
			if (!clc.demoplaying) {

				Mod_DrawWorldAxes();

				if (analyzer.RecordingExists() && !analyzer.isRecording() && analyzer.isPreviewing()) {
					Mod_DrawJumpPath();
					Mod_DrawJumpHitbox();
					Mod_DrawJumpDirection();

				}

				if (jbuilder.isEditing() && !jbuilder.segments.empty()) {
					Mod_B_DrawPath();


				}

				Mod_DrawFPSHelpers();
				Mod_A_500FPS();
			}

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
		Mod_DrawCurveSpeed();

		Mod_DrawEvents();
		Mod_BounceCalculator();


		if (!clc.demoplaying) {
			Mod_DrawAngleHelper();
			Mod_A_Strafebot();
			Mod_A_AutoFPS();
			Mod_DisallowHalfbeat();
		}
		
		if (vangle_que.yes) {

			CG_SetPlayerAngles(vangle_que.src, vangle_que.dst);
			vangle_que.yes = false;
		}
		//if(jumpanalyzer.hugging_bounce && !jumpanalyzer.walking)
		//char buff[48];
		//sprintf_s(buff, "airTime: %i\ngroundTime: %i", jumpanalyzer.serverTime - jumpanalyzer.airTime, jumpanalyzer.serverTime - jumpanalyzer.groundTime);
		//r::R_AddCmdDrawTextWithEffects(buff, "fonts/objectivefont", r::X(300), r::Y(300), v::mod_velometer.GetArray(3), v::mod_velometer.GetArray(3), 0.f, vec4_t{255,255,0,255}, 3, v::mod_velometer_glow.evar->vecValue, 0, 0, 0, 500, 1000, 2000);
		//
		//float delta = AngleDelta(cgs->compassNorthYaw, cgs->refdefViewAngles[1]);
		//
		//static float incr = 0;
		//ScreenPlacement* scrPlace = CG_GetScreenPlacement(cgs->clientNum);
		//CG_DrawRotatedPic(1, 1, scrPlace, 100, 100, 100, 100, delta, vec4_t{ 0,255,0,170 }, "white");

		
	
	}



	return CG_DrawActive_f();
}