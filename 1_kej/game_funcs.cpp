#include "pch.h"

void iPrintLn(const char* text)
{
    __asm
    {

        push text
        push 0 //int localClientNum
        mov esi, 0x43dda0
        call esi
        add esp, 0x8
    }
}
void iPrintLnBold(const char* text)
{
    __asm
    {
        push text
        push 0 //int localClientNum
        mov esi, 0x43de00
        call esi
        add esp, 0x8
    }
}
void SendCommand(const char* command)
{
    __asm
    {
        push    command
        push    0
        push    0
        mov     esi, 0x004F9AB0
        call    esi
        add     esp, 0x0C
    }
}
cg::cmd_function_s* Cmd_FindCommand(const char* name)
{
    static const DWORD fnc = 0x4F9950;
    __asm
    {
        mov esi, name;
        call fnc;
    }
}
cg::cmd_function_s* Cmd_AddCommand(char* cmdname, void(__cdecl* function)())
{
    if(cod4x_entry)
        return ((cmd_function_s*(__cdecl*)(char* cmd, void* function))Cmd_AddCommand_fnc)(cmdname, function);

    cmd_function_s* cmd = Cmd_FindCommand(cmdname);
    printf("adding __a new func command: %s\n", cmdname);

    if (cmd)
        return cmd;

    printf("adding a new func command: %s\n", cmdname);


    static cmd_function_s _cmd{};

    __asm {
        push function;
        mov edi, offset _cmd;
        mov eax, cmdname;
        mov esi, 0x4F99A0;
        call esi;
        add esp, 4;
    }

    return cmd_functions;
}
cg::cmd_function_s* Cmd_RemoveCommand(const char* cmdname)
{
    __asm
    {
        push cmdname;
        mov esi, 0x4F99E0;
        call esi;
        add esp, 0x4;
    }


}
void OpenMenu_f()
{

    r::should_draw_menu = !r::should_draw_menu;
    if(r::should_draw_menu)
        Com_Printf(CON_CHANNEL_CONSOLEONLY, "^2opening the menu\n");
    else 
        Com_Printf(CON_CHANNEL_CONSOLEONLY, "^1closing the menu\n");

    r::R_RemoveInput(r::should_draw_menu);
}
void Cmd_Init()
{
    std::cout << "calling Cmd_Init()\n";
    Cmd_AddCommand((char*)"1_kej_openmenu", OpenMenu_f);

}