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
			if (analyzer.RecordingExists() && !analyzer.isRecording() && analyzer.InRecordingMode() && analyzer.isPreviewing()) {
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

		if (analyzer.isRecording())
			R_DrawText("Recording", 0, 800, 2, 2, 0, vec4_t{ 1,1,1,1 }, 0);

		//float optYaw, test;

		////static DWORD old_ms = Sys_Milliseconds();
		////DWORD ms = Sys_Milliseconds();

		//if (std::isnan(clients->viewangles[YAW]))
		//	clients->viewangles[YAW] = 0;
		//else if (clients->viewangles[YAW] > 3000 || clients->viewangles[YAW] < -3000)
		//	clients->viewangles[YAW] = fmodf(clients->viewangles[YAW], 360);

		//optYaw = getOptAngle(test);
		//if (optYaw == -400.f || std::isnan(optYaw))
		//	return CG_DrawActive_f();

		//uint32_t forwardmove = (uint32_t)input->move;
		//uint32_t sidemove = (uint32_t)input->strafe;

		//if (GROUND && forwardmove <= 0 || GROUND && sidemove == 0)
		//	return CG_DrawActive_f();


		//if (sidemove != 0 || forwardmove != 0) {
		//	//UserCMD_SetAngles(angles);
		//	//if (ms - old_ms > 1000 || GROUND) {
		//	//	old_ms = ms;
		//	setYaw(cgs->refdefViewAngles[YAW], optYaw);
		//	//}
		//}
	}



	return CG_DrawActive_f();
}