#include "pch.h"


void cg::Mod_DrawVelocity()
{
	const int32_t velocity = (int32_t)glm::length(glm::vec2(cg::clients->cgameVelocity[0], cg::clients->cgameVelocity[1]));
	static int32_t velocity_prev_frame = velocity;

	static DWORD ms = Sys_MilliSeconds();
	const DWORD timePassed = Sys_MilliSeconds() - ms;

	static glm::vec4 col{};

	if (timePassed > cgs->frametime) {
		ms = Sys_MilliSeconds();
		col.a = 255;
		if (velocity > velocity_prev_frame) {
			col.r = 0;
			col.g = 255;
			col.b = 0;
		}
		else if (velocity < velocity_prev_frame) {
			col.r = 255;
			col.g = 0;
			col.b = 0;
		}
		else {
			col.r = 255;
			col.g = 255;
			col.b = 0;
		}

		velocity_prev_frame = velocity;

	}

	char buffer[1024];
	sprintf_s(buffer, "%i", velocity);
	r::R_DrawText(buffer, 960, 540, 3, 3, 0, (float*)&col, 0);
}