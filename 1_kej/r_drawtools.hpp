#pragma once

#ifndef drawtools
#define drawtools

#include "pch.h"


using namespace cg;
namespace r
{
	Material* R_RegisterMaterial(const char* fontname);
	Font_s* R_RegisterFont(const char* fontname);

	void CG_AdjustFrom640(float& x, float& y, float& w, float& h);

	char* __cdecl R_AddCmdDrawText(const char* text, int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style);
	void R_AddCmdDrawStretchPic(Material* material, float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float* color);
	void R_DrawRect(const char* material, float x, float y, float w, float h, const float* color);
	void R_DrawText(const char* text, const char* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style);
	void R_DrawText(const char* text, float x, float y, float xScale, float yScale, float rotation, float* color, int style);

	float X(float pos);
	float Y(float pos);

	void MetricsHelpMarker(const char* desc);
}

#endif