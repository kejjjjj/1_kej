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

		if (analyzer.isRecording())
			R_DrawText("Recording", 0, 800, 2, 2, 0, vec4_t{ 1,1,1,1 }, 0);

		char buff[150];

		//sprintf_s(buff, "wishDir[0]: %.6f\nwishDir[1]: %.6f\nwishDirAngle: %.6f\naccelSpeed: %.6f\naddSpeed: %.6f",
		//				air.wishDir[0], air.wishDir[1], atan2(air.wishDir[1] * air.accelspeed, air.wishDir[0] * air.accelspeed) * 180.f / PI, air.accelspeed, air.addspeed);

		sprintf_s(buff, "125fps: %.3f\n200fps: %.3f\n250fps: %.3f\n333fps: %.3f\nl200: %.3f", fps_zones.fps125, fps_zones.fps200, fps_zones.fps250, fps_zones.fps333, fps_zones.length200);

		R_DrawText(buff, 0, 300, 1, 1, 0, vec4_t{ 1,1,0,1 }, 0);


		//char buff[40];
		//sprintf_s(buff, "clients->snap.ps.weaponstate: %i", clients->snap.ps.weaponstate);
		//R_DrawText(buff, 0, 300, 2, 2, 0, vec4_t{ 1,1,0,1 }, 0);

		//if (GetAsyncKeyState(VK_HOME) & 1) {
		//	int rpg = BG_FindWeaponIndexForName("rpg_mp");

		//	if (rpg) {
		//		G_SelectWeaponIndex(rpg, -1);

		//		int weapons[128];
		//		size_t count = G_GetWeaponsList(weapons);

		//		for (size_t i = 0; i < count; i++)
		//			Com_Printf(CON_CHANNEL_OBITUARY, "weapon[%i]: %s\n", i, BG_WeaponNames[weapons[i]]->szInternalName);


		//	}

		//}

		float optYaw, test;

		//static DWORD old_ms = Sys_Milliseconds();
		//DWORD ms = Sys_Milliseconds();

		if (std::isnan(clients->viewangles[YAW]))
			clients->viewangles[YAW] = 0;
		else if (clients->viewangles[YAW] > 3000 || clients->viewangles[YAW] < -3000)
			clients->viewangles[YAW] = fmodf(clients->viewangles[YAW], 360);

		optYaw = getOptAngle(test);
		if (optYaw == -400.f || std::isnan(optYaw))
			return CG_DrawActive_f();

		uint32_t forwardmove = (uint32_t)input->move;
		uint32_t sidemove = (uint32_t)input->strafe;

		if (GROUND && forwardmove <= 0 || GROUND && sidemove == 0)
			return CG_DrawActive_f();


		if (sidemove != 0 || forwardmove != 0) {
			//UserCMD_SetAngles(angles);
			//if (ms - old_ms > 1000 || GROUND) {
			//	old_ms = ms;
			setYaw(cgs->refdefViewAngles[YAW], optYaw);
			//}
		}
	}



	return CG_DrawActive_f();
}