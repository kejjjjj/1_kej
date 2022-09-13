#include "pch.h"

void Script_OnMenuResponse(int serverId, int menu, const char* response)
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
    else if (!strcmp(menu_name, "cj")) {

        if (!strcmp(response, "save"))
            Script_OnPositionSaved();

        else if (!strcmp(response, "load"))
            Script_OnPositionLoaded();
    }

    //printf("menu[" "%s" "], response[" "%s" "]\n", menu_name, response);
}
void Script_ParseMenuResponse(char* text)
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
    unfixed = unfixed.substr(pos + 1);

    pos = unfixed.find_first_of(' ');
    str = unfixed.substr(0, pos);
    menu = std::stoi(str);

    unfixed = unfixed.substr(pos + 1);
    pos = unfixed.find_last_of('\n');
    str = unfixed.substr(0, pos);
    response = str.c_str();

    Script_OnMenuResponse(sv_serverId, menu, response);

}
__declspec(naked) void Script_ScriptMenuResponse()
{
    const static DWORD fnc = 0x4F8D90;
    const static DWORD retn = 0x54DE5E;
    char* text;
   // itemDef_s* _item;
    __asm
    {
        mov text, eax; //eax holds the va
        //mov edx, _item; //edx holds the itemdef ptr
        //mov edx, [esp + 8];
        //mov _item, edx;
        call fnc;
        pop edi;
        pop esi;
        pop ebx;
        add esp, 0x400;
        // push _item;
        push text;
        call Script_ParseMenuResponse; //call Script_ParseMenuResponse to steal the response
        add esp, 0x4;
        retn;
    }
}
__declspec(naked) void Script_OpenScriptMenu()
{
    const static DWORD fnc = 0x4F8D90;
    const static DWORD retn = 0x46D4D8;
    static char* text{};
    __asm
    {
        mov text, eax;
        add esp, 0x10;
        pop esi;
        pop ebx;
        pop edi;
        xor ecx, ecx;
        pop ebp;
        call fnc;
        push text;
        call Script_ParseMenuResponse;
        add esp, 0x4;
        retn;
    }
}
void Script_OnPositionLoaded()
{
    if (v::mod_jumpanalyzer.isEnabled()) {
        if (cg::jumpanalyzer.hasJumped)
            Com_Printf(CON_CHANNEL_OBITUARY, "^6jump velocity: ^2%i\n", cg::jumpanalyzer.jumpVelocity);
        if (cg::jumpanalyzer.hasBounced)
            Com_Printf(CON_CHANNEL_OBITUARY, "^6bounce velocity: ^2%i\n", cg::jumpanalyzer.bounceVelocity);

        memset(&cg::jumpanalyzer, 0, sizeof(cg::jumpanalyzer_s));
    }
}
void Script_OnPositionSaved()
{
    
}