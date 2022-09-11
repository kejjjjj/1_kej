// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"


typedef int(*WinMainCRTStartup_h)();
WinMainCRTStartup_h WinMainCRTStartup_f;

void _init();

__declspec(naked) void dll_init()
{

    __asm
    {
        call    _init;
        mov		eax, 0x67493C;
        jmp		eax;
    }
}

void _init()
{
    static bool once = true;
    if (once) {
        AllocConsole();
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);

        std::thread(cg::CG_DllEntry).detach();


        hook a;
        a.remove(&(PVOID&)WinMainCRTStartup_f, dll_init);
        a.write_addr(0x67493C, "E8 48 A8 00 00 E9 16 FE FF FF", 10);
    }
    std::cout << "requesting to inject\n";
    once = false;
}


static bool hooked = false;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!hooked) {
            hook* a = nullptr;
            WinMainCRTStartup_f = (WinMainCRTStartup_h)(0x67493C);
            a->install(&(PVOID&)WinMainCRTStartup_f, dll_init);
            __asm {
                mov esi, 0x67493C;
                call esi;
            }
            hooked = true;
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void cg::CG_DllEntry()
{
    if (!(DWORD)GetModuleHandleA("iw3mp.exe")) {
        return;
    }


    while (!cgs || !cg::dx->device) {
        std::this_thread::sleep_for(100ms);
    }
   // std::this_thread::sleep_for(1s);

    CG_Init();

    bool monitoring = true;

    while (monitoring) {

        if (!monitoring)
            break;

        dvar_s* fs_game = Dvar_FindMalleableVar("fs_game");

        if (fs_game) {
            mglobs.isUsing = (!strcmp(fs_game->current.string, "mods/1_kej_v2"));

        }

        Sleep(1000);
    }

}