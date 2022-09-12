#pragma once

#ifndef scrcmd
#define scrcmd

typedef int scr_entref_t;
typedef void (*xfunction_t)();
inline cg::scr_function_s* scr_functions = NULL;
inline cg::scr_function_s* scr_methods = NULL;

bool Scr_AddMethod(const char* cmd_name, xfunction_t function, bool developer);
bool Scr_AddFunction(const char* cmd_name, xfunction_t function, bool developer);
xfunction_t Scr_GetMethod(char** v_functionName);

inline void (*stub)();

void Script_ScriptMenuResponse();
void Script_ParseMenuResponse(char* text, cg::itemDef_s* item);
void Script_OnMenuResponse(int serverId, int menu, const char* response, cg::itemDef_s* item);

#endif