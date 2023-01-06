#include "pch.h"

void cg::CM_BuildAxialPlanes(float* planes, const cbrush_t* mins)
{

	(planes)[0] = -1.0;
	(planes)[1] = 0.0;
	(planes)[2] = 0.0;
	(planes)[3] = -mins->mins[0];
	(planes)[4] = 1.0;
	(planes)[5] = 0.0;
	(planes)[6] = 0.0;
	(planes)[7] = mins->maxs[0];
	(planes)[8] = 0.0;
	(planes)[10] = 0.0;
	(planes)[9] = -1.0;
	(planes)[11] = -mins->mins[1];
	(planes)[12] = 0.0;
	(planes)[14] = 0.0;
	(planes)[13] = 1.0;
	(planes)[15] = mins->maxs[1];
	(planes)[16] = 0.0;
	(planes)[17] = 0.0;
	(planes)[18] = -1.0;
	(planes)[19] = -mins->mins[2];
	(planes)[20] = 0.0;
	(planes)[21] = 0.0;
	(planes)[22] = 1.0;
	(planes)[23] = mins->maxs[2];
}
void cg::Phys_GetWindingForBrushFace(unsigned int brushSide, cbrush_t* brush, Poly* outPolys, const float(*planes)[4], signed int maxVerts)
{
	static DWORD fn = 0x00599560;
	__asm
	{
		mov edx, maxVerts;
		mov ecx, planes;
		push ecx;
		push edx;
		mov eax, brushSide;
		mov edx, brush;
		mov esi, outPolys;
		call fn;
		add esp, 0x8;

	}

}