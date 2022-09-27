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
		Mod_A_Strafebot();
		Mod_A_AutoFPS();

		if (analyzer.isRecording())
			R_DrawText("Recording", 0, 800, 2, 2, 0, vec4_t{ 1,1,1,1 }, 0);

		if(automation.pendingSlide)
			R_DrawText("Slide", v::mod_velometer.evar->arrayValue[1], v::mod_velometer.evar->arrayValue[2] - 20 * v::mod_velometer.evar->arrayValue[3], v::mod_velometer.evar->arrayValue[3], v::mod_velometer.evar->arrayValue[3], 0, vec4_t{0,1,0,1}, 0);


		//if (GetAsyncKeyState(VK_INSERT) & 1) {
		//	//itemParse_t** menuItems = reinterpret_cast<itemParse_t**>(0xCB0CD10);
		//	for (int i = 0; i < 512; i++) {

		//		menuDef_t* menu = g_menus->menus[i];

		//		if (menu) {
		//			Com_Printf(CON_CHANNEL_CONSOLEONLY, "menu[%i]: %s\n", i, menu->window.name);
		//		}

		//	}
		//}

		//char buff[150];

		////sprintf_s(buff, "wishDir[0]: %.6f\nwishDir[1]: %.6f\nwishDirAngle: %.6f\naccelSpeed: %.6f\naddSpeed: %.6f",
		////				air.wishDir[0], air.wishDir[1], atan2(air.wishDir[1] * air.accelspeed, air.wishDir[0] * air.accelspeed) * 180.f / PI, air.accelspeed, air.addspeed);

		//sprintf_s(buff, "125fps: %.3f\n200fps: %.3f\n250fps: %.3f\n333fps: %.3f\nl200: %.3f", fps_zones.fps125, fps_zones.fps200, fps_zones.fps250, fps_zones.fps333, fps_zones.length200);

		//R_DrawText(buff, 0, 300, 1, 1, 0, vec4_t{ 1,1,0,1 }, 0);


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

	
	}



	return CG_DrawActive_f();
}