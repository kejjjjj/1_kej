// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

static bool hooked = false;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!hooked) {
            std::thread(cg::CG_DllEntry, hModule, (LPTHREAD_START_ROUTINE)cg::CG_DllEntry).detach();
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



void cg::CG_DllEntry(HMODULE hModule, LPTHREAD_START_ROUTINE startAddr)
{
    if (!(DWORD)GetModuleHandleA("iw3mp.exe")) {
        return;
    }

    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    while (!cgs && &cg::dx->device == nullptr) {
        std::this_thread::sleep_for(100ms);
    }
    std::this_thread::sleep_for(3s);

    CG_Init();
}