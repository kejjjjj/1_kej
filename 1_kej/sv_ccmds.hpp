#pragma once

#ifndef ccmds
#define ccmds

#include "pch.h"

namespace cg
{
	inline void(*SV_Map_f)();
	void SV_Map();

	void Mod_EditMemory(bool forceDisable);
}

#endif