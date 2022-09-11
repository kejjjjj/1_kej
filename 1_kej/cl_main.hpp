#pragma once

#ifndef clmain
#define clmain

#include "pch.h"

namespace cg
{
	typedef void(*CL_Disconnect_h)(int);
	inline CL_Disconnect_h CL_Disconnect_f;
	void CL_Disconnect(int localClientNum);


}

#endif