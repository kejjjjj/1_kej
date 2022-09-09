#include "pch.h"

dvar_s* Dvar_FindMalleableVar(const char* name)
{

    DWORD addr = 0x56b5d0;
    __asm
    {
        mov edi, name
        call[addr]
    }

   // return ((dvar_s * (__cdecl*)(const char* name))0x56B5D0)(name);

}
dvar_s* Dvar_RegisterNew(const char* name, dvar_type type, int flags, const char* description, DvarValue defaultValue, DvarLimits domain)
{
    dvar_s* dvar = Dvar_FindMalleableVar(name);

    if (dvar) {
        Com_Printf(CON_CHANNEL_CONSOLEONLY, "dvar (%s) already exists\n", name);
        return Dvar_Reregister(dvar, name, type, flags, description, defaultValue, domain);
    }

   return ((dvar_s * (__cdecl*)(const char*, dvar_type, int, const char*, DvarValue, DvarLimits))0x56C130)(name, type, flags, description, defaultValue, domain);
}
dvar_s* Dvar_Reregister(dvar_s* dvar, const char* _name, dvar_type _type, int flags, const char* description, DvarValue defaultValue, DvarLimits domain)
{
  return ((dvar_s * (__fastcall*)(dvar_s*, const char*, dvar_type, int, const char*, DvarValue, DvarLimits))0x56BFF0)(dvar, _name, _type, flags, description, defaultValue, domain);

}
dvar_s* Dvar_RegisterEnum(const char* dvarName, int defaultIdx, int flags, const char* description, DvarLimits strings)
{
    return ((dvar_s * (__cdecl*)(const char* dvarName, int defaultIdx, int flags, const char* description, DvarLimits strings))0x56C600)(dvarName, defaultIdx, flags, description, strings);

}
void Dvar_Init()
{
    //DvarValue val{};
    //DvarLimits lim{};

    //val.integer = 1;
    //val.enabled = 1;
    //val.string = "deserteaglegold_mp";
    //val.vector[0] = 0;
    //val.vector[1] = 0;
    //val.vector[2] = 0;
    //val.vector[3] = 0;
    //val.value = 0;

    //lim.integer.max = 5;
    //lim.integer.min = 0;
    //


    //Dvar_RegisterNew("1_kej_rpgtype", dvar_type::integer, dvar_flags::saved, "preferred rpg mode\n0. default\n1. sustain", val, lim);
    //Dvar_RegisterNew("1_kej_spawnweapon", dvar_type::string, dvar_flags::saved, "weapon given after spawning", val, lim);

}