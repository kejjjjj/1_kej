#pragma once

#ifndef assman
#define assman

#include "pch.h"

namespace r
{
	inline XAssetHeader(*Material_Register_FastFile_f)(const char* name);
	XAssetHeader Material_Register_FastFile(const char* name);

	struct ass_material_s
	{
		size_t selectedIndex;
		size_t selectedTextureTable;
		bool isEditing;
		bool shaderEdit;
		Material* mtl;
		IDirect3DBaseTexture9* basemap;
		GfxImageLoadDef* loadDef;
		const char* name;

	};

	void R_AssMan_Main(bool& isOpen);
	void R_AssMan_EditMaterial(ass_material_s& mtl);
	void R_AssMan_EditShader(ass_material_s& mtl);


}

#endif