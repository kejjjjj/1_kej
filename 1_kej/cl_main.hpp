#pragma once

#ifndef clmain
#define clmain

#include "pch.h"

namespace cg
{
	inline void(*CL_Disconnect_f)(int);
	void CL_Disconnect(int localClientNum);


}

#endif