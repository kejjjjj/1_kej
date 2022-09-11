#pragma once

#ifndef gamefuncs
#define gamefuncs

#include "pch.h"

void iPrintLn(const char* text);
void iPrintLnBold(const char* text);
void SendCommand(const char* command);

inline cg::cmd_function_s cmd_openmenu;
cg::cmd_function_s* Cmd_FindCommand(const char* name);
cg::cmd_function_s* Cmd_AddCommand(char* cmdname, void(__cdecl* function)());
cg::cmd_function_s* Cmd_RemoveCommand(const char* cmdname);

void Cmd_Init();
#endif