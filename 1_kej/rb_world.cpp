#include "pch.h"


void r::RBW_TerrainClips()
{
	if (!v::mod_wcol_patch_clips.isEnabled())
		return;

	static std::vector<v3>& v = cworld.terrain.clip_points;
	vec3_t tris[3];
	BYTE col[4];
	vec3_t out;


	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
		std::cout << "v.size(): " << v.size() << '\n';
	}

	if (v.size() >= 3) {
		for (int i = 0; i < v.size() - 3; i += 3) {



			tris[0][0] = v[i].x;
			tris[0][1] = v[i].y;
			tris[0][2] = v[i].z;

			tris[1][0] = v[i + 1].x;
			tris[1][1] = v[i + 1].y;
			tris[1][2] = v[i + 1].z;

			tris[2][0] = v[i + 2].x;
			tris[2][1] = v[i + 2].y;
			tris[2][2] = v[i + 2].z;

			VectorSubtract(tris[0], clients->cgameOrigin, out);
			const float mag = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);

			if (mag > v::mod_wcol_drawdist.GetFloat())
				continue;

			R_ConvertColorToBytes(vec4_t{ 1,0,0,v::mod_wcol_alpha.GetFloat() }, col);

			RB_DrawPolyInteriors(3, tris, col, v::mod_wcol_two_sided.isEnabled(), v::mod_wcol_depth.isEnabled());
			//RB_DrawTriangleOutline(tris, vec4_t{ 255,0,0,255 }, 1, v::mod_wcol_depth.isEnabled());
		}
	}
}