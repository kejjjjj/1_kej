#include "pch.h"

void cg::Mod_EditMemory(bool forceDisable)
{
	std::cout << "modifying bytes\n";

	bool enabled = false;
	hook* a = nullptr;
	const char* bytes = "";

	evar_o* evar = Evar_FindByName("1_kej_bhop_nodelay");
	if (evar) {
		enabled = (forceDisable == true) ? false : evar->isEnabled();
		bytes = (enabled == false) ? "\x81\xF9\xF4\x01\x00\x00" : "\x83\xF9\x00\x90\x90\x90"; //if ( pm->cmd.serverTime - _ps->jumpTime < 500 )
		a->write_addr(0x407DAE, bytes, 6);
	}
	evar = Evar_FindByName("1_kej_bhop");

	if (evar) {
		enabled = (forceDisable == true) ? false : evar->isEnabled();
		bytes = (enabled == false) ? "\xF7\x46\x28\x00\x04\x00" : "\xF7\x46\x28\x00\x00\x00"; //if ( (pm->oldcmd.buttons & 0x400) != 0 )
		a->write_addr(0x407DDC, bytes, 6);
	}

}


void cg::SV_Map()
{
	dvar_s* fs_game = Dvar_FindMalleableVar("fs_game");

	if (fs_game) {
		if (!strcmp(fs_game->current.string, "mods/1_kej_v2")) {
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "Loading 1_kej features..\n");
			std::cout << "Loading 1_kej features..\n";

			cg::CG_InitHooks();
			Cmd_Init();
			Mod_EditMemory(false);
			if (!r::R_Init()) {
				MessageBoxA(NULL, "failed to hook renderer", "FATAL ERROR", MB_ICONERROR);
				exit(-1);
			}
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2Done!\n");

		}
	}

	return SV_Map_f();
}