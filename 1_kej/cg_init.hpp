#pragma once

#ifndef __cod4x
#define __cod4x

#include "pch.h"

namespace cg
{
	struct mod_globs {
		bool initialized;
		bool isUsing;

	};

	void cod4x();
	void CG_Init();
	void CG_InitHooks();
	void CG_InitForeverHooks();
	void CG_PrepareHooks();
	void CG_RemoveHooks();

	inline mod_globs mglobs;
}

#endif