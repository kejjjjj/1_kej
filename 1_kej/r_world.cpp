#include "pch.h"

bool r::WorldToScreen(vec3_t vWorldLocation, vec2_t xy)
{
	int centerX = cg::cgs->refdef.width / 2;
	int centerY = cg::cgs->refdef.height / 2;

	cg::refdef_s* ref = &cg::cgs->refdef;

	vec3_t vLocal, vTransForm;
	vec3_t vright(ref->viewaxis[1][0], ref->viewaxis[1][1], ref->viewaxis[1][2]);
	vec3_t vup(ref->viewaxis[2][0], ref->viewaxis[2][1], ref->viewaxis[2][2]);
	vec3_t vfwd(ref->viewaxis[0][0], ref->viewaxis[0][1], ref->viewaxis[0][2]);

	

	VectorSubtract(vWorldLocation, cg::cgs->refdef.vieworg, vLocal);

	vTransForm[0] = DotProduct(vLocal, vright);
	vTransForm[1] = DotProduct(vLocal, vup);
	vTransForm[2] = DotProduct(vLocal, vfwd);

	if (vTransForm[2] < 0.01) {
		return 0;
	}

	if (xy) {
		xy[0] = centerX * (1 - (vTransForm[0] / ref->tanHalfFovX / vTransForm[2]));
		xy[1] = centerY * (1 - (vTransForm[1] / ref->tanHalfFovY / vTransForm[2]));
	}

	return  vTransForm[2] > 0;
}
HRESULT r::R_DrawXModelSkinnedCached(GfxCmdBufSourceState* src, GfxCmdBufState* state, GfxModelSkinnedSurface* modelSurf)
{
	if(!v::mod_chams.isEnabled())
		return R_DrawXModelSkinnedCached_h(src, state, modelSurf);

	const auto R_GetD3D9TextureDataWithColor = [](BYTE r, BYTE g, BYTE b, BYTE* buffer) -> void {
		BYTE col[60] =
		{
			  0x42, 0x4D, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
			  0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
			  0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  b, g, r, 0x00, 0x00, 0x00
		};

		memcpy_s(buffer, 60, &col, 60);
	};

	static bool create = false;


	static vec3_t old_col = { v::mod_chams_col.GetVector(0),	v::mod_chams_col.GetVector(1),	v::mod_chams_col.GetVector(2)	},
				  old_zcol	{ v::mod_chams_zcol.GetVector(0),	v::mod_chams_zcol.GetVector(1),	v::mod_chams_zcol.GetVector(2)	};

	const bool colChanged = (old_col[0]  != v::mod_chams_col.GetVector(0)  || old_col[1] != v::mod_chams_col.GetVector(1)   || old_col[2] != v::mod_chams_col.GetVector(2)) ||
							(old_zcol[0] != v::mod_chams_zcol.GetVector(0) || old_zcol[1] != v::mod_chams_zcol.GetVector(1) || old_zcol[2] != v::mod_chams_zcol.GetVector(2));

	if (!create || colChanged || !tex_Z && !tex_noZ) {

		if (tex_Z)
			tex_Z->Release();
		if (tex_noZ)
			tex_noZ->Release();

		VectorCopy(v::mod_chams_col.evar->vecValue, old_col);
		VectorCopy(v::mod_chams_zcol.evar->vecValue, old_zcol);

		BYTE col[60]{};

		R_GetD3D9TextureDataWithColor(v::mod_chams_col.GetVector(0) * 255, v::mod_chams_col.GetVector(1) * 255, v::mod_chams_col.GetVector(2) * 255, col);
		D3DXCreateTextureFromFileInMemory(cg::dx->device, (LPCVOID)&col, 60, &tex_noZ);

		R_GetD3D9TextureDataWithColor(v::mod_chams_zcol.GetVector(0) * 255, v::mod_chams_zcol.GetVector(1) * 255, v::mod_chams_zcol.GetVector(2) * 255, col);
		D3DXCreateTextureFromFileInMemory(cg::dx->device, (LPCVOID)&col, 60, &tex_Z);

		create = true;

	}

	if(v::mod_chams_wireframe.isEnabled())
		cg::dx->device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (v::mod_chams_z.isEnabled()) {
		cg::dx->device->SetRenderState(D3DRS_ZENABLE, false);
		cg::dx->device->SetTexture(0, tex_Z);
		R_DrawXModelSkinnedCached_h(src, state, modelSurf);

	}

	if (v::mod_chams_wireframe.isEnabled())
		cg::dx->device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);


	cg::dx->device->SetRenderState(D3DRS_ZENABLE, true);
	cg::dx->device->SetTexture(0, tex_noZ);
	

	R_DrawXModelSkinnedCached_h(src, state, modelSurf);


	cg::dx->device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}