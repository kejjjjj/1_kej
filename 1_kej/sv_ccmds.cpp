#include "pch.h"

void cg::Mod_EditMemory(bool forceDisable)
{
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

	const auto L_CreateCmd = [](const char* cmdname) -> void {
		
		if (Dvar_FindMalleableVar(cmdname)) 
			return;
		
		char buff[128];

		sprintf_s(buff, "seta %s 0\n", cmdname);

		Cbuf_AddText(buff, cgs->clientNum);

	};

	SV_Map_f();

	const dvar_s* fs_game = Dvar_FindMalleableVar("fs_game");
	const dvar_s* g_gametype = Dvar_FindMalleableVar("g_gametype");
	const dvar_s* sv_running = Dvar_FindMalleableVar("sv_running");

	if (fs_game && g_gametype && sv_running) {

		if (sv_cmd_args->argc[sv_cmd_args->nesting] < 1)
			return;

		if (!sv_running->current.enabled) {
			Com_PrintError(CON_CHANNEL_CONSOLEONLY, "failed to [%s] because '%s' is missing\n", *(sv_cmd_args->argv[sv_cmd_args->nesting] + 0), *(sv_cmd_args->argv[sv_cmd_args->nesting] + 1));
			return;
		}

		//for restore position
		L_CreateCmd("cjmod_mapname");
		L_CreateCmd("cjmod_X");
		L_CreateCmd("cjmod_Y");
		L_CreateCmd("cjmod_Z");
		L_CreateCmd("cjmod_angleX");
		L_CreateCmd("cjmod_angleY");



		dvar_s* sv_punkbuster = Dvar_FindMalleableVar("sv_punkbuster");
		dvar_s* cl_punkbuster = Dvar_FindMalleableVar("cl_punkbuster");

		if (sv_punkbuster) { sv_punkbuster->current.integer = 0; sv_punkbuster->current.enabled = 0; }
		if (cl_punkbuster) { cl_punkbuster->current.integer = 0; cl_punkbuster->current.enabled = 0; }

		if (!strcmp(fs_game->current.string, "mods/1_kej_v2") && (!strcmp(g_gametype->current.string, "cj") || !strcmp(g_gametype->latched.string, "cj"))) {
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "Loading 1_kej features..\n");
			std::cout << "Loading 1_kej features..\n";

			cg::CG_InitHooks();
			Cmd_Init();
			Mod_EditMemory(false);
			if (!r::R_Init()) {
				//MessageBoxA(NULL, "failed to hook renderer", "FATAL ERROR", MB_ICONERROR);
				fs::Log_Write(LOG_FATAL, "failed to hook renderer\n");
			}
			analyzer.ClearData();
			box500.bounds[0] = 32;
			box500.bounds[1] = 32;
			box500.bounds[2] = 32;


			Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2Done!\n");

		}
	}

	return;
}