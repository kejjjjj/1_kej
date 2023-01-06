#include "pch.h"

void r::CG_AdjustFrom640(float& x, float& y, float& w, float& h)
{
	const float scale = (float)cgs->refdef.width / 640.f;

	x *= scale;
	y *= scale;
	w *= scale;
	h *= scale;
}
Material* r::R_RegisterMaterial(const char* mtl)
{
	return ((Material * (*)(const char* mtl, int size))0x5F2A80)(mtl, sizeof(mtl));

}
Font_s* r::R_RegisterFont(const char* fontname)
{
	return ((Font_s * (*)(const char* fontname, int size))0x5F1EC0)(fontname, sizeof(fontname));
}
void r::R_DrawRect(const char* material, float x, float y, float w, float h, const float* color)
{
	//CG_AdjustFrom640(x, y, w, h);
	Material* mat = R_RegisterMaterial(material);
	R_AddCmdDrawStretchPic(mat, X(x), Y(y), X(w), Y(h), 0, 0, 0, 0, color);


}
void r::R_AddCmdDrawStretchPic(Material* material, float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float* color)
{
	const static uint32_t R_AddCmdDrawStretchPic_func = 0x5F65F0;
	__asm
	{
		pushad;
		push	color;
		mov		eax, [material];
		sub		esp, 20h;
		fld		t1;
		fstp[esp + 1Ch];
		fld		s1;
		fstp[esp + 18h];
		fld		t0;
		fstp[esp + 14h];
		fld		s0;
		fstp[esp + 10h];
		fld		h;
		fstp[esp + 0Ch];
		fld		w;
		fstp[esp + 8h];
		fld		y;
		fstp[esp + 4h];
		fld		x;
		fstp[esp];
		call	R_AddCmdDrawStretchPic_func;
		add		esp, 24h;
		popad;
	}
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
void r::R_AddCmdDrawTextWithEffects(char* text, int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation,
	const float* color, int style, const float* glowColor, Material* fxMaterial, Material* fxMaterialGlow,
	int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	const static uint32_t R_AddCmdDrawTextWithEffects_f = 0x5F6D30;

	return ((void(__cdecl*)(char* text, int maxChars, Font_s * font, float x, float y, float xScale, float yScale, float rotation,
		const float* color, int style, const float* glowColor, Material * fxMaterial, Material * fxMaterialGlow,
		int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration))0x5F6D30)(text, maxChars, font, x,  y,  xScale,  yScale,  rotation,
			color,  style, glowColor,  fxMaterial, fxMaterialGlow,
			 fxBirthTime,  fxLetterTime,  fxDecayStartTime,  fxDecayDuration);
}
void r::R_AddCmdDrawTextWithEffects(char* text, const char* font, float x, float y, float xScale, float yScale, float rotation,
	const float* color, int style, const float* glowColor, Material* fxMaterial, Material* fxMaterialGlow,
	int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration)
{
	Font_s* _font = R_RegisterFont(font);

	R_AddCmdDrawTextWithEffects(text, 0x7FFFFFFF, _font, x, y, xScale, yScale, rotation, color, style, glowColor, fxMaterial, fxMaterialGlow, fxBirthTime, fxLetterTime, fxDecayStartTime, fxDecayDuration);

}
ScreenPlacement* r::CG_GetScreenPlacement(int LocalClientNum)
{
	return (ScreenPlacement*)((68 * LocalClientNum + 14894040));
}
void r::CG_DrawRotatedPic(int vertical, int horizontal, ScreenPlacement* scrPlace, float x, float y, float w, float h, float angle, float* color, const char* material)
{
	Material* mat = R_RegisterMaterial(material);
	return CG_DrawRotatedPic(vertical, horizontal, scrPlace, x, y, w, h, angle, color, mat);
}
void r::CG_DrawRotatedPic(int vertical, int horizontal, ScreenPlacement* scrPlace, float x, float y, float w, float h, float angle, float* color, Material* material)
{
	ScrPlace_ApplyRect(&x, &w, &y, &h, scrPlace, horizontal, vertical);
	return CG_DrawRotatedPicPhysical(scrPlace, x, y, w, h, angle, color, material);
}
ScreenPlacement* r::ScrPlace_ApplyRect(float* x, float* w, float* y, float* h, ScreenPlacement* placement, int horizontal, int vertical)
{
	ScreenPlacement* result; // eax
	double _x; // st6
	double _w; // st6

	result = placement;
	switch (horizontal)
	{
	case 1:
		_x = placement->scaleVirtualToReal[0] * *x + placement->realViewableMin[0];
		goto LABEL_9;
	case 2:
		_x = placement->scaleVirtualToReal[0] * *x + placement->realViewportSize[0] * 0.5;
		goto LABEL_9;
	case 3:
		_x = placement->scaleVirtualToReal[0] * *x + placement->realViewableMax[0];
		goto LABEL_9;
	case 4:
		*x = placement->scaleVirtualToFull[0] * *x;
		_w = placement->scaleVirtualToFull[0];
		goto OOF;
	case 5:
		goto LABEL_11;
	case 6:
		*x = placement->scaleRealToVirtual[0] * *x;
		_w = placement->scaleRealToVirtual[0];
		goto OOF;
	case 7:
		_x = (placement->realViewableMax[0] + placement->realViewableMin[0]) * 0.5 + placement->scaleVirtualToReal[0] * *x;
		goto LABEL_9;
	default:
		_x = placement->scaleVirtualToReal[0] * *x + placement->subScreenLeft;// crash
	LABEL_9:
		*x = _x;
		_w = placement->scaleVirtualToReal[0];
	OOF:
		*w = _w * *w;
	LABEL_11:
		switch (vertical)
		{
		case 1:
			*y = *y * placement->scaleVirtualToReal[1] + placement->realViewableMin[1];
			*h = placement->scaleVirtualToReal[1] * *h;
			break;
		case 2:
			*y = 0.5 * placement->realViewportSize[1] + *y * placement->scaleVirtualToReal[1];
			*h = placement->scaleVirtualToReal[1] * *h;
			break;
		case 3:
			*y = *y * placement->scaleVirtualToReal[1] + placement->realViewableMax[1];
			*h = placement->scaleVirtualToReal[1] * *h;
			break;
		case 4:
			*y = *y * placement->scaleVirtualToFull[1];
			*h = placement->scaleVirtualToFull[1] * *h;
			break;
		case 5:
			return result;
		case 6:
			*y = *y * placement->scaleRealToVirtual[1];
			*h = placement->scaleRealToVirtual[1] * *h;
			break;
		case 7:
			*y = 0.5 * (placement->realViewableMax[1] + placement->realViewableMin[1]) + *y * placement->scaleVirtualToReal[1];
			*h = placement->scaleVirtualToReal[1] * *h;
			break;
		default:
			*y = *y * placement->scaleVirtualToReal[1];
			*h = placement->scaleVirtualToReal[1] * *h;
			break;
		}
		return result;
	}
}
void r::CG_DrawRotatedPicPhysical(ScreenPlacement* scrPlace, float x, float y, float w, float h, float angle, float* color, Material* material)
{
	double v8; // st7
	double v9; // st4
	double v10; // st3
	double v11; // st6
	double v12; // st2
	double v13; // st7
	double v14; // st5
	float v16; // [esp+0h] [ebp-44h] BYREF
	float v17; // [esp+Ch] [ebp-38h]
	float v18; // [esp+10h] [ebp-34h]
	float v19; // [esp+14h] [ebp-30h]
	float v20; // [esp+18h] [ebp-2Ch]
	float v21; // [esp+1Ch] [ebp-28h]
	float v22; // [esp+20h] [ebp-24h]
	float verts[8]; // [esp+24h] [ebp-20h] BYREF
	float wa; // [esp+50h] [ebp+Ch]
	float wb; // [esp+50h] [ebp+Ch]
	float wc; // [esp+50h] [ebp+Ch]
	float wd; // [esp+50h] [ebp+Ch]
	float we; // [esp+50h] [ebp+Ch]
	float wf; // [esp+50h] [ebp+Ch]
	float wg; // [esp+50h] [ebp+Ch]
	float wh; // [esp+50h] [ebp+Ch]
	float wi; // [esp+50h] [ebp+Ch]
	float wj; // [esp+50h] [ebp+Ch]
	float wk; // [esp+50h] [ebp+Ch]
	float wl; // [esp+50h] [ebp+Ch]
	float ha; // [esp+54h] [ebp+10h]

	v16 = angle;
	v17 = angle * 0.01745329238474369;
	angle = cos(v17);
	v16 = sin(v17);
	wa = w * 0.5;
	v17 = wa * scrPlace->scaleRealToVirtual[0];
	wb = 0.5 * h;
	ha = wb * scrPlace->scaleRealToVirtual[1];
	wc = x * scrPlace->scaleRealToVirtual[0];
	v8 = v17;
	v17 = wc + v17;
	wd = scrPlace->scaleRealToVirtual[1] * y;
	v18 = wd + ha;
	v19 = v8 * angle;
	v20 = v8 * v16;
	v21 = v16 * ha;
	v22 = angle * ha;
	v9 = v17 - v19 * 1.0;
	v10 = v21 * -1.0;
	we = v9 - v10;
	verts[0] = we * scrPlace->scaleVirtualToReal[0];
	v11 = v18 - 1.0 * v20;
	v12 = -1.0 * v22;
	wf = v12 + v11;
	verts[1] = wf * scrPlace->scaleVirtualToReal[1];
	v13 = v17 + v19;
	wg = v13 - v10;
	verts[2] = wg * scrPlace->scaleVirtualToReal[0];
	v14 = v20 + v18;
	wh = v12 + v14;
	verts[3] = wh * scrPlace->scaleVirtualToReal[1];
	wi = v13 - v21;
	verts[4] = wi * scrPlace->scaleVirtualToReal[0];
	wj = v14 + v22;
	verts[5] = wj * scrPlace->scaleVirtualToReal[1];
	wk = v9 - v21;
	verts[6] = wk * scrPlace->scaleVirtualToReal[0];
	wl = v22 + v11;
	verts[7] = wl * scrPlace->scaleVirtualToReal[1];

	__asm
	{
		mov edx, material;
		push material;
		lea edx, verts;
		mov ecx, color;
		mov esi, 0x5F7230;
		call esi;
		add esp, 0x4;
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
	const float x = (float)cgs->refdef.width;
	return pos <= 1920 ? pos / (1920.f / x) : pos * (x / 1920);

}
float r::Y(float pos)
{
	const float y = (float)cgs->refdef.height;
	return pos <= 1080 ? pos / (1080.f / y) : pos * (y / 1080);
}
void r::MetricsHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
std::string r::R_UserCmdKeysPressed(char forwardmove, char sidemove)
{
	std::string key;

	if (forwardmove < 0)
		key.push_back('S');
	else if (forwardmove > 0)
		key.push_back('W');
	else 
		key.push_back(' ');



	if (sidemove < 0)
		key.push_back('A');
	else if (sidemove > 0)
		key.push_back('D');
	else 
		key.push_back(' ');


	return key;
}
r::box_s::box_s(vec3_t origin, vec3_t mins, vec3_t maxs)
{
	//box_s box{};

	vec3_t lowA, lowB, lowC, lowD;
	vec3_t highA, highB, highC, highD;

	lowA[0] = origin[0] - mins[0];
	lowA[1] = origin[1] - mins[1];
	lowA[2] = origin[2] - mins[2];

	lowB[0] = origin[0] + mins[0];
	lowB[1] = origin[1] + mins[1];
	lowB[2] = origin[2] - mins[2];

	lowC[0] = origin[0] - mins[0];
	lowC[1] = origin[1] + mins[1];
	lowC[2] = origin[2] - mins[2];

	lowD[0] = origin[0] + mins[0];
	lowD[1] = origin[1] - mins[1];
	lowD[2] = origin[2] - mins[2];

	highA[0] = lowA[0];
	highA[1] = lowA[1];
	highA[2] = origin[2] + maxs[2];

	highB[0] = lowB[0];
	highB[1] = lowB[1];
	highB[2] = origin[2] + maxs[2];

	highC[0] = lowC[0];
	highC[1] = lowC[1];
	highC[2] = origin[2] + maxs[2];

	highD[0] = lowD[0];
	highD[1] = lowD[1];
	highD[2] = origin[2] + maxs[2];

	this->lowA_valid = WorldToScreen(lowA, this->lowA);
	this->lowB_valid = WorldToScreen(lowB, this->lowB);
	this->lowC_valid = WorldToScreen(lowC, this->lowC);
	this->lowD_valid = WorldToScreen(lowD, this->lowD);

	this->highA_valid = WorldToScreen(highA, this->highA);
	this->highB_valid = WorldToScreen(highB, this->highB);
	this->highC_valid = WorldToScreen(highC, this->highC);
	this->highD_valid = WorldToScreen(highD, this->highD);

	//return box;
}
void r::box_s::R_DrawConstructedBoxEdges(vec4_t col) const
{
	if (!ImGui::GetCurrentContext())
		return;

	if(this->lowA_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->lowC[0], this->lowC[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowB_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->lowD[0], this->lowD[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowC_valid && this->lowB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowC[0], this->lowC[1]), ImVec2(this->lowB[0], this->lowB[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowD_valid && this->lowA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowD[0], this->lowD[1]), ImVec2(this->lowA[0], this->lowA[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highA_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highA[0], this->highA[1]), ImVec2(this->highC[0], this->highC[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highB[0], this->highB[1]), ImVec2(this->highD[0], this->highD[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highC_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highC[0], this->highC[1]), ImVec2(this->highB[0], this->highB[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highD_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highD[0], this->highD[1]), ImVec2(this->highA[0], this->highA[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowA_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->highA[0], this->highA[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowB_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->highB[0], this->highB[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowC_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowC[0], this->lowC[1]), ImVec2(this->highC[0], this->highC[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowD_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowD[0], this->lowD[1]), ImVec2(this->highD[0], this->highD[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);
}
void r::box_s::R_DrawConstructedBox(vec4_t col) const
{
	if (!ImGui::GetCurrentContext())
		return;

	if (this->lowA_valid && this->highC_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->highC[0], this->highC[1]), ImVec2(this->lowC[0], this->lowC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowA_valid && this->highA_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA[0], this->highA[1]), ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->highC[0], this->highC[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowB_valid && this->highD_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->highD[0], this->highD[1]), ImVec2(this->lowD[0], this->lowD[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowB_valid && this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highB[0], this->highB[1]), ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->highD[0], this->highD[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowC_valid && this->highB_valid && this->lowB_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowC[0], this->lowC[1]), ImVec2(this->highB[0], this->highB[1]), ImVec2(this->lowB[0], this->lowB[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowC_valid && this->highC_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highC[0], this->highC[1]), ImVec2(this->lowC[0], this->lowC[1]), ImVec2(this->highB[0], this->highB[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowD_valid && this->highA_valid && this->lowA_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowD[0], this->lowD[1]), ImVec2(this->highA[0], this->highA[1]), ImVec2(this->lowA[0], this->lowA[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowD_valid && this->highD_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highD[0], this->highD[1]), ImVec2(this->lowD[0], this->lowD[1]), ImVec2(this->highA[0], this->highA[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->highA_valid && this->highB_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA[0], this->highA[1]), ImVec2(this->highB[0], this->highB[1]), ImVec2(this->highC[0], this->highC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->highA_valid && this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA[0], this->highA[1]), ImVec2(this->highB[0], this->highB[1]), ImVec2(this->highD[0], this->highD[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	
	if (this->lowA_valid && this->lowB_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->lowC[0], this->lowC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowA_valid && this->lowB_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->lowD[0], this->lowD[1]), IM_COL32(col[0], col[1], col[2], col[3]));
}
void r::R_DrawTriangle(vec3_t points[3], vec4_t col) {

	if (!ImGui::GetCurrentContext())
		return;

	vec2_t sc[3];

	const bool a = WorldToScreen(points[0], sc[0]);
	const bool b = WorldToScreen(points[1], sc[1]);
	const bool c = WorldToScreen(points[2], sc[2]);

	if (!a || !b || !c)
		return;

	ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(sc[0][0], sc[0][1]), ImVec2(sc[1][0], sc[1][1]), ImVec2(sc[2][0], sc[2][1]), IM_COL32(col[0], col[1], col[2], col[3]));


}
void r::R_DrawTriangleOutline(vec3_t points[3], vec4_t col)
{
	if (!ImGui::GetCurrentContext())
		return;

	vec2_t sc[3];

	const bool a = WorldToScreen(points[0], sc[0]);
	const bool b = WorldToScreen(points[1], sc[1]);
	const bool c = WorldToScreen(points[2], sc[2]);

	if (!a || !b || !c)
		return;

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(sc[0][0], sc[0][1]), ImVec2(sc[1][0], sc[1][1]), IM_COL32(col[0], col[1], col[2], col[3]), 2);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(sc[0][0], sc[0][1]), ImVec2(sc[2][0], sc[2][1]), IM_COL32(col[0], col[1], col[2], col[3]), 2);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(sc[1][0], sc[1][1]), ImVec2(sc[2][0], sc[2][1]), IM_COL32(col[0], col[1], col[2], col[3]), 2);


}
void r::R_DrawTriangle(vec3_t pointA, vec3_t pointB, vec3_t pointC, vec4_t col)
{
	if (!ImGui::GetCurrentContext())
		return;

	vec2_t sc[3];

	const bool a = WorldToScreen(pointA, sc[0]);
	const bool b = WorldToScreen(pointB, sc[1]);
	const bool c = WorldToScreen(pointC, sc[2]);

	if (!a || !b || !c)
		return;

	ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(sc[0][0], sc[0][1]), ImVec2(sc[1][0], sc[1][1]), ImVec2(sc[2][0], sc[2][1]), IM_COL32(col[0], col[1], col[2], col[3]));
}
bool r::ButtonCentered(const char* label, float alignment)
{
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * alignment;
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	return ImGui::Button(label);
}
LPDIRECT3DTEXTURE9 r::UI_FindImageByName(const char* name)
{
	for (const auto& i : imagePairs) {
		if (!strcmp(name, fs::removeFileExtension(i.first.c_str(), 4).c_str()))
			return i.second;
	}
	return nullptr;
}
size_t r::UI_GetImageIndex(const char* name)
{
	for (size_t i = 0; i < imagePairs.size(); i++) {

		if (!strcmp(name, fs::removeFileExtension(imagePairs[i].first.c_str(), 4).c_str()))
			return i;
	}
	return 0;
}
void r::UI_CreateSettings(bool& editing)
{
	LPDIRECT3DTEXTURE9 tex = r::UI_FindImageByName("Settings_no_load");

	if (!tex) {
		tex = r::UI_FindImageByName("Error_no_load");
		if (!tex) {
			fs::Log_Write(LOG_FATAL, "unable to load the image '%s'", std::string(fs::GetExePath() + "\\1_kej\\images\\Error_no_load.png").c_str());
			return;
		}
	}

	ImGui::BeginGroup();

	ImGui::Image(tex, ImVec2(24, 24));
	
	if (ImGui::IsItemHovered()) {
		const ImVec2 mins = ImGui::GetItemRectMin();
		const ImVec2 maxs = ImGui::GetItemRectMax();

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(mins.x - 3, mins.y - 3), ImVec2(maxs.x + 3, maxs.y + 3), IM_COL32(255, 255, 255, 170));


		if(ImGui::IsItemClicked())
			editing = !editing;
	}
	ImGui::EndGroup();
}


void r::UI_DrawGradientZone(ImVec2 size)
{
	ImGradient grad;
	grad.addMark(0, ImColor(255, 111, 0, 255));
	grad.addMark(0.5f, ImColor(255, 175, 0, 255));
	grad.addMark(1, ImColor(255, 230, 0, 255));
	const ImVec2 sp = ImGui::GetCursorScreenPos();
	ImGui::DrawGradientBar(&grad, sp, size.x, 5);
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(sp.x, sp.y + 5), ImVec2(sp.x + size.x, sp.y + size.y), ImColor(0.08f, 0.07f, 0.075f, 0.8f));
	ImGui::Dummy(ImVec2(size.x, 1));
}


std::vector<ImVec2> r::OriginsToScreen(std::vector<jump_data> data, std::vector<ImVec2>* color, float average) 
{
	std::vector<ImVec2> points;
	color->clear();
	color->resize(1);
	color->erase(color->begin(), color->end());

	int validPoints{ 0 };
	vec2_t xy;

	for (unsigned i = 0; i < data.size(); i++) {
		if (r::WorldToScreen(data[i].origin, xy)) {
			points.push_back(ImVec2(xy[0], xy[1]));

			ImVec2 fcolor;

			float col = VALUE2COLOR(glm::length(glm::vec2(data[i].velocity[0], data[i].velocity[1])), average);

			fcolor.x = 255.f - col;
			fcolor.y = col;
			if (col > 255) {
				fcolor.x = 0;
				fcolor.y = 255; //green because we got more speed
			}
			color->push_back(fcolor);
			validPoints += 1;
		}
	}
	points.resize(validPoints);
	color->resize(validPoints);
	return points;
}
std::vector<ImVec2> r::OriginsToScreen(std::vector<jump_data> data)
{
	std::vector<ImVec2> points;

	int validPoints{ 0 };
	vec2_t xy;

	for (unsigned i = 0; i < data.size(); i++) {
		if (r::WorldToScreen(data[i].origin, xy)) {
			points.push_back(ImVec2(xy[0], xy[1]));
			validPoints += 1;
		}
	}
	points.resize(validPoints);
	return points;
}