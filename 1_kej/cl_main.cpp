#include "pch.h"

void cg::CL_Disconnect(int localClientNum)
{

	if (clientUI[0].connectionState != CA_DISCONNECTED) { //gets called in the loading screen in 1.7
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "removing hooks because player disconnected\n");
		Cmd_RemoveCommand("1_kej_openmenu");
		CG_RemoveHooks();
		r::ResetImFont = true;
		if (analyzer.isRecording())
			analyzer.StopRecording();

		analyzer.ClearData();

		Mod_EditMemory(true);

		for(auto &i : r::imagePairs)
			i.second->Release();

	}


	return CL_Disconnect_f(localClientNum);
}