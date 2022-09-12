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

    AllocConsole();
    freopen_s(&_con, "CONOUT$", "w", stdout);

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

            __asm {
                mov esi, _init;
                call esi;
                //add esp, 0;
            }
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