
#include "pch.h"

DWORD Sys_MilliSeconds()
{
	return timeGetTime() - *(DWORD*)0xCC18C84; //sys_basetime
}
