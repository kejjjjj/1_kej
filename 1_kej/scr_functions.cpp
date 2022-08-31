#include "pch.h"

#define svs (*((cg::serverStatic_t*)(0x1CBFC80)))

void PlayerCmd_JumpButtonPressed(scr_entref_t arg)
{
	if (NOT_SERVER)
		return;

	int32_t ent(0);
	cg::gentity_s* gent;
	if (HIWORD(arg)) {
		Scr_ObjectError("Not an entity");
		gent = NULL;
	}
	else {
		ent = LOWORD(arg);
		gent = &cg::gent[ent];
		if (!gent->client) {
			Scr_ObjectError("Entity: [%i] is not a player", ent);
		}
	}
	if (Scr_GetNumParam() > 0)
		Scr_ObjectError("Usage: entity JumpButtonPressed()");

	const cg::client_t* cl = &svs.clients[ent];
	if (!cl || !gent) {
		Scr_ObjectError("Entity: [%i] is not a player", ent);
		return;
	}
	Scr_AddInt((cl->lastUsercmd.buttons & 1024) == true);
}

void Scr_LoadMethods()
{
	Scr_AddMethod("jumpbuttonpressed", (xfunction_t)PlayerCmd_JumpButtonPressed, false);
}
xmethod_t Player_GetMethod(const char** name)
{
	static cg::scr_function_s* cmd = scr_methods;
	static bool once = true;
	xmethod_t a = (xmethod_t)Player_GetMethod_f(name);

	if (!a) {
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "Player_GetMethod: %s is not a valid method\n", *name);

	}
	else {
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2Player_GetMethod: %s is a valid method\n", *name);

		if (!cmd || !once)
			return NULL;
		once = false;
		a = (xmethod_t)Scr_GetMethod(&cmd->name);
		if (a) {
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "^5Player_GetMethod: %s is a valid method\n", cmd->name);
			//cmd = cmd->next;


		}
	}
	return a;
}