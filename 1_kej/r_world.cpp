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