#include "pch.h"


Material* r::R_RegisterMaterial(const char* fontname)
{
	return ((Material * (*)(const char* fontname, int size))0x5F2A80)(fontname, sizeof(fontname));

}
Font_s* r::R_RegisterFont(const char* fontname)
{
	return ((Font_s * (*)(const char* fontname, int size))0x5F1EC0)(fontname, sizeof(fontname));
}
char* __cdecl r::R_AddCmdDrawText(const char* text, int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style)
{
	const static uint32_t R_AddCmdDrawText_func = 0x5F6B00;
	__asm
	{
		push	style;
		sub     esp, 14h;
		fld		rotation;
		fstp[esp + 10h];
		fld		yScale;
		fstp[esp + 0Ch];
		fld		xScale;
		fstp[esp + 8];
		fld		y;
		fstp[esp + 4];
		fld		x;
		fstp[esp];
		push	font;
		push	maxChars;
		push	text;
		mov		ecx, [color];
		call	R_AddCmdDrawText_func;
		add		esp, 24h;
	}
}
void r::R_DrawText(const char* text, const char* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style)
{

	Font_s* _font = R_RegisterFont(font);

	R_AddCmdDrawText(text, 0x7FFFFFFF, _font, X(x), Y(y), xScale, yScale, rotation, color, style);

}
void r::R_DrawText(const char* text, float x, float y, float xScale, float yScale, float rotation, float* color, int style)
{
	R_DrawText(text, "fonts/smalldevfont", x, y, xScale, yScale, rotation, color, style);
}

float r::X(float pos)
{
	const float x = cgs->refdef.width;
	return pos <= 1920 ? pos / (1920.f / x) : pos * (x / 1920);

}
float r::Y(float pos)
{
	const float y = cgs->refdef.height;
	return pos <= 1080 ? pos / (1080.f / y) : pos * (y / 1080);
}