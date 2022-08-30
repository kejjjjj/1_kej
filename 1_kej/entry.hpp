#pragma once

#ifndef entryp
#define entryp

#include "pch.h"

namespace cg {

	void CG_DllEntry(HMODULE hModule, LPTHREAD_START_ROUTINE startAddr);

}
#endif