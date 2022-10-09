#pragma once

#ifndef rworld
#define rworld

#include "pch.h"

namespace r
{
	bool WorldToScreen(vec3_t vWorldLocation, vec2_t xy);

	inline HRESULT (*R_DrawXModelSkinnedCached_h)(cg::GfxCmdBufSourceState* src, cg::GfxCmdBufState* state, cg::GfxModelSkinnedSurface* modelSurf);

	HRESULT  R_DrawXModelSkinnedCached(GfxCmdBufSourceState* src, GfxCmdBufState* state, GfxModelSkinnedSurface* modelSurf);
}


#endif