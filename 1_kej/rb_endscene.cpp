#include "pch.h"


void r::RB_DrawPolyInteriors(int n_points, const vec3_t* points, const BYTE* color, bool two_sided, bool depthTest)
{
	//partly copied from iw3xo :)
	if (n_points < 3)
		return;
	static Material whiteMaterial = *rgp->whiteMaterial;
	static uint32_t ogBits = whiteMaterial.stateBitsTable->loadBits[1];

	Material* material = &whiteMaterial;

	if (gfxCmdBufState->origMaterial != material || gfxCmdBufState->origTechType != MaterialTechniqueType::TECHNIQUE_UNLIT) {
		if (tess->indexCount)
			RB_EndTessSurface();

		if(depthTest)
			material->stateBitsTable->loadBits[1] = 44;
		else
			material->stateBitsTable->loadBits[1] = ogBits;

		if(two_sided)
			material->stateBitsTable->loadBits[0] = 422072677;
		else
			material->stateBitsTable->loadBits[0] = 422089061;

		RB_BeginSurface(MaterialTechniqueType::TECHNIQUE_UNLIT, material);

	}
	if (n_points + tess->vertexCount > 5450 || tess->indexCount + 2 * (n_points - 2) > 1048576)// RB_CheckTessOverflow
	{
		RB_EndTessSurface();
		RB_BeginSurface(gfxCmdBufState->origTechType, gfxCmdBufState->origMaterial);
	}
	int idx = 0;

	for (; idx < n_points; ++idx) {
		RB_SetPolyVertice(points[idx], color, tess->vertexCount + idx, idx);
	}

	for (idx = 2; idx < n_points; ++idx)
	{
		tess->indices[tess->indexCount + 0] = tess->vertexCount;
		tess->indices[tess->indexCount + 1] = (idx + tess->vertexCount);
		tess->indices[tess->indexCount + 2] = (idx + tess->vertexCount - 1);
		tess->indexCount += 3;
	}

	tess->vertexCount += n_points;

	RB_EndTessSurface();

}
int r::RB_AddDebugLine(GfxPointVertex* verts, char depthTest, const vec_t* start, vec_t* end, const vec_t* color, int vertCount)
{
	int _vc = vertCount;
	uint8_t _color[4]{0,0,0,0};
	if (vertCount + 2 > 2725)
	{
		RB_DrawLines3D(vertCount / 2, 1, verts, depthTest);
		_vc = 0;
	}

	GfxPointVertex* vert = &verts[_vc];
	if (color) {
		R_ConvertColorToBytes(color, vert->color);
	}

	verts[_vc + 1].color[0] = vert->color[0];
	verts[_vc + 1].color[1] = vert->color[1];
	verts[_vc + 1].color[2] = vert->color[2];
	verts[_vc + 1].color[3] = vert->color[3];

	VectorCopy(start, vert->xyz);

	vert = &verts[_vc + 1];
	VectorCopy(end, vert->xyz);


	return _vc + 2;

	//return ((int(*)(GfxPointVertex *, char, const vec_t *, vec_t *, const vec_t *, int))0x658210)(verts, depthTest, start, end, color, vertCount);
}
void r::R_ConvertColorToBytes(const vec4_t in, uint8_t* out)
{

	((char(__fastcall*)(const float* in, uint8_t * out))0x493530)(in, out);

	return;
}
char r::RB_DrawLines3D(int count, int width, GfxPointVertex* verts, char depthTest)
{
	((char(__cdecl*)(int, int, GfxPointVertex*, char))0x613040)(count, width, verts, depthTest);
	return 1;

}
int r::RB_BeginSurface(MaterialTechniqueType tech, Material* material)
{
	int rval=0;
	const static DWORD fnc = 0x61A220;
	__asm
	{
		mov edi, tech;
		mov esi, material;
		call fnc;
		mov rval, eax;
	}
	return rval;
}
void r::RB_EndTessSurface()
{
	((void(*)())0x61A2F0)();

}
void r::RB_SetPolyVertice(const vec3_t pos, const BYTE* col, const int vert, const int index)
{
	VectorCopy(pos, tess->verts[vert].xyzw);
	//tess->verts[vert].color.packed = 0xFF00FFAA;
	tess->verts[vert].color.array[0] = col[0];
	tess->verts[vert].color.array[1] = col[1];
	tess->verts[vert].color.array[2] = col[2];
	tess->verts[vert].color.array[3] = col[3];

	//std::cout << "color: " << std::hex << tess->verts[vert].color.packed << '\n';

	switch (index)
	{
	case 0:
		tess->verts[vert].texCoord[0] = 0.0f;
		tess->verts[vert].texCoord[1] = 0.0f;
		break;

	case 1:
		tess->verts[vert].texCoord[0] = 0.0f;
		tess->verts[vert].texCoord[1] = 1.0f;
		break;
	case 2:
		tess->verts[vert].texCoord[0] = 1.0f;
		tess->verts[vert].texCoord[1] = 1.0f;
		break;
	case 3:
		tess->verts[vert].texCoord[0] = 1.0f;
		tess->verts[vert].texCoord[1] = 0.0f;
		break;

	default:
		tess->verts[vert].texCoord[0] = 0.0f;
		tess->verts[vert].texCoord[1] = 0.0f;
		break;
	}

	tess->verts[vert].normal.packed = 1073643391;
}
char r::RB_DrawDebug(GfxViewParms* viewParms)
{
//	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {

	RBW_TerrainClips();
	

	return RB_DrawDebug_f(viewParms);
}

void r::RB_DrawTriangleOutline(vec3_t points[3], vec4_t color, int width, bool depthTest)
{
	GfxPointVertex verts[6]{};



	RB_AddDebugLine(verts, depthTest, points[0], points[1], color, 0);
	RB_AddDebugLine(verts, depthTest, points[0], points[2], color, 2);
	RB_AddDebugLine(verts, depthTest, points[1], points[2], color, 4);

	RB_DrawLines3D(3, width, verts, depthTest);

}