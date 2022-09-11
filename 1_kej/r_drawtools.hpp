#pragma once

#ifndef drawtools
#define drawtools

#include "pch.h"


using namespace cg;
namespace r
{
	Material* R_RegisterMaterial(const char* fontname);
	Font_s* R_RegisterFont(const char* fontname);

	char* __cdecl R_AddCmdDrawText(const char* text, int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style);
	void R_DrawText(const char* text, const char* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style);
	void R_DrawText(const char* text, float x, float y, float xScale, float yScale, float rotation, float* color, int style);

	float X(float pos);
	float Y(float pos);

	void MetricsHelpMarker(const char* desc);
}

#endif