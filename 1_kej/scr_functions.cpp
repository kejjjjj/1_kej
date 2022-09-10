#include "pch.h"

#define svs (*((cg::serverStatic_t*)(0x1CBFC80)))

void PlayerCmd_GetButtonPressed(scr_entref_t arg)
{

	int32_t ent(0);
	cg::gentity_s* gent;
	if (HIWORD(arg)) {
		Scr_ObjectError("Not an entity");
		gent = NULL;
	}
	else {
		ent = LOWORD(arg);
		gent = Scr_GetEntity(arg);
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

	int32_t ent(0);
	cg::gentity_s* gent;
	if (HIWORD(arg)) {
		Scr_ObjectError("Not an entity");
		gent = NULL;
	}
	else {
		ent = LOWORD(arg);
		gent = Scr_GetEntity(arg);
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

	int32_t ent(0);
	cg::gentity_s* gent;
	if (HIWORD(arg)) {
		Scr_ObjectError("Not an entity");
		gent = NULL;
	}
	else {
		ent = LOWORD(arg);
		gent = Scr_GetEntity(arg);
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
void PlayerCmd_SetVelocity(scr_entref_t arg)
{

	int32_t ent(0);
	cg::gentity_s* gent;
	vec3_t velocity{};
	if (HIWORD(arg)) {
		Scr_ObjectError("Not an entity");
		gent = NULL;
		return;
	}
	else {
		ent = LOWORD(arg);
		gent = Scr_GetEntity(arg);
		if (!gent->client) {
			Scr_ObjectError("Entity: [%i] is not a player", ent);
			return;
		}
	}
	if (Scr_GetNumParam() != 1)
		Scr_ObjectError("Usage: player setVelocity( vec3 )");

	Scr_GetVector(0, velocity);
	VectorCopy(velocity, gent->client->ps.velocity);
}

void GScr_WorldToScreen(scr_entref_t arg)
{
	if (Scr_GetNumParam() != 1) {
		Scr_ObjectError("Usage: WorldToScreen( end )");
		return;
	}
	vec3_t end;
	vec2_t screen;
	Scr_GetVector(0, end);

	bool success = r::WorldToScreen(end, screen);
	Scr_AddVector(vec3_t{ screen[0], screen[1], (float)success});

}
void GScr_WeaponExists()
{
	if (Scr_GetNumParam() != 1)
		Scr_ObjectError("Usage: weaponExists( string )");

	char* weap = Scr_GetString(0);

	if (!weap) {
		Scr_AddInt(0);
		return;
	}
	int wpIdx = ((int(__cdecl*)(const char*))0x416610)(weap);

	Scr_AddInt(wpIdx > 0);
	

}
void GScr_GetEvarInt()
{
	if (Scr_GetNumParam() != 1)
		Scr_ObjectError("Usage: GetEvarInt( string )");

	char* _evar = Scr_GetString(0);

	evar_o* evar = Evar_FindByName(_evar);

	if (evar) {
		Scr_AddInt(evar->GetInt());
		return;
	}
	Scr_AddInt(0);
}
void GScr_GetEvarFloat()
{
	if (Scr_GetNumParam() != 1)
		Scr_ObjectError("Usage: GetEvarFloat( string )");

	char* _evar = Scr_GetString(0);


	evar_o* evar = Evar_FindByName(_evar);

	if (evar) {
		Scr_AddFloat(evar->GetFloat());
		return;
	}
	Scr_AddFloat(0);
}
void GScr_GetEvar()
{
	if (Scr_GetNumParam() != 1)
		Scr_ObjectError("Usage: GetEvar( string )");

	char* _evar = Scr_GetString(0);


	evar_o* evar = Evar_FindByName(_evar);


	if (evar) {
		char buf[64];

		switch (evar->evar->type) {
		case EVAR_BOOL:
			if (snprintf(buf, sizeof(buf), "%i", evar->isEnabled()) > 0)
				Scr_AddString(buf);
			else Scr_AddString((char*)"");
			break;
		case EVAR_INT:
			if (snprintf(buf, sizeof(buf), "%i", evar->GetInt()) > 0)
				Scr_AddString(buf);
			else Scr_AddString((char*)"");
			break;
		case EVAR_FLOAT:
			if (snprintf(buf, sizeof(buf), "%f", evar->GetFloat()) > 0)
				Scr_AddString(buf);
			else Scr_AddString((char*)"");
			break;

		case EVAR_STRING:
			if (snprintf(buf, sizeof(buf), "%s", evar->GetString()) > 0) {
				Scr_AddString(buf);
			}
			else Scr_AddString((char*)"");
			break;
		default:
			Scr_AddString((char*)"");
			break;
		}
	
		return;
	}
	Scr_AddString((char*)"");
}
void GScr_WriteToAddress()
{
	if (Scr_GetNumParam() != 3)
		Scr_ObjectError("Usage: WriteToAddress( address, bytes, length )");

	char* addr_str = Scr_GetString(0);
	char* bytes = Scr_GetString(1);
	int length = Scr_GetInt(2);

	if (length < 0) {
		Scr_ObjectError("write length (%i) must be greater than 0", length);
		return;
	} else if(sizeof(addr_str) < 0) {
		Scr_ObjectError("invalid address");
		return;
	}else if (sizeof(bytes) < 0) {
		Scr_ObjectError("invalid amount of bytes to write");
		return;
	}
	if (addr_str[0] != '0' || addr_str[1] != 'x') {
		Scr_ObjectError("invalid address format, (missing 0x)");
		return;
	}
	const DWORD destination = std::stoul(addr_str, nullptr, 16);

	if (!destination) {
		Scr_ObjectError("invalid address");
		return;
	}
	BYTE* fixed_bytes = new BYTE[length];
	int byte;
	for (BYTE i = 0; i < length; i++) {
		std::string combined;
		std::stringstream ss;

		combined.push_back(*(BYTE*)(bytes));
		combined.push_back(*(BYTE*)(bytes+1));

		ss << combined;
		ss >> std::hex >> byte;

		fixed_bytes[i] = (BYTE)(byte);

		
		bytes += 3;
	}

	hook* a = nullptr;
	a->write_addr(destination, (char*)fixed_bytes, length);

	delete[] fixed_bytes;
}
void Gscr_GetAddressInt()
{
	if (Scr_GetNumParam() != 1)
		Scr_ObjectError("Usage: GetAddressInt( address <as a string> )");

	char* addr_str = Scr_GetString(0);

	if (sizeof(addr_str) < 0) {
		Scr_ObjectError("invalid address");
		Scr_AddInt(0);
		return;
	}

	const DWORD destination = std::stoul(addr_str, nullptr, 16);

	if (!destination) {
		Scr_ObjectError("invalid address");
		Scr_AddInt(0);
		return;
	}

	if (&destination == nullptr) {
		Scr_ObjectError("attempted to read null memory");
		Scr_AddInt(0);
		return;
	}

	Scr_AddInt(*(int*)destination);

}
void Gscr_GetAddressFloat()
{
	if (Scr_GetNumParam() != 1)
		Scr_ObjectError("Usage: GetAddressFloat( address <as a string> )");

	char* addr_str = Scr_GetString(0);

	if (sizeof(addr_str) < 0) {
		Scr_ObjectError("invalid address");
		Scr_AddFloat(0);
		return;
	}

	const DWORD destination = std::stoul(addr_str, nullptr, 16);

	if (!destination) {
		Scr_ObjectError("invalid address");
		Scr_AddFloat(0);
		return;
	}

	if (&destination == nullptr) {
		Scr_ObjectError("attempted to read null memory");
		Scr_AddFloat(0);
		return;
	}

	Scr_AddFloat(*(float*)destination);

}
void GScr_SendCommand()
{
	if (Scr_GetNumParam() != 1) {
		Scr_ObjectError("Usage: SendCommand( string )");
		return;
	}
	char* str = Scr_GetString(0);

	if (str) {
		SendCommand(str);
	}
}
void Scr_LoadMethods()
{
	Scr_AddMethod("getbuttonpressed",	(xfunction_t)PlayerCmd_GetButtonPressed, false);
	Scr_AddMethod("getforwardmove",		(xfunction_t)PlayerCmd_GetForwardMove, false);
	Scr_AddMethod("getrightmove",		(xfunction_t)PlayerCmd_GetRightMove, false);
	Scr_AddMethod("setvelocity",		(xfunction_t)PlayerCmd_SetVelocity, false);

	Scr_AddFunction("weaponexists",		(xfunction_t)GScr_WeaponExists, false);
	Scr_AddFunction("worldtoscreen",	(xfunction_t)GScr_WorldToScreen, false);
	Scr_AddFunction("getevarint",		(xfunction_t)GScr_GetEvarInt, false);
	Scr_AddFunction("getevarfloat",		(xfunction_t)GScr_GetEvarFloat, false);
	Scr_AddFunction("getevar",			(xfunction_t)GScr_GetEvar, false);
	Scr_AddFunction("writetoaddress",	(xfunction_t)GScr_WriteToAddress, false);
	Scr_AddFunction("getaddressint",	(xfunction_t)Gscr_GetAddressInt, false);
	Scr_AddFunction("getaddressfloat",  (xfunction_t)Gscr_GetAddressFloat, false);

	Scr_AddFunction("sendcommand",		(xfunction_t)GScr_SendCommand, false);


}
xfunction_t Scr_GetFunction(const char** name, int* type)
{
	xfunction_t a = (xfunction_t)Scr_GetFunction_f(name, type);
	cg::scr_function_s* cmd = scr_functions;

	if (a)
		return a;

	else {
		if (!cmd)
			return 0;
		while (strcmp(*name, cmd->name)) {
			cmd = cmd->next;
			if (!cmd)
				return 0;

		}
		a = (xfunction_t)cmd->function;
		*name = cmd->name;
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "^5Adding function: %s\n", cmd->name);

	}
	return a;
}
xmethod_t Player_GetMethod(const char** name)
{
	xmethod_t a = (xmethod_t)Player_GetMethod_f(name);
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