#pragma once

#ifndef cmodexport
#define cmodexport

#include "pch.h"

namespace cg
{
	struct exp_s
	{
		uint32_t brush = 0;
		uint32_t entity = 0;
		vec3_t A1{}, B1{}, C1{};
		uint16_t vert = 0;
		uint16_t vertCount = 0;
	};

	inline vec3_t exp_mins, exp_maxs, exp_origin;

	class MapExport
	{
	public:
		MapExport();
		~MapExport() { fs::F_CloseFile(f); }
		bool EXP_BeginExport();
	private:
		
		bool EXP_BeginExportB();
		void EXP_WriteHeader();
		bool EXP_ExportLeaves();
		void EXP_ExportSurfaces();

		void EXP_WriteTriangle(const vec3_t A, const vec3_t B, const vec3_t C, const std::string& texture);

		std::fstream f;
		bool ready = false;
		exp_s e;
	};


}

#endif