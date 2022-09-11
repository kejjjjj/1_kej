

#include "pch.h"

evar_o* Evar_FindByName(const char* name)
{
	evar_o* evar = nullptr;

	for (uint32_t i = 0; i < evarCount; i++) {
		evar = evarList[i];
		if (!strcmp(name, evar->evar->name))
			return evar;

	}
	return evar; //returns a nullptr on purpose
}
void evar_o::Register(const char* name, evartype_t type, float defaultValue, uint32_t size) //arrays
{

	evar_s* evar = this->evar;

	if (type < evartype_t::EVAR_ARRAY || size < 1 || !evar)
		return;

	evar->arrayValue.reserve(size);
	evar->name = name;
	evar->type = type;
	evar->value = defaultValue;

	switch (type) {
	case evartype_t::EVAR_ARRAY:
		for (uint32_t i = 0; i < size; i++){
			evar->arrayValue.push_back(defaultValue);
		}
		break;
	}

	evarList[evarCount] = this;
	evar->Next = evarList[evarCount + 1];
	evarCount += 1;
	evar->initialized = true;
}
void evar_o::Register(const char* name, evartype_t type, float* defaultValue)
{
	evar_s* evar = this->evar;

	if (type < evartype_t::EVAR_VEC2 || !evar)
		return;

	evar->name = name;
	evar->type = type;
	evar->value = defaultValue[0];
	switch (type) {
	case evartype_t::EVAR_VEC2:
		evar->enabled = (bool)defaultValue[0] && (bool)defaultValue[1];
		evar->vecValue[0] = defaultValue[0];
		evar->vecValue[1] = defaultValue[1];
		break;
	case evartype_t::EVAR_VEC3:
		evar->enabled = (bool)defaultValue[0] && (bool)defaultValue[1] && (bool)defaultValue[2];
		evar->vecValue[0] = defaultValue[0];
		evar->vecValue[1] = defaultValue[1];
		evar->vecValue[2] = defaultValue[2];
		break;
	case evartype_t::EVAR_VEC4:
		evar->enabled = (bool)defaultValue[0] && (bool)defaultValue[1] && (bool)defaultValue[2] && (bool)defaultValue[3];
		evar->vecValue[0] = defaultValue[0];
		evar->vecValue[1] = defaultValue[1];
		evar->vecValue[2] = defaultValue[2];
		evar->vecValue[3] = defaultValue[3];
		break;
	case evartype_t::EVAR_ARRAY:
		for (uint32_t i = 0; i < 32; i++) {

		}
		break;
	}
	evarList[evarCount] = this;
	evar->Next = evarList[evarCount + 1];
	evarCount += 1;
	evar->initialized = true;

}
void evar_o::Register(const char* name, evartype_t type, const char* defaultValue)
{
	evar_s* evar = this->evar;

	if (type != evartype_t::EVAR_STRING || !evar)
		return;

	evar->type = evartype_t::EVAR_STRING;
	evar->name = name;
	evar->enabled = true;
	evar->value = 0;

	evar->stringValue = defaultValue;
	evarList[evarCount] = this;
	evar->Next = evarList[evarCount + 1];
	evarCount += 1;
	evar->initialized = true;
}
void evar_o::Register(const char* name, evartype_t type, float defaultValue)
{
	evar_s* evar = this->evar;

	if (!evar) {
		return;
	}

	evar->type = type;
	evar->name = name;
	evar->enabled = defaultValue != 0.0;
	evar->value = defaultValue;


	switch (type) {
	case evartype_t::EVAR_BOOL:
		evar->enabled = (bool)defaultValue;
		evar->intValue = evar->enabled;
		evar->floatValue = NULL;
		break;
	case evartype_t::EVAR_INT:
		evar->intValue = (int)defaultValue;
		evar->floatValue = NULL;
		break;
	case evartype_t::EVAR_FLOAT:
		evar->floatValue = defaultValue;
		evar->intValue = NULL;
		break;
	}
	evarList[evarCount] = this;
	evar->Next = evarList[evarCount + 1];
	evarCount += 1;
	evar->initialized = true;

	
}
void evar_o::SetValue(float value)
{
	evar_s* evar = this->evar;

	if (!evar)
		return;
	evar->value = value;
	evar->enabled = (value != 0.0);

	switch (evar->type) {
	case evartype_t::EVAR_BOOL:
		evar->intValue = evar->enabled;
		evar->floatValue = NULL;
		break;
	case evartype_t::EVAR_INT:
		evar->intValue = (int)value;
		evar->floatValue = NULL;
		break;
	case evartype_t::EVAR_FLOAT:
		evar->floatValue = value;
		evar->intValue = NULL;
		break;
	}

}
void evar_o::SetValue(const char* value)
{
	evar_s* evar = this->evar;

	if (!evar) {
		printf("setvalue(string): passed a null\n");
		return;
	}

	evar->stringValue = value;
	printf("SetValue(%s): name: [%s] at: [0x%p]\n", value, evar->name, &evar->stringValue);
}
void evar_o::SetValue(float* value)
{
	evar_s* evar = this->evar;


	if (evar->type < evartype_t::EVAR_VEC2 || !evar)
		return;



	switch (evar->type) {
	case evartype_t::EVAR_VEC2:
		evar->enabled = (bool)value[0] && (bool)value[1];
		evar->vecValue[0] = value[0];
		evar->vecValue[1] = value[1];
		break;
	case evartype_t::EVAR_VEC3:
		evar->enabled = (bool)value[0] && (bool)value[1] && (bool)value[2];
		evar->vecValue[0] = value[0];
		evar->vecValue[1] = value[1];
		evar->vecValue[2] = value[2];
		break;
	case evartype_t::EVAR_VEC4:
		evar->enabled = (bool)value[0] && (bool)value[1] && (bool)value[2] && (bool)value[3];
		evar->vecValue[0] = value[0];
		evar->vecValue[1] = value[1];
		evar->vecValue[2] = value[2];
		evar->vecValue[3] = value[3];
		break;

	}

}
void evar_o::SetValue(float* valueArray, uint32_t items, uint32_t beginIndex)
{
	evar_s* evar = this->evar;
	if (evar->type < evartype_t::EVAR_ARRAY || items > evar->arrayValue.size() || !evar)
		return;

	switch (evar->type) {
	case evartype_t::EVAR_ARRAY:
		for (uint32_t i = beginIndex; i < beginIndex + items; i++) {

			if (i >= evar->arrayValue.size())
				break;

			evar->arrayValue[i] = valueArray[i];
		}
		break;

	}

}
std::vector<evar_s*> Evar_GetAlphabetically()
{

	std::vector<std::string> evar_names;
	std::vector<evar_s*> evars;

	for (uint32_t i = 0; i < evarCount; i++) {
		evar_o* evar = evarList[i];

		if (evar)
			evar_names.push_back(evar->evar->name);
	}

	std::sort(evar_names.begin(), evar_names.end());

	for (auto& i : evar_names) {
		evar_o* evar = Evar_FindByName(i.c_str());

		if (evar)
			evars.push_back(evar->evar);
	}

	return evars;

}
void Evar_Setup()
{
	evarCount = 0;

	v::cfg::cfgDirectory = fs::GetExePath() + "\\1_kej.cfg";
	
	v::mod_velometer.Register	("1_kej_velometer",		evartype_t::EVAR_ARRAY,		(float)1, 4); //enabled, x, y, scale
	v::mod_rpg_mode.Register	("1_kej_rpg_mode",		evartype_t::EVAR_STRING,	"default");
	v::mod_coordinates.Register ("1_kej_coordinates",	evartype_t::EVAR_ARRAY,		(float)1, 4); //enabled, x, y, scale
	v::mod_hitanalyzer.Register ("1_kej_hitanalyzer",	evartype_t::EVAR_BOOL,		(float)0);


}
int evar_o::GetInt()
{
	return this->evar->intValue;
}
float evar_o::GetFloat()
{
	return this->evar->floatValue;
}
float evar_o::GetVector(uint32_t prm)
{
	return this->evar->vecValue[prm];
}
const char* evar_o::GetString()
{
	return this->evar->stringValue.c_str();
}
bool evar_o::isEnabled()
{
	return this->evar->enabled;
}