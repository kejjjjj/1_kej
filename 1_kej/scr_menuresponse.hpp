#pragma once

#ifndef menuresp
#define menuresp

#include "pch.h"

inline void (*stub)(), (*stub2)();

void Script_OpenScriptMenu();
void Script_ScriptMenuResponse();
void Script_ParseMenuResponse(char* text);
void Script_OnMenuResponse(int serverId, int menu, const char* response);

void Script_OnPositionLoaded();
void Script_OnPositionSaved();


#endif