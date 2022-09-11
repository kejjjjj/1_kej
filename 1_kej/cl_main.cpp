#include "pch.h"

void cg::CL_Disconnect(int localClientNum)
{
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "calling CL_Disconnect()\n");
	Cmd_RemoveCommand("1_kej_openmenu");
	CG_RemoveHooks();


	return CL_Disconnect_f(localClientNum);
}