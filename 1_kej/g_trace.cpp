#include "pch.h"

char cg::CG_BulletTrace(BulletTraceResults* trace, BulletFireParams* fireParams, centity_s* ignore, int depthSurfaceType)
{
	TraceHitType hitType; // eax
	char result; // al
	unsigned __int16 hitId; // cx
	centity_s* hitEntity; // eax
	double trace_cent; // st7
	int entType; // eax
	int traceSurfFlags; // ecx
	int surfFlags; // eax

	memset(trace, 0, 68);
	CG_TracePoint(vec3_origin->extents.start, &trace->trace, fireParams->start, vec3_origin->extents.start, fireParams->end, fireParams->ignoreEntIndex, MASK_SHOT | MASK_SHOT_HULL, 1u, 1);

	hitType = trace->trace.hitType;
	if (hitType == TRACE_HITTYPE_NONE)
	{
		return 0;
	}
	else if (hitType == TRACE_HITTYPE_DYNENT_MODEL || hitType == TRACE_HITTYPE_DYNENT_BRUSH)
	{
		hitId = 1022;
		hitEntity = 0;
	}
	else if (hitType != TRACE_HITTYPE_ENTITY) {
		hitId = 1023;
		hitEntity = &(*(centity_s*)0x084F2D8) + 1023;
	}
	else {
		hitEntity = 0;
		hitId = trace->trace.hitId;
		if (hitId != 1022)
		{
			hitEntity = &(*(centity_s*)0x084F2D8) + hitId;
		}

	}
	trace_cent = trace->trace.fraction;
	trace->hitPos[0] = (fireParams->end[0] - fireParams->start[0]) * trace_cent + fireParams->start[0];
	trace->hitPos[1] = (fireParams->end[1] - fireParams->start[1]) * trace_cent + fireParams->start[1];
	trace->hitPos[2] = trace_cent * (fireParams->end[2] - fireParams->start[2]) + fireParams->start[2];

	if (hitEntity)
	{
		entType = hitEntity->nextState.eType;
		if ((entType == ET_PLAYER || entType == ET_PLAYER_CORPSE) && !trace->trace.surfaceFlags)
		{
			trace->trace.surfaceFlags = SURF_FLESH;
		}
		trace->ignoreHitEnt = hitId == ignore->nextState.number;
	}
	traceSurfFlags = trace->trace.surfaceFlags;
	surfFlags = (traceSurfFlags >> 20) & 0x1F;
	trace->depthSurfaceType = surfFlags;
	if ((traceSurfFlags & 0x100) != 0)
	{
		trace->depthSurfaceType = 0;
		result = 1;
	}
	else
	{
		if (!surfFlags)
		{
			if (depthSurfaceType)
			{
				trace->depthSurfaceType = depthSurfaceType;
			}
		}
		result = 1;
	}
	return result;
}
char cg::BG_AdvanceTrace(BulletTraceResults* br, BulletFireParams* bpp, float _fraction)
{
	TraceHitType v3; // eax
	unsigned __int16 entIndex; // ax
	double v5; // st7
	char success; // al
	float lenb; // [esp+0h] [ebp-4h]
	float negLen; // [esp+0h] [ebp-4h]
	float fraction; // [esp+0h] [ebp-4h]

	v3 = br->trace.hitType;
	if (v3 == TRACE_HITTYPE_DYNENT_MODEL || v3 == TRACE_HITTYPE_DYNENT_BRUSH)
	{
		entIndex = 1022;
	}
	else if (v3 == TRACE_HITTYPE_ENTITY)
	{
		entIndex = br->trace.hitId;
	}
	else
	{
		entIndex = 1023;
	}
	bpp->ignoreEntIndex = entIndex;
	if (entIndex != 1022)
	{
		success = 1;
		bpp->start[0] = br->hitPos[0];
		bpp->start[1] = br->hitPos[1];
		bpp->start[2] = br->hitPos[2];
		return success;
	}
	v5 = _fraction;
	if (_fraction > 0.0)
	{
		lenb = br->trace.normal[1] * bpp->dir[1] + bpp->dir[0] * br->trace.normal[0] + br->trace.normal[2] * bpp->dir[2];
		negLen = -lenb;
		if (negLen >= 0.125)
		{
			success = 1;
			fraction = v5 / negLen;
		}
		else
		{
			success = 0;
			fraction = v5 * 8.0;
		}
		bpp->start[0] = bpp->dir[0] * fraction + br->hitPos[0];
		bpp->start[1] = bpp->dir[1] * fraction + br->hitPos[1];
		bpp->start[2] = fraction * bpp->dir[2] + br->hitPos[2];
	}
	else
	{
		success = 1;
		bpp->start[0] = br->hitPos[0];
		bpp->start[1] = br->hitPos[1];
		bpp->start[2] = br->hitPos[2];
	}
	return success;
}
void __fastcall cg::CG_TracePoint(vec3_t maxs, trace_t* trace, vec3_t start, vec3_t mins, vec3_t end, int entityNum, int contentMask, uint8_t unknw0, int8_t traceStaticModels)
{

	_asm
	{
		mov eax, [contentMask];
		mov ecx, [entityNum];
		mov edx, [end];
		push edi;
		mov edi, [trace];
		push traceStaticModels;
		push unknw0;
		push eax;
		mov eax, [mins];
		push ecx;
		mov ecx, [start];
		push edx;
		push eax;
		mov eax, [maxs];
		push ecx;
		mov esi, 0x459EF0;
		call esi;
		add esp, 0x1C;
	} //shit asm, but at least it doesn't crash and it doesn't seem to cause any weird issues..
}
int cg::PM_playerTrace(pmove_t* pm, trace_t* trace, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask)
{
	int retn = 0;
	TraceHitType v9; // eax
	uint16_t entityNum = 0;

	CG_Trace(trace, start, mins, maxs, end, passEntityNum, contentMask);

	if (trace->startsolid && (svs->clients[5].reliableCommandInfo[18].cmd[360] & trace->contents) != 0)
	{
		v9 = trace->hitType;
		if (v9 == TRACE_HITTYPE_DYNENT_MODEL || v9 == TRACE_HITTYPE_DYNENT_BRUSH)
		{
			entityNum = 1022;
		}
		else if (v9 == TRACE_HITTYPE_ENTITY)
		{
			entityNum = trace->hitId;
		}
		else
		{
			entityNum = 1023;
		}
		//PM_AddTouchEnt(pm, entityNum);
		pm->tracemask &= 0xFDFFFFFF;
		CG_Trace(trace, start, mins, maxs, end, passEntityNum, contentMask & 0xFDFFFFFF);
	}

	return retn;
}
cg::pmove_t* cg::PM_AddTouchEnt(pmove_t* pm, int groundEntityNum)
{
	int numtouch; // esi
	int i; // ecx
	int* touchents; // edx

	if (groundEntityNum != 1022)
	{
		numtouch = pm->numtouch;
		if (numtouch != 32)
		{
			i = 0;
			if (numtouch <= 0)
			{
			LABEL_7:
				pm->touchents[numtouch] = groundEntityNum;
				++pm->numtouch;
			}
			else
			{
				touchents = pm->touchents;
				while (*touchents != groundEntityNum)
				{
					++i;
					++touchents;
					if (i >= numtouch)
					{
						goto LABEL_7;
					}
				}
			}
		}
	}
	return pm;
}