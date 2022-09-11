#pragma once

#ifndef ccmds
#define ccmds

#include "pch.h"

namespace cg
{
	typedef void(*SV_Map_h)(char*);
	inline SV_Map_h SV_Map_f;
	void SV_Map(char* a1);
}

#endif