#include "pch.h"

void cg::SV_Map(char* a1)
{
	dvar_s* fs_game = Dvar_FindMalleableVar("fs_game");

	if (fs_game) {
		if (!strcmp(fs_game->current.string, "mods/1_kej_v2")) {
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "Loading 1_kej features..\n");
			CG_InitHooks();
			Cmd_Init();
			if (!r::R_Init()) {
				MessageBoxA(NULL, "failed to hook renderer", "FATAL ERROR", MB_ICONERROR);
				exit(-1);
			}
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2Done!\n");

		}
	}

	return SV_Map_f(a1);
}