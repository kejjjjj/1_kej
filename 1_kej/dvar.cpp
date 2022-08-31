#include "pch.h"

dvar_s* Dvar_FindMalleableVar(const char* name)
{
    return ((dvar_s * (__cdecl*)(const char* name))0x56B5D0)(name);

}
dvar_s* Dvar_RegisterNew(const char* name, DvarType type, int flags, const char* description, DvarValue defaultValue, DvarLimits domain)
{
    dvar_s* dvar = Dvar_FindMalleableVar(name);

    if (dvar) {
        Com_Printf(CON_CHANNEL_CONSOLEONLY, "dvar (%s) already exists\n", name);
        return Dvar_Reregister(dvar, name, type, flags, description, defaultValue, domain);
    }

   return ((dvar_s * (__cdecl*)(const char*, DvarType, int, const char*, DvarValue, DvarLimits))0x56C130)(name, type, flags, description, defaultValue, domain);
}
dvar_s* Dvar_Reregister(dvar_s* dvar, const char* name, DvarType type, int flags, const char* description, DvarValue defaultValue, DvarLimits domain)
{
    return ((dvar_s * (__fastcall*)(dvar_s*, int, const char*, DvarType, const char*, DvarValue, DvarLimits))0x56BFF0)(dvar, flags, name, type, description, defaultValue, domain);
}
