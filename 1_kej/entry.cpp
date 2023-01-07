// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"


typedef int(*WinMainCRTStartup_h)();
WinMainCRTStartup_h WinMainCRTStartup_f;

void _init();

int dll_init()
{
    _init();

    hook a;
    a.remove(&(PVOID&)WinMainCRTStartup_f, dll_init);
    //a.write_addr(0x67493C, "\xE8\x48\xA8\x00\x00\xE9\x16\xFE\xFF\xFF", 10);
    __asm
    {
        mov eax, 0x67493C;
        jmp eax;
    }

}
bool hooked = false;
FILE* _con;
void _init()
{

    if (hooked)
        return;

    //AllocConsole();
    //freopen_s(&_con, "CONOUT$", "w", stdout);

    std::thread(cg::CG_DllEntry).detach();
    std::cout << "requesting to inject\n";
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        DisableThreadLibraryCalls(hModule);

        if (!hooked) {
            DWORD oldProtect;
            VirtualProtect(GetModuleHandle(nullptr), 0xD536000, PAGE_EXECUTE_READWRITE, &oldProtect);
            //hook* a = nullptr;
            WinMainCRTStartup_f = (WinMainCRTStartup_h)(0x67493C);

            //a->install(&(PVOID&)WinMainCRTStartup_f, dll_init);
            _init();
            //__asm {
            //    mov esi, _init;
            //    call esi;
            //    //add esp, 0;
            //}
            hooked = true;
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        
        //if (lpReserved != nullptr)
        //{
        //    break;
        //}
        //if (_con) {
        //    fclose(_con);
        //    FreeConsole();
        //}
        //MessageBoxA(NULL, "DLL_PROCESS_DETACH", "DLL_PROCESS_DETACH", 0);
        break;
    }
    return TRUE;
}

void cg::CG_DllEntry()
{
    const DWORD iw3mp = (DWORD)GetModuleHandleA("iw3mp.exe");
    const DWORD iw3x = (DWORD)GetModuleHandleA("iw3x.dll");

    if (!iw3mp && !iw3x) {
        return;
    }

    while (!cgs || !cg::dx->device) {
        std::this_thread::sleep_for(100ms);
    }
   // std::this_thread::sleep_for(1s);
    fs::Log_Create(fs::GetExePath() + "\\1_kej_log.txt");

    if (iw3x)
        Com_PrintWarning(CON_CHANNEL_CONSOLEONLY, "iw3xo detected; expect undefined behavior..\n");

    CG_Init();

    bool monitoring = true;

    while (monitoring) {

        if (!monitoring)
            break;

        const dvar_s* fs_game = Dvar_FindMalleableVar("fs_game");
        dvar_s* g_gametype = Dvar_FindMalleableVar("g_gametype");
        if (fs_game) {
            mglobs.isUsing = (!strcmp(fs_game->current.string, "mods/1_kej_v2"));
            if (mglobs.isUsing && ((strcmp(g_gametype->current.string, "cj")) || strcmp(g_gametype->latched.string, "cj")) && clientUI[0].connectionState == CA_DISCONNECTED) {
                g_gametype->current.string = "cj";
                g_gametype->latched.string = "cj";
                Com_PrintWarning(CON_CHANNEL_CONSOLEONLY, "1_kej_v2 is loaded, but the gametype is wrong.. changing gametype to cj\n");
            }
        }

        Sleep(500);
    }

}