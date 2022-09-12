#include "pch.h"

void cg::CL_Disconnect(int localClientNum)
{

	if (clientUI[0].connectionState != CA_DISCONNECTED) { //gets called in the loading screen in 1.7
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "removing hooks because player disconnected\n");
		Cmd_RemoveCommand("1_kej_openmenu");
		CG_RemoveHooks();

		Mod_EditMemory(true);
	}


	return CL_Disconnect_f(localClientNum);
}