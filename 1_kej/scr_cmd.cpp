
#include "pch.h"


#pragma warning (disable : 4996)

bool Scr_AddFunction(const char* cmd_name, xfunction_t function, bool developer) {

    cg::scr_function_s* cmd;

    for (cmd = scr_functions; cmd; cmd = cmd->next) {
        if (!strcmp(cmd_name, cmd->name)) {
            if (function != NULL) {
                Com_PrintWarning(CON_CHANNEL_CONSOLEONLY, "Scr_AddFunction: %s already defined\n", cmd_name);
            }
            return false;
        }
    }

    cmd = (cg::scr_function_s*)malloc(sizeof(cg::scr_function_s) + strlen(cmd_name) + 1);

    if (!cmd) {
        Com_PrintError(CON_CHANNEL_CONSOLEONLY, "Scr_AddFunction: %s failed to allocate memory\n", cmd_name);
        return false;
    }

    strcpy((char*)(cmd + 1), cmd_name);
    cmd->name = (char*)(cmd + 1);
    cmd->function = function;
    cmd->developer = developer;
    cmd->next = scr_functions;
    scr_functions = cmd;
    return true;
}

bool Scr_AddMethod(const char* cmd_name, xfunction_t function, bool developer)
{
    cg::scr_function_s* cmd;

    for (cmd = scr_methods; cmd; cmd = cmd->next) {
        if (!strcmp(cmd_name, cmd->name)) {
            if (function != NULL) {
                Com_PrintWarning(CON_CHANNEL_CONSOLEONLY, "Scr_AddMethod: %s already defined\n", cmd_name);
            }
            return false;
        }
    }
    cmd = (cg::scr_function_s*)malloc(sizeof(cg::scr_function_s) + strlen(cmd_name) + 1);

    if (!cmd) {
        Com_PrintError(CON_CHANNEL_CONSOLEONLY, "Scr_AddMethod: %s failed to allocate memory\n", cmd_name);
        return false;
    }
    strcpy((char*)(cmd + 1), cmd_name);
    cmd->name = (char*)(cmd + 1);
    cmd->function = function;
    cmd->developer = developer;
    cmd->next = scr_methods;
    scr_methods = cmd;
    return true;
}
xfunction_t Scr_GetMethod(char** v_functionName)
{
    cg::scr_function_s* cmd;

    for (cmd = scr_methods; cmd != NULL; cmd = cmd->next) {
        if (!stricmp(*v_functionName, cmd->name)) {
            *v_functionName = cmd->name;
            return cmd->function;
        }
    }
    return NULL;
}