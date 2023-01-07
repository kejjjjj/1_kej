#include "pch.h"

void cg::CL_Disconnect(int localClientNum)
{

	if (clientUI[0].connectionState != CA_DISCONNECTED) { //gets called in the loading screen in 1.7
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "removing hooks because player disconnected\n");
		Cmd_RemoveCommand("1_kej_openmenu");
		CG_RemoveHooks();
		cworld.terrain.clip_points.clear();
		cworld.terrain.clip_points.resize(0);
		r::ResetImFont = true;
		if (analyzer.isRecording())
			analyzer.StopRecording();

		analyzer.ClearData();
		jbuilder.ClearData();

		Mod_EditMemory(true);

		glob_pm = nullptr;
		glob_pml = nullptr;
	}


	return CL_Disconnect_f(localClientNum);
}
void cg::CL_PlayDemo()
{
	CL_PlayDemo_f();

	if (clc.demoplaying != NULL) {

		Com_Printf(CON_CHANNEL_CONSOLEONLY, "Loading 1_kej features for a demo..\n");
		std::cout << "Loading 1_kej features for a demo..\n";

		cg::CG_InitHooks();

	}

}
void cg::xCL_PlayDemo(char* name, int isTimeDemo, int a3)
{
	xCL_PlayDemo_f(name, isTimeDemo, a3);

	if (clc.demoplaying != NULL) {

		Com_Printf(CON_CHANNEL_CONSOLEONLY, "Loading 1_kej features for a demo..\n");
		std::cout << "Loading 1_kej features for a demo..\n";

		cg::CG_InitHooks();

	}
}

int cg::GetKeyBinding(const char* command)
{
	unsigned int keyIndex; // ebx
	const char** v1; // esi
	char* key; // eax
	const char* action; // [esp-4h] [ebp-10h]

	keyIndex = 0;
	v1 = (const char**)0x8F1DCC;

	do {
		if (*v1)
		{
			if (**v1)
			{
				char* keystr;
				__asm
				{
					mov eax, keyIndex;
					xor edi, edi;
					mov esi, 0x4677C0;
					call esi;
					mov keystr, eax;
				}
				action = *v1;

				if (!strcmp(command, action))
					return keyIndex;

				//Com_Printf(CON_CHANNEL_OBITUARY, "%s \"%s\"\n", keystr, action);
			}
		}
		v1 += 3;
		++keyIndex;

	} while ((DWORD)v1 < (DWORD)historyEditLines);

	return 0;
}