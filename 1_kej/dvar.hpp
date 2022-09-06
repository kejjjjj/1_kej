#pragma once

#ifndef __dvar
#define __dvar

#include "pch.h"

#pragma once
#include "pch.h"

#ifndef dvar_s_
#define dvar_s_

union DvarLimits
{
	struct
	{
		int stringCount;
		const char** strings;
	} enumeration;

	struct
	{
		int min;
		int max;
	} integer;

	struct
	{
		float min;
		float max;
	} value;

	struct
	{
		float min;
		float max;
	} vector;
};

union DvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	float value;
	float vector[4];
	const char* string;
	char color[4];
};

enum DvarType
{
	DVAR_TYPE_BOOL = 0x0,
	DVAR_TYPE_FLOAT = 0x1,
	DVAR_TYPE_FLOAT_2 = 0x2,
	DVAR_TYPE_FLOAT_3 = 0x3,
	DVAR_TYPE_FLOAT_4 = 0x4,
	DVAR_TYPE_INT = 0x5,
	DVAR_TYPE_ENUM = 0x6,
	DVAR_TYPE_STRING = 0x7,
	DVAR_TYPE_COLOR = 0x8,
	DVAR_TYPE_COUNT = 0x9,
};

enum class dvar_type : std::int8_t
{
	boolean = 0,
	value = 1,
	vec2 = 2,
	vec3 = 3,
	vec4 = 4,
	integer = 5,
	enumeration = 6,
	string = 7,
	color = 8,
	rgb = 9 // Color without alpha
};

//enum dvar_flags : std::uint16_t
//{
//	none = 0,
//	saved = 1 << 0,
//	latched = 1 << 1,
//	cheat_protected = 1 << 2,
//	replicated = 1 << 3,
//	user_created = 1 << 8,
//	user_info = 1 << 9,
//	server_info = 1 << 10,
//	write_protected = 1 << 11,
//	read_only = 1 << 13,
//	auto_exec = 1 << 15,
//	printable = 1 << 16,
//};

enum dvar_flags : std::uint16_t
{
	none = 0x0,
	saved = 0x1,
	user_info = 0x2, // sent to server on connect or change
	server_info = 0x4, // sent in response to front end requests
	replicated = 0x8,
	write_protected = 0x10,
	latched = 0x20,
	read_only = 0x40,
	cheat_protected = 0x80,
	temp = 0x100,
	no_restart = 0x400, // do not clear when a cvar_restart is issued
	user_created = 0x4000, // created by a set command
};

struct dvar_s
{
	const char* name;
	const char* description;
	//unsigned __int16 flags;
	dvar_flags flags;
	//char type;
	dvar_type type;
	bool modified;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	bool(__cdecl* domainFunc)(dvar_s*, DvarValue);
	dvar_s* hashNext;
};

dvar_s* Dvar_FindMalleableVar(const char* name);
dvar_s* Dvar_RegisterNew(const char* name, dvar_type type, int flags, const char* description, DvarValue defaultValue, DvarLimits domain);
dvar_s* Dvar_Reregister(dvar_s* dvar, const char* name, dvar_type type, int flags, const char* description, DvarValue defaultValue, DvarLimits domain);
dvar_s* Dvar_RegisterEnum(const char* dvarName, int defaultIdx, int flags, const char* description, DvarLimits strings);

void Dvar_Init();
#endif

#endif
