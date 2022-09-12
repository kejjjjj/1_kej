
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
void Script_OnMenuResponse(int serverId, int menu, const char* response, cg::itemDef_s* item)
{
    //this is the equivelant to .gsc waittill("menuresponse", menu, response)

    const auto getMenuName = [](int _menu) -> char* {
        int* stringoffs = &cg::clients->gameState.stringOffsets[1970];
        return &clients->gameState.stringData[*(stringoffs + _menu)];
    };

    char* menu_name = getMenuName(menu);

    const bool allies = !strcmp(response, "allies");
    const bool axis = !strcmp(response, "axis");
    const bool autoassign = !strcmp(response, "autoassign");

    const bool team_marinesopfor = !strcmp(menu_name, "team_marinesopfor");

    if ((team_marinesopfor) && (allies || axis || autoassign)) {

        Cbuf_AddText(";wait; openscriptmenu changeclass specops_mp,0\n", cgs->clientNum);
        Cbuf_AddText(";wait; openscriptmenu changeclass specops_mp,0\n", cgs->clientNum);

    }

    printf("menu[" "%s" "], response[" "%s" "]\n", menu_name, response);
}
void Script_ParseMenuResponse(char* text, cg::itemDef_s* item)
{
    std::string unfixed = text;
    int sv_serverId;
    int menu;
    const char* response;

    //skip first 7 chars
    unfixed = unfixed.substr(7);

    size_t pos = unfixed.find_first_of(' ');
    std::string str = unfixed.substr(0, pos);

    sv_serverId = std::stoi(str);
    unfixed = unfixed.substr(pos+1);

    pos = unfixed.find_first_of(' ');
    str = unfixed.substr(0, pos);
    menu = std::stoi(str);

    unfixed = unfixed.substr(pos + 1);
    pos = unfixed.find_last_of('\n');
    str = unfixed.substr(0, pos);
    response = str.c_str();

    Script_OnMenuResponse(sv_serverId, menu, response, item);

}
__declspec(naked) void Script_ScriptMenuResponse()
{
    const static DWORD fnc = 0x4F8D90;
    const static DWORD retn = 0x54DE5E;
    char* text;
    itemDef_s* _item;
    __asm
    {
        mov text, eax; //eax holds the va
        mov edx, _item;
        mov edx, [esp + 8];
        mov _item, edx;
        call fnc;
        pop edi;
        pop esi;
        pop ebx;
        add esp, 0x400;
        push _item;
        push text;
        call Script_ParseMenuResponse; //call Script_ParseMenuResponse to steal the response
        add esp, 0x8;
        retn;
    }



}