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
    static bool hasColls = true;

    if ((team_marinesopfor) && (allies || axis || autoassign)) {

        Cbuf_AddText(";wait; openscriptmenu changeclass specops_mp,0\n", cgs->clientNum);
        Cbuf_AddText(";wait; openscriptmenu changeclass specops_mp,0\n", cgs->clientNum);

        if (cworld.terrain.clip_points.empty()) {
            CMod_GetAllTerrainClips();
            Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2All tool textures fetched\n");
        }

    }
    else if (!strcmp(menu_name, "cj")) {

        if (!strcmp(response, "save"))
            Script_OnPositionSaved();

        else if (!strcmp(response, "load"))
            Script_OnPositionLoaded();

        else if (!strcmp(response, "record")) {
            analyzer.SetRecordingMode(!analyzer.InRecordingMode());
            Com_Printf(CON_CHANNEL_OBITUARY, "Recording mode %s\n", analyzer.InRecordingMode() == true ? "^2enabled" : "^1disabled");

            if (!analyzer.InRecordingMode() && analyzer.isRecording())
                analyzer.StopRecording();

        }
        else if (!strcmp(response, "autoslide")) {
            automation.keybindPressed = true;
        }
        else if (!strcmp(response, "segment"))
            analyzer.OnStartSegment();

        else if (!strcmp(response, "500fps"))
            Mod_A_OnCreate500FPS();

        else if (!strcmp(response, "bounce_calc"))
            Mod_BounceCalculator_Create();

        else if (!strcmp(response, "toggle_collisions")) {
            hook* a = 0;
            if (hasColls)
                a->nop(0x4F4C8E);
            else
                a->write_addr(0x4F4C8E, "\xE8\x1D\xF4\xFF\xFF", 5);
            hasColls = !hasColls;
        }

    }

    //printf("menu[" "%s" "], response[" "%s" "]\n", menu_name, response);
}
void Script_ParseMenuResponse(char* text) //this will always be the same format so hardcoding everything should not cause issues
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


    }
    if (analyzer.isSegmenting()) {
       // Com_Printf(CON_CHANNEL_OBITUARY, "segment frames: [%i]\n", analyzer.segData.size());

        //analyzer.segData.erase(analyzer.segData.begin(), analyzer.segData.end());
        //analyzer.segData.clear();
        //analyzer.segData.resize(0);

    }
    analyzer.StopRecording();
    analyzer.OnEndSegment();

    memset(&cg::jumpanalyzer, 0, sizeof(cg::jumpanalyzer_s));

    memset(&automation, 0, sizeof(automation_s));

}
void Script_OnPositionSaved()
{
    analyzer.StopRecording();
    analyzer.OnEndSegment();

}