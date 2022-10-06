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

	void R_AddCmdDrawTextWithEffects(char* text, int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation, 
		const float* color, int style, const float* glowColor, Material* fxMaterial, Material* fxMaterialGlow, 
		int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration); //holy this takes a lot of args

	void R_AddCmdDrawTextWithEffects(char* text, const char* font, float x, float y, float xScale, float yScale, float rotation,
		const float* color, int style, const float* glowColor, Material* fxMaterial, Material* fxMaterialGlow,
		int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration);

	std::string R_UserCmdKeysPressed(char forwardmove, char sidemove);

	float X(float pos);
	float Y(float pos);

	void MetricsHelpMarker(const char* desc);

	struct box_s
	{
		vec2_t lowA;
		vec2_t lowB;
		vec2_t lowC;
		vec2_t lowD;

		vec2_t highA;
		vec2_t highB;
		vec2_t highC;
		vec2_t highD;

		bool lowA_valid;
		bool lowB_valid;
		bool lowC_valid;
		bool lowD_valid;
		
		bool highA_valid;
		bool highB_valid;
		bool highC_valid;
		bool highD_valid;


	};

	box_s R_ConstructBoxFromBounds(vec3_t origin, vec3_t mins, vec3_t maxs);

	void R_DrawConstructedBox(box_s box, vec4_t col);
	void R_DrawConstructedBoxEdges(box_s box, vec4_t col);

	void R_DrawTriangle(vec3_t points[3], vec4_t col);
	void R_DrawTriangle(vec3_t pointA, vec3_t pointB, vec3_t pointC, vec4_t col);

	bool ButtonCentered(const char* label, float alignment = 0.5f);

	void UI_CreateSettings(bool& isediting);
	LPDIRECT3DTEXTURE9 UI_FindImageByName(const char* name);
	size_t UI_GetImageIndex(const char* name);
	void UI_DrawGradientZone(ImVec2 size);

	std::vector<ImVec2> OriginsToScreen(std::vector<jump_data> data, std::vector<ImVec2>* color, float average);
	std::vector<ImVec2> OriginsToScreen(std::vector<jump_data> data);

}

#endif