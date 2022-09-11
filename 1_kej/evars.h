#pragma once

#ifndef __evars
#define __evars

#include "pch.h"

namespace v
{
	namespace cfg
	{
		inline std::string cfgDirectory;
	}

	inline evar_o
		mod_velometer,
		mod_rpg_mode,
		mod_coordinates,
		mod_hitanalyzer,
		mod_bhop,
		mod_bhop_nodelay;

}

#endif