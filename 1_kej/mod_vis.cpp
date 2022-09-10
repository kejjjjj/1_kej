#include "pch.h"


void cg::Mod_DrawVelocity()
{
	if (!v::mod_velometer.isEnabled())
		return;

	const int32_t velocity = (int32_t)glm::length(glm::vec2(cg::clients->cgameVelocity[0], cg::clients->cgameVelocity[1]));
	static int32_t velocity_prev_frame = velocity;

	static DWORD ms = Sys_MilliSeconds();
	const DWORD timePassed = Sys_MilliSeconds() - ms;

	static glm::vec4 col{};

	if (timePassed > (1000.f / cgs->frametime) / 10) {
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

	char buffer[10];
	sprintf_s(buffer, "%i", velocity);
	r::R_DrawText(buffer, v::mod_velometer.evar->arrayValue[1], v::mod_velometer.evar->arrayValue[2], v::mod_velometer.evar->arrayValue[3], v::mod_velometer.evar->arrayValue[3], 0, (float*)&col, 0);
}
void cg::Mod_DrawCoordinates()
{
	if (!v::mod_coordinates.isEnabled())
		return;

	char buffer[128];
	static glm::vec4 col{};

	sprintf_s(buffer, "x:     %.6f\ny:     %.6f\nz:     %.6f\nyaw: %.6f", clients->cgameOrigin[0], clients->cgameOrigin[1], clients->cgameOrigin[2], cgs->refdefViewAngles[YAW]);

	col.r = 0;
	col.g = 255;
	col.b = 0;
	col.w = 255;

	if (clients->cgameOrigin[0] == (int)clients->cgameOrigin[0] || clients->cgameOrigin[1] == (int)clients->cgameOrigin[1])
		col.b = 255;

	r::R_DrawText(buffer, v::mod_coordinates.evar->arrayValue[1], v::mod_coordinates.evar->arrayValue[2], v::mod_coordinates.evar->arrayValue[3], v::mod_coordinates.evar->arrayValue[3], 0, (float*)&col, 0);

}