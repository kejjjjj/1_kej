#pragma once

#ifndef clmain
#define clmain

#include "pch.h"

namespace cg
{
	inline void(*CL_Disconnect_f)(int);
	void CL_Disconnect(int localClientNum);
	
	inline DWORD CL_PlayDemo_Addr;
	inline void (*CL_PlayDemo_f)();
	void CL_PlayDemo();
	void xCL_PlayDemo(char* name, int isTimeDemo, int a3);
	inline void(*xCL_PlayDemo_f)(char* name, int isTimeDemo, int a3);

	int GetKeyBinding(const char* command);
}

#endif