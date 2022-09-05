#include "pch.h"

#define svs (*((cg::serverStatic_t*)(0x1CBFC80)))

void PlayerCmd_GetButtonPressed(scr_entref_t arg)
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
		Scr_ObjectError("Usage: player GetButtonPressed()");

	//const cg::client_t* cl = &svs.clients[ent];
	//if (!cl || !gent) {
	//	Scr_ObjectError("Entity: [%i] is not a player", ent);
	//	return;
	//}
	const cg::usercmd_s* cmd = cg::cinput->GetUserCmd(cg::cinput->currentCmdNum - 1);

	if (!cmd) {
		Scr_AddInt(0);
		return;
	}
	Scr_AddInt(cmd->buttons);
}
void PlayerCmd_GetForwardMove(scr_entref_t arg)
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
		Scr_ObjectError("Usage: player GetForwardMove()");

	const cg::usercmd_s* cmd = cg::cinput->GetUserCmd(cg::cinput->currentCmdNum - 1);

	if (!cmd) {
		Scr_AddInt(0);
		return;
	}

	Scr_AddInt(cmd->forwardmove);
}
void PlayerCmd_GetRightMove(scr_entref_t arg)
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
		Scr_ObjectError("Usage: player GetRightMove()");

	const cg::usercmd_s* cmd = cg::cinput->GetUserCmd(cg::cinput->currentCmdNum - 1);

	if (!cmd) {
		Scr_AddInt(0);
		return;
	}

	Scr_AddInt(cmd->rightmove);
}
void Scr_LoadMethods()
{
	Scr_AddMethod("getbuttonpressed", (xfunction_t)PlayerCmd_GetButtonPressed, false);
	Scr_AddMethod("getforwardmove", (xfunction_t)PlayerCmd_GetForwardMove, false);
	Scr_AddMethod("getrightmove", (xfunction_t)PlayerCmd_GetRightMove, false);

}
xmethod_t Player_GetMethod(const char** name)
{
	static bool once = true;
	xmethod_t a = (xmethod_t)Player_GetMethod_f(name);
	int32_t i = 0;
	cg::scr_function_s* cmd = scr_methods;

	if (a)
		return a;

	else
	{
		if (!cmd)
			return 0;
		while (strcmp(*name, cmd->name)) {
			cmd = cmd->next;
			if (!cmd)
				return 0;
			
		}
		a = (xmethod_t)cmd->function;
		*name = cmd->name;
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2Adding method: %s\n", cmd->name);
	}
	return a;
}