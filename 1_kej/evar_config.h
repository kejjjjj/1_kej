#pragma once


#ifndef evarload
#define evarload

#include "pch.h"

bool Evar_SaveToFile(std::string directory);
bool Evar_LoadFromFile(std::string directory);

//call this if the evar is a vector/array type when loading from a text file
bool Evar_LoadVector(std::fstream& f, evar_s* evar, vec4_t vec);
#endif