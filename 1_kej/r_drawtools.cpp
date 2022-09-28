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
r::box_s r::R_ConstructBoxFromBounds(vec3_t origin, vec3_t mins, vec3_t maxs)
{
	box_s box{};

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

	box.lowA_valid = WorldToScreen(lowA, box.lowA);
	box.lowB_valid = WorldToScreen(lowB, box.lowB);
	box.lowC_valid = WorldToScreen(lowC, box.lowC);
	box.lowD_valid = WorldToScreen(lowD, box.lowD);

	box.highA_valid = WorldToScreen(highA, box.highA);
	box.highB_valid = WorldToScreen(highB, box.highB);
	box.highC_valid = WorldToScreen(highC, box.highC);
	box.highD_valid = WorldToScreen(highD, box.highD);

	return box;
}
void r::R_DrawConstructedBoxEdges(box_s box, vec4_t col)
{
	if (!ImGui::GetCurrentContext())
		return;

	if(box.lowA_valid && box.lowC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.lowA[0], box.lowA[1]), ImVec2(box.lowC[0], box.lowC[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.lowB_valid && box.lowD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.lowB[0], box.lowB[1]), ImVec2(box.lowD[0], box.lowD[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.lowC_valid && box.lowB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.lowC[0], box.lowC[1]), ImVec2(box.lowB[0], box.lowB[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.lowD_valid && box.lowA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.lowD[0], box.lowD[1]), ImVec2(box.lowA[0], box.lowA[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.highA_valid && box.highC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.highA[0], box.highA[1]), ImVec2(box.highC[0], box.highC[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.highB_valid && box.highD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.highB[0], box.highB[1]), ImVec2(box.highD[0], box.highD[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.highC_valid && box.highB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.highC[0], box.highC[1]), ImVec2(box.highB[0], box.highB[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.highD_valid && box.highA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.highD[0], box.highD[1]), ImVec2(box.highA[0], box.highA[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.lowA_valid && box.highA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.lowA[0], box.lowA[1]), ImVec2(box.highA[0], box.highA[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.lowB_valid && box.highB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.lowB[0], box.lowB[1]), ImVec2(box.highB[0], box.highB[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.lowC_valid && box.highC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.lowC[0], box.lowC[1]), ImVec2(box.highC[0], box.highC[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (box.lowD_valid && box.highD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(box.lowD[0], box.lowD[1]), ImVec2(box.highD[0], box.highD[1]),IM_COL32(col[0], col[1], col[2], col[3]), 1.f);
}
void r::R_DrawConstructedBox(box_s box, vec4_t col)
{
	if (!ImGui::GetCurrentContext())
		return;

	if (box.lowA_valid && box.highC_valid && box.lowC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.lowA[0], box.lowA[1]), ImVec2(box.highC[0], box.highC[1]), ImVec2(box.lowC[0], box.lowC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (box.lowA_valid && box.highA_valid && box.highC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.highA[0], box.highA[1]), ImVec2(box.lowA[0], box.lowA[1]), ImVec2(box.highC[0], box.highC[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (box.lowB_valid && box.highD_valid && box.lowD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.lowB[0], box.lowB[1]), ImVec2(box.highD[0], box.highD[1]), ImVec2(box.lowD[0], box.lowD[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (box.lowB_valid && box.highB_valid && box.highD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.highB[0], box.highB[1]), ImVec2(box.lowB[0], box.lowB[1]), ImVec2(box.highD[0], box.highD[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (box.lowC_valid && box.highB_valid && box.lowB_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.lowC[0], box.lowC[1]), ImVec2(box.highB[0], box.highB[1]), ImVec2(box.lowB[0], box.lowB[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (box.lowC_valid && box.highC_valid && box.highB_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.highC[0], box.highC[1]), ImVec2(box.lowC[0], box.lowC[1]), ImVec2(box.highB[0], box.highB[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (box.lowD_valid && box.highA_valid && box.lowA_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.lowD[0], box.lowD[1]), ImVec2(box.highA[0], box.highA[1]), ImVec2(box.lowA[0], box.lowA[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (box.lowD_valid && box.highD_valid && box.highA_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.highD[0], box.highD[1]), ImVec2(box.lowD[0], box.lowD[1]), ImVec2(box.highA[0], box.highA[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (box.highA_valid && box.highB_valid && box.highC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.highA[0], box.highA[1]), ImVec2(box.highB[0], box.highB[1]), ImVec2(box.highC[0], box.highC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (box.highA_valid && box.highB_valid && box.highD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.highA[0], box.highA[1]), ImVec2(box.highB[0], box.highB[1]), ImVec2(box.highD[0], box.highD[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	
	if (box.lowA_valid && box.lowB_valid && box.lowC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.lowA[0], box.lowA[1]), ImVec2(box.lowB[0], box.lowB[1]), ImVec2(box.lowC[0], box.lowC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (box.lowA_valid && box.lowB_valid && box.lowD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(box.lowA[0], box.lowA[1]), ImVec2(box.lowB[0], box.lowB[1]), ImVec2(box.lowD[0], box.lowD[1]), IM_COL32(col[0], col[1], col[2], col[3]));
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