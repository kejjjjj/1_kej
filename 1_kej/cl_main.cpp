#include "pch.h"

void cg::CL_Disconnect(int localClientNum)
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "calling CL_Disconnect()\n");

	if (clientUI[0].connectionState != CA_DISCONNECTED) { //gets called in the loading screen in 1.7
		Cmd_RemoveCommand("1_kej_openmenu");
		CG_RemoveHooks();

		Mod_EditMemory(true);
	}


	return CL_Disconnect_f(localClientNum);
}