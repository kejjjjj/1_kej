#pragma once

#ifndef cfghash
#define cfghash

#include "pch.h"

enum evartype_t
{
	EVAR_BOOL,
	EVAR_INT,
	EVAR_FLOAT,
	EVAR_STRING,
	EVAR_VEC2,
	EVAR_VEC3,
	EVAR_VEC4,
	EVAR_ARRAY //stores all values as floats
};

struct evar_s
{
	bool initialized; //a way to check if Evar_Register was ever called
	const char* name;
	int intValue;
	float floatValue;
	const char* stringValue;
	vec4_t vecValue;
	std::vector<float> arrayValue;
	bool enabled;
	float value;
	evartype_t type;
	evar_s* Next;
};
void Evar_Setup();

struct evar_o : evar_s
{
	evar_o() {
		this->evar = new evar_s;
	}
	~evar_o()
	{
		if (this->evar)
			delete this->evar;
	}
	void Register(const char* name, evartype_t type, float defaultValue);
	void Register(const char* name, evartype_t type, float* defaultValue);
	void Register(const char* name, evartype_t type, const char* defaultValue);
	void Register(const char* name, evartype_t type, float defaultValue, uint32_t size); //arrays


	int GetInt();
	float GetFloat();
	float GetVector(uint32_t prm);
	const char* GetString();
	bool isEnabled();

	void SetValue(float value);
	void SetValue(float* value);
	void SetValue(float* valueArray, uint32_t items, uint32_t beginIndex);
	void SetValue(const char* value);

	evar_s* evar;
	
};
evar_o* Evar_FindByName(const char* name);
std::vector<evar_s*> Evar_GetAlphabetically();

inline evar_o* evarList[256]{};
inline uint32_t evarCount;

#endif