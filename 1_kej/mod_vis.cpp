#include "pch.h"

void cg::Mod_DrawEvents()
{
	if (analyzer.isRecording() || analyzer.isSegmenting()) {
		const bool isPaused = analyzer.RecordingPaused();

		char buffer[30];

		const char* const mode = analyzer.isSegmenting() == true ? "Segmenting" : "Recording";

		sprintf_s(buffer, "%s", isPaused == false ? mode : "Paused");

		r::R_DrawText(buffer, 0, 800, 2, 2, 0, isPaused == false ? vec4_t{ 1,1,1,1 } : vec4_t{ 1,0,0,1 }, 0);
	}
	if (automation.pendingSlide) {

		Material* fxMaterial = r::R_RegisterMaterial("decode_characters");
		Material* fxMaterialGlow = r::R_RegisterMaterial("decode_characters_glow");

		r::R_AddCmdDrawTextWithEffects((char*)"Slide", "fonts/objectivefont", r::X(v::mod_velometer.GetArray(1)), r::Y(v::mod_velometer.GetArray(2) - 40) , v::mod_velometer.GetArray(3), v::mod_velometer.GetArray(3), 0.f, vec4_t{ 0,1,0,1 }, 3, v::mod_velometer_glow.evar->vecValue, fxMaterial, fxMaterialGlow, 0, 500, 1000, 2000);


		//r::R_DrawText("Slide", v::mod_velometer.GetArray(1), v::mod_velometer.GetArray(2) - 20 * v::mod_velometer.GetArray(3), v::mod_velometer.GetArray(3), v::mod_velometer.GetArray(3), 0, vec4_t{ 0,1,0,1 }, 0);
	}
}
void cg::Mod_DrawVelocity()
{
	if (!v::mod_velometer.isEnabled())
		return;


	int32_t velocity;

	if (analyzer.isPreviewing() && (analyzer.RecordingExists() || analyzer.Segmenter_RecordingExists())) {
		jump_data* jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);
		
		float x{}, y{};

		if (jData) {
			x = jData->velocity[0];
			y = jData->velocity[1];
		}

		velocity = (int32_t)glm::length(glm::vec2(x, y));
	}
	else 
		velocity = (int32_t)glm::length(glm::vec2(cg::clients->cgameVelocity[0], cg::clients->cgameVelocity[1]));

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

	char buffer[20];
	if(!v::mod_showFPS.isEnabled())
		sprintf_s(buffer, "%i", velocity);
	else
		sprintf_s(buffer, "%i\n%i %s", velocity, jumpanalyzer.recommendedFPS, GetAsyncKeyState(VK_SPACE) < 0 == true && v::mod_autoFPS_space333.isEnabled() && VID_ACTIVE ? "(hold 333)" : "");

	buffer[19] = '\0';
	//r::R_DrawText(buffer, "fonts/normalfont", v::mod_velometer.evar->arrayValue[1], v::mod_velometer.evar->arrayValue[2], v::mod_velometer.evar->arrayValue[3], v::mod_velometer.evar->arrayValue[3], 0, (float*)&col, 1);
	
	Material* fxMaterial = r::R_RegisterMaterial("decode_characters");
	Material* fxMaterialGlow = r::R_RegisterMaterial("decode_characters_glow");

	r::R_AddCmdDrawTextWithEffects(buffer, "fonts/objectivefont", r::X(v::mod_velometer.GetArray(1)), r::Y(v::mod_velometer.GetArray(2)), v::mod_velometer.GetArray(3), v::mod_velometer.GetArray(3), 0.f, (float*)&col, 3, v::mod_velometer_glow.evar->vecValue, fxMaterial, fxMaterialGlow, 0, 500, 1000, 2000);


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

	r::R_AddCmdDrawTextWithEffects(buffer, "fonts/normalfont", r::X(v::mod_coordinates.GetArray(1)), r::Y(v::mod_coordinates.GetArray(2)), v::mod_coordinates.GetArray(3), v::mod_coordinates.GetArray(3), 0.f, vec4_t{0,1,0,1}, 3, vec4_t{1,1,1,0}, 0, 0, 0, 0, 0, 0);


	//r::R_DrawText(buffer, v::mod_coordinates.evar->arrayValue[1], v::mod_coordinates.evar->arrayValue[2], v::mod_coordinates.evar->arrayValue[3], v::mod_coordinates.evar->arrayValue[3], 0, (float*)&col, 0);

}
#define BANGLE2COLOR( x )  ( (int)( ( x ) * 255.f / 35 ) & 255 )

void cg::Mod_DrawSurfaceInfo()
{
	if (!v::mod_elevatable_surf.isEnabled() && !v::mod_bounceable_surf.isEnabled())
		return;

	trace_t trace;
	const vec3_t mins = { -1,-1,-1 };
	const vec3_t maxs = { 1, 1, 1 };
	vec3_t angles;

	const auto _AnglesToForward = [](vec3_t angles, vec3_t out) -> void { //loses a lot of precision when scaled a lot
		float fwd = angles[1] * (PI / 180);
		const float ycos = cos(fwd);
		const float ysin = sin(fwd);

		fwd = angles[0] * (PI / 180);
		const float xcos = cos(fwd);
		const float xsin = sin(fwd);

		out[0] = xcos * ycos;
		out[1] = xcos * ysin;
		out[2] = -xsin;
	};

	//_AnglesToForward(clients->cgameViewangles, angles);
	//VectorScale(angles, 999999, angles);
	AnglesToForward(clients->cgameViewangles, rg->viewOrg, 99999, angles);
	CG_TracePoint(maxs, &trace, rg->viewOrg, mins, angles, cgs->clientNum, MASK_PLAYERSOLID, 0, 1);

	const float normalX = trace.normal[0] >= 0.f ? trace.normal[0] : -trace.normal[0];
	const float normalY = trace.normal[1] >= 0.f ? trace.normal[1] : -trace.normal[1];


	if (trace.normal[2] >= .3f && trace.normal[2] <= .7f && v::mod_bounceable_surf.isEnabled()) {
		char buffer[64];
		const float bAngle = (90.f + trace.normal[2] * 90.f) - 117;
		const float _col = (bAngle / 36.f);
		sprintf_s(buffer, "bounce (+%.6f)", bAngle); //as long as it gives an idea of the angle :blush:

		vec4_t col;
		col[0] = 0.f + (_col);
		col[1] = 1.f - (_col);
		col[2] = 0.f;
		col[3] = 1.f;

		r::R_DrawText(buffer, 960, 700, 1.6f, 1.6f, 0.f, col, 0);

	}
	else if ((normalX == 1.f || normalY == 1.f) && v::mod_elevatable_surf.isEnabled()) {
		char buffer[48];
		vec3_t endpos{}, out{};

		endpos[0] = rg->viewOrg[0] + trace.fraction * (angles[0] - rg->viewOrg[0]);
		endpos[1] = rg->viewOrg[1] + trace.fraction * (angles[1] - rg->viewOrg[1]);
		endpos[2] = rg->viewOrg[2] + trace.fraction * (angles[2] - rg->viewOrg[2]);

		vec3_t normals, out2;
		VectorCopy(trace.normal, normals);
		vectoangles(normals, normals);

		AnglesToForward(normals, endpos, -1.1, out2);

		VectorClear(angles);		 
		angles[YAW] = normalX == 1.f ? (trace.normal[0] > 0  ? -180 : 0) : (trace.normal[1] > 0 ? -90 : 90);
		_AnglesToForward(angles, out);
		VectorScale(out, 0.125, out);
		VectorAdd(out, endpos, out);
		VectorAddAll(out, angles[YAW] < 0 ? 14 : -14, out);
		CG_TracePoint(maxs, &trace, out2, mins, out, cgs->clientNum, MASK_PLAYERSOLID, 0, 1);

		if (trace.startsolid) {
			sprintf_s(buffer, "elevator (%c: %.6f)", normalX == 1.f ? 'X' : 'Y', normalX == 1.f ? out[0] : out[1]);

			r::R_DrawText(buffer, 960, 700, 1.6f, 1.6f, 0.f, vec4_t{ 0,1,0,1 }, 0); //can never be true when bounce is true, so draw on top of it
		}

	}
}
//#define BAR_START_Y 490
//#define BAR_HEIGHT 10
void cg::Mod_DrawFPSHelpers()
{
	constexpr static float length_marker250 = 1.f;

	static bool rightmove{};

	const usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);


	if (cmd->rightmove > 0)
		rightmove = true;
	else if (cmd->rightmove < 0)
		rightmove = false;


	FPS_CalculateSingleBeatDirection(rightmove, cmd);

	float yaw = clients->cgameViewangles[YAW] > 0 ? clients->cgameViewangles[YAW] : 180.f - clients->cgameViewangles[YAW] * -1; //mirror the yaw
	float aa = atan2(-(int)cmd->rightmove, (int)cmd->forwardmove) * 57.2957795f;
	const dvar_s* _fov = Dvar_FindMalleableVar("cg_fov");
	const dvar_s* fovscale = Dvar_FindMalleableVar("cg_fovscale");

	const float fov = _fov->current.value * fovscale->current.value * v::mod_fps_transferz.evar->arrayValue[3];
	bool isInverted = clients->cgameViewangles[YAW] < fov || clients->cgameViewangles[YAW] > 180.f - fov;

	if (analyzer.isPreviewing() || jbuilder.isEditing()) {

		jump_data* jData;
		if (analyzer.isPreviewing())
			jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);
		else
			jData = jbuilder.FetchFrameData(jbuilder.preview_frame);


		if (jData) {
			aa = atan2(-(int)jData->rightmove, (int)jData->forwardmove) * 57.2957795f;
			yaw = jData->angles[YAW] > 0 ? jData->angles[YAW] : 180.f - jData->angles[YAW] * -1;
			rightmove = jData->rightmove > 0;
			isInverted = jData->angles[YAW] < fov || jData->angles[YAW] > 180.f - fov;
		}

	}

	aa > 0 ? aa -= 45 : aa += 45;

	static const float m250 = 86.f;
	vec2_t marker250 = { m250, 90.f + m250 };
	vec2_t zone125 = { fps_zones.fps125, 90.f + fps_zones.fps125 };
	vec2_t zone200 = { fps_zones.fps200, 90.f + fps_zones.fps200 };
	vec2_t zone250 = { fps_zones.fps250, 90.f + fps_zones.fps250 };
	vec2_t zone333 = { fps_zones.fps333, 90.f + fps_zones.fps333 };

	if (rightmove) {
		marker250[0] = 180.f - marker250[0] - length_marker250;
		marker250[1] = 180.f - marker250[1] - length_marker250;
		zone125[0] = 180.f - zone125[0] - fps_zones.length125;
		zone125[1] = 180.f - zone125[1] - fps_zones.length125;
		zone200[0] = 180.f - zone200[0] - fps_zones.length200;
		zone200[1] = 180.f - zone200[1] - fps_zones.length200;
		zone250[0] = 180.f - zone250[0] - fps_zones.length250;
		zone250[1] = 180.f - zone250[1] - fps_zones.length250;
		//yaw -= 10;
	}

	yaw = AngleNormalize180(yaw += aa);
	if (yaw < 0)
		yaw = 180.f - fabs(yaw);


	
	//r::R_DrawRect("white", 0, BAR_START_Y, 1920, 10, vec4_t{ 1,1,1,100 });

	const float BAR_START_Y = v::mod_fps_transferz.evar->arrayValue[1];
	const float BAR_HEIGHT = v::mod_fps_transferz.evar->arrayValue[2];



	float &DistanceFromZone = mod_fps.DistanceToTransferZone;
	const bool isLong125 = v::mod_autoFPS_long125.isEnabled();


	if (isInverted) {
		if (v::mod_fps_transferz.evar->arrayValue[0] != NULL) {

			if (!isLong125) {
				CG_FillAngleYaw(-180.f + zone125[0], -180.f + (zone125[0] + fps_zones.length125), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_125col.evar->vecValue);
				CG_FillAngleYaw(-180.f + zone125[1], -180.f + (zone125[1] + fps_zones.length125), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_125col.evar->vecValue);
			}
			else {
				CG_FillAngleYaw(-180.f + zone333[0], -180.f + (zone333[0] + fps_zones.length333), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_333col.evar->vecValue);
				CG_FillAngleYaw(-180.f + zone333[1], -180.f + (zone333[1] + fps_zones.length333), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_333col.evar->vecValue);
			}

			CG_FillAngleYaw(-180.f + zone250[0], -180.f + (zone250[0] + fps_zones.length250), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_250col.evar->vecValue);
			CG_FillAngleYaw(-180.f + zone250[1], -180.f + (zone250[1] + fps_zones.length250), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_250col.evar->vecValue);

			CG_FillAngleYaw(-180.f + zone200[0], -180.f + (zone200[0] + fps_zones.length200), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_200col.evar->vecValue);
			CG_FillAngleYaw(-180.f + zone200[1], -180.f + (zone200[1] + fps_zones.length200), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_200col.evar->vecValue);

			if (!isLong125) {
				CG_FillAngleYaw(-180.f + zone333[0], -180.f + (zone333[0] + fps_zones.length333), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_333col.evar->vecValue);
				CG_FillAngleYaw(-180.f + zone333[1], -180.f + (zone333[1] + fps_zones.length333), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_333col.evar->vecValue);
			}
			else {
				CG_FillAngleYaw(-180.f + zone125[0], -180.f + (zone125[0] + fps_zones.length125), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_125col.evar->vecValue);
				CG_FillAngleYaw(-180.f + zone125[1], -180.f + (zone125[1] + fps_zones.length125), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_125col.evar->vecValue);
			}

			CG_FillAngleYaw(-180.f + marker250[0], -180.f + (marker250[0] + length_marker250), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_markercol.evar->vecValue);
			CG_FillAngleYaw(-180.f + marker250[1], -180.f + (marker250[1] + length_marker250), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_markercol.evar->vecValue);

		}
		DistanceFromZone = (rightmove == false) ? yaw - (-180.f + marker250[0]) : yaw - (-180.f + (marker250[0] + length_marker250));

	} else {

		DistanceFromZone = (rightmove == false) ? yaw - marker250[0] : yaw - (marker250[0] + length_marker250);

	}
	if (DistanceFromZone < 0.f)
		DistanceFromZone = 90.f + DistanceFromZone;


	if (v::mod_fps_transferz.evar->arrayValue[0] != NULL) {
		if (!isLong125) {
			CG_FillAngleYaw(zone125[0], (zone125[0] + fps_zones.length125), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_125col.evar->vecValue);
			CG_FillAngleYaw(zone125[1], (zone125[1] + fps_zones.length125), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_125col.evar->vecValue);
		}
		else {
			CG_FillAngleYaw(zone333[0], (zone333[0] + fps_zones.length333), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_333col.evar->vecValue);
			CG_FillAngleYaw(zone333[1], (zone333[1] + fps_zones.length333), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_333col.evar->vecValue);

		}

		CG_FillAngleYaw(zone250[0], (zone250[0] + fps_zones.length250), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_250col.evar->vecValue);
		CG_FillAngleYaw(zone250[1], (zone250[1] + fps_zones.length250), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_250col.evar->vecValue);

		CG_FillAngleYaw(zone200[0], (zone200[0] + fps_zones.length200), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_200col.evar->vecValue);
		CG_FillAngleYaw(zone200[1], (zone200[1] + fps_zones.length200), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_200col.evar->vecValue);

		if (!isLong125) {
			CG_FillAngleYaw(zone333[0], (zone333[0] + fps_zones.length333), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_333col.evar->vecValue);
			CG_FillAngleYaw(zone333[1], (zone333[1] + fps_zones.length333), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_333col.evar->vecValue);
		}
		else {
			CG_FillAngleYaw(zone125[0], (zone125[0] + fps_zones.length125), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_125col.evar->vecValue);
			CG_FillAngleYaw(zone125[1], (zone125[1] + fps_zones.length125), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_125col.evar->vecValue);
		}
	
		CG_FillAngleYaw(marker250[0], (marker250[0] + length_marker250), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_markercol.evar->vecValue);
		CG_FillAngleYaw(marker250[1], (marker250[1] + length_marker250), yaw, BAR_START_Y, BAR_HEIGHT, fov, v::mod_markercol.evar->vecValue);
	}

	DistanceFromZone = fmodf(DistanceFromZone, 90);

	if (!rightmove)
		DistanceFromZone = 90.f - DistanceFromZone;


	if (v::mod_fps_transferz.evar->arrayValue[0] != NULL)
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(r::X(958), r::Y(BAR_START_Y - 10)), ImVec2(r::X(962), r::Y(BAR_HEIGHT + BAR_START_Y + 10)), ImColor(1.f, 1.f, 1.f, 1.f));
		//r::R_DrawRect("white", 958, BAR_START_Y - 10, 4, BAR_HEIGHT + 20, vec4_t{ 1,1,1,255 });


	range_t ranges, ranges2;

	if (!isLong125) {
		ranges = AnglesToRange(DEG2RAD(zone333[0]), DEG2RAD(zone333[0] + fps_zones.length333), DEG2RAD(fmodf(yaw, 90)), fov);
		ranges2 = AnglesToRange(DEG2RAD(zone333[1]), DEG2RAD(zone333[1] + fps_zones.length333), DEG2RAD(fmodf(yaw, 90)), fov);
	}
	else {
		ranges = AnglesToRange(DEG2RAD(zone125[0]), DEG2RAD(zone125[0] + fps_zones.length125), DEG2RAD(fmodf(yaw, 90)), fov);
		ranges2 = AnglesToRange(DEG2RAD(zone125[1]), DEG2RAD(zone125[1] + fps_zones.length125), DEG2RAD(fmodf(yaw, 90)), fov);
	}

	if (ranges.x1 <= 960 && ranges.x2 > 960 || ranges2.x1 <= 960 && ranges2.x2 > 960) {
		jumpanalyzer.recommendedFPS = isLong125 == false ? 333 : 125;
		return;
	}

	if (!isLong125) {
		ranges = AnglesToRange(DEG2RAD(zone125[0]), DEG2RAD(zone125[0] + fps_zones.length125), DEG2RAD(fmodf(yaw, 90)), fov);
		ranges2 = AnglesToRange(DEG2RAD(zone125[1]), DEG2RAD(zone125[1] + fps_zones.length125), DEG2RAD(fmodf(yaw, 90)), fov);
	}
	else {
		ranges = AnglesToRange(DEG2RAD(zone333[0]), DEG2RAD(zone333[0] + fps_zones.length333), DEG2RAD(fmodf(yaw, 90)), fov);
		ranges2 = AnglesToRange(DEG2RAD(zone333[1]), DEG2RAD(zone333[1] + fps_zones.length333), DEG2RAD(fmodf(yaw, 90)), fov);
	}

	if (ranges.x1 <= 960 && ranges.x2 > 960 || ranges2.x1 <= 960 && ranges2.x2 > 960) {
		jumpanalyzer.recommendedFPS = isLong125 == false ? 125 : 333;
		return;
	}

	ranges = AnglesToRange(DEG2RAD(zone200[0]), DEG2RAD(zone200[0] + fps_zones.length200), DEG2RAD(fmodf(yaw, 90)), fov);
	ranges2 = AnglesToRange(DEG2RAD(zone200[1]), DEG2RAD(zone200[1] + fps_zones.length200), DEG2RAD(fmodf(yaw, 90)), fov);

	if (ranges.x1 <= 960 && ranges.x2 > 960 || ranges2.x1 <= 960 && ranges2.x2 > 960) {
		jumpanalyzer.recommendedFPS = 200;
		return;
	}

	ranges = AnglesToRange(DEG2RAD(zone250[0]), DEG2RAD(zone250[0] + fps_zones.length250), DEG2RAD(fmodf(yaw, 90)), fov);
	ranges2 = AnglesToRange(DEG2RAD(zone250[1]), DEG2RAD(zone250[1] + fps_zones.length250), DEG2RAD(fmodf(yaw, 90)), fov);

	if (ranges.x1 <= 960 && ranges.x2 > 960 || ranges2.x1 <= 960 && ranges2.x2 > 960) {
		jumpanalyzer.recommendedFPS = 250;
		return;
	}
	

}
void cg::FPS_CalculateSingleBeatDirection(bool& rightmove, const usercmd_s* cmd)
{
	static uint16_t frames = NULL;
	static vec_t oldYaw = NULL;
	static bool _rightmove;
	const vec_t newYaw = cgs->refdefViewAngles[YAW];

	frames += 1;

	if (frames >= 4) {
		frames = 0;

		if (oldYaw < newYaw && cmd->forwardmove != 0 && cmd->rightmove == 0 && rightmove)
			_rightmove = false;
		else if (oldYaw > newYaw && cmd->forwardmove != 0 && cmd->rightmove == 0 && !rightmove)
			_rightmove = true;
		oldYaw = newYaw;
	}
	if(cmd->rightmove == 0)
		rightmove = _rightmove;
}
void cg::Mod_DrawVelocityDirection()
{
	if (!v::mod_veldirection.isEnabled() || NOT_SERVER)
		return;


	vec3_t orgPos;
	const jump_data* jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);

	if (analyzer.isPreviewing()) {

		if (jData) {
			VectorCopy(jData->origin, orgPos);
		}
		else
			VectorCopy(clients->cgameOrigin, orgPos);
	}
	else
		VectorCopy(clients->cgameOrigin, orgPos);

	float velAngle = atan2(clients->cgameVelocity[1], clients->cgameVelocity[0]) * 180.f / PI;

	if (analyzer.isPreviewing()) {

		if (jData) {
			velAngle = atan2(jData->velocity[1], jData->velocity[0]) * 180.f / PI;

		}

	}

	vec3_t angles = { 0, velAngle, 0 }, end;
	AnglesToForward(angles, orgPos, 100, end);
	vec2_t self_xy, end_xy;
	if (r::WorldToScreen(orgPos, self_xy) && r::WorldToScreen(end, end_xy)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(end_xy[0], end_xy[1]), ImVec2(self_xy[0], self_xy[1]), IM_COL32(255, 255, 0, 255), 1.5f);
	}
}
#define DIRECTION_LENGTH 2000
void cg::Mod_DrawWorldAxes()
{
	if (!v::mod_show_worldaxes.isEnabled() || NOT_SERVER)
		return;

	vec3_t forwardStart, start;

	vec3_t orgPos;

	if (analyzer.isPreviewing()) {
		const jump_data* jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);

		if (jData) {
			VectorCopy(jData->origin, orgPos);
		}
		else
			VectorCopy(clients->cgameOrigin, orgPos);
	}else
		VectorCopy(clients->cgameOrigin, orgPos);


	VectorCopy(orgPos, forwardStart);
	VectorCopy(orgPos, start);

	forwardStart[0] -= DIRECTION_LENGTH;

	const float pitch = clients->cgameViewangles[PITCH];

	start[2] -= 1000;
	forwardStart[2] -= 1000;


	if (pitch < 0) {
		start[0] -= fabs(pitch) * 50;
	}

	vec2_t self_xy, end_xy, nearest_xy;
	if (r::WorldToScreen(forwardStart, self_xy) && r::WorldToScreen(start, end_xy)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(end_xy[0], end_xy[1]), ImVec2(self_xy[0], self_xy[1]), IM_COL32(255, 0, 0, 255), 2.f);
	}
	start[0] = orgPos[0];
	if (pitch < 0) {
		start[0] += fabs(pitch) * 50;
	}
	forwardStart[0] += DIRECTION_LENGTH * 2;
	if (r::WorldToScreen(forwardStart, self_xy) && r::WorldToScreen(start, end_xy)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(end_xy[0], end_xy[1]), ImVec2(self_xy[0], self_xy[1]), IM_COL32(255, 0, 0, 255), 2.f);
	}
	VectorCopy(orgPos, forwardStart);
	forwardStart[2] -= 1000;


	//Y
	forwardStart[1] -= DIRECTION_LENGTH;
	if (pitch < 0) {
		start[1] -= fabs(pitch) * 50;
	}

	if (r::WorldToScreen(forwardStart, self_xy) && r::WorldToScreen(start, end_xy)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(end_xy[0], end_xy[1]), ImVec2(self_xy[0], self_xy[1]), IM_COL32(255, 0, 0, 255), 2.f);
	}
	start[1] = orgPos[1];
	if (pitch < 0) {
		start[1] += fabs(pitch) * 50;
	}
	forwardStart[1] += DIRECTION_LENGTH * 2;
	if (r::WorldToScreen(forwardStart, self_xy) && r::WorldToScreen(start, end_xy)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(end_xy[0], end_xy[1]), ImVec2(self_xy[0], self_xy[1]), IM_COL32(255, 0, 0, 255), 2.f);
	}

	VectorCopy(orgPos, forwardStart);
	forwardStart[2] -= 1000;

	if (!v::mod_worldaxes_opt.isEnabled())
		return;

	const usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);

	static bool rightmove;

	if (cmd->rightmove > 0)
		rightmove = true;
	else if (cmd->rightmove < 0)
		rightmove = false;

	FPS_CalculateSingleBeatDirection(rightmove, cmd);
	jump_data* jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);
	if (analyzer.isPreviewing()) {

		if (jData) {
			rightmove = jData->rightmove > 0;
		}

	}

	float delta;
	float opt;
	if(!analyzer.isPreviewing())
		opt = R_getOptAngle(rightmove, delta);

	else {
		if (jData)
			opt = getOptForAnalyzer(jData, GROUND);
		else
			opt = R_getOptAngle(rightmove, delta);

	}
	vec3_t opt3, nearestAxis3;
	AnglesToForward(vec3_t{ 0, opt, 0 }, forwardStart, DIRECTION_LENGTH, opt3);

	axis_s nearestAxis = CG_GetNearestWorldAxisFromYaw(opt);

	AnglesToForward(vec3_t{ 0, nearestAxis.angle, 0 }, forwardStart, DIRECTION_LENGTH, nearestAxis3);


	if (r::WorldToScreen(opt3, self_xy) && r::WorldToScreen(start, end_xy) && r::WorldToScreen(nearestAxis3, nearest_xy) ) {
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(end_xy[0], end_xy[1]), ImVec2(self_xy[0], self_xy[1]), ImVec2(nearest_xy[0], nearest_xy[1]), IM_COL32(255, 255, 0, 25));
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(end_xy[0], end_xy[1]), ImVec2(self_xy[0], self_xy[1]), IM_COL32(255, 255, 0, 255), 2.f);
	}

}
void cg::Mod_GetAccelerationAngles(const bool rightmove, vec2_t out)
{
	static float delta;
	const float yaw = clients->cgameViewangles[YAW];
	jump_data* jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);

	float opt;
	if (!analyzer.isPreviewing())
		opt = R_getOptAngle(rightmove, delta);

	else {
		if (jData)
			opt = getOptForAnalyzer(jData, GROUND);
		else
			opt = R_getOptAngle(rightmove, delta);

	}

	if(rightmove)
		out[0] = opt;
	else out[1] = opt;

	//delta = (delta > 0) ? delta : -delta;

	const float maxAngle = 45.f - (delta);



	if (rightmove) {
		out[1] = out[0] - maxAngle;
	}
	else {
		out[0] = out[1] + maxAngle;

	}
	//char buffer[40];
	//sprintf_s(buffer, "delta: %.6f", maxAngle);

	//r::R_DrawText(buffer, 0, 500, 1.5f, 1.5f, 0, vec4_t{ 0,255,0,255 }, 0);
}
void cg::Mod_DrawAngleHelper()
{
	if (NOT_SERVER || !v::mod_anglehelper.isEnabled() || !v::mod_anglehelper.evar->arrayValue[0])
		return;

	const usercmd_s* cmd = cinput->GetUserCmd(cinput->currentCmdNum - 1);

	float yaw = clients->cgameViewangles[YAW];
	const dvar_s* cg_fov = Dvar_FindMalleableVar("cg_fov");
	const dvar_s* cg_fovscale = Dvar_FindMalleableVar("cg_fovscale");
	vec2_t accel_angles;

	static bool rightmove;

	if (cmd->rightmove > 0)
		rightmove = true;
	else if (cmd->rightmove < 0)
		rightmove = false;

	FPS_CalculateSingleBeatDirection(rightmove, cmd);

	if (analyzer.isPreviewing()) {
		const jump_data* jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);

		if (jData) {
			rightmove = jData->rightmove > 0;
			yaw = jData->angles[YAW];
		}

	}


	if (!cg_fov || !cg_fovscale)
		return;

	Mod_GetAccelerationAngles(rightmove, accel_angles);

	const float fov = (cg_fov->current.value * cg_fovscale->current.value) * v::mod_anglehelper.evar->arrayValue[3];

	CG_FillAngleYaw(accel_angles[0], accel_angles[1], yaw, v::mod_anglehelper.evar->arrayValue[1], v::mod_anglehelper.evar->arrayValue[2], fov, vec4_t{255,0,0,0.7});
	r::R_DrawRect("white", 958, v::mod_anglehelper.evar->arrayValue[1] - 10, 4, v::mod_anglehelper.evar->arrayValue[2] + 20, vec4_t{ 255,255,255,255 });
}
void cg::Mod_DrawCurveSpeed()
{

	if (!v::mod_curve_speed.isEnabled())
		return;

	static float yawPrevious = clients->cgameViewangles[YAW] < 0 ? -clients->cgameViewangles[YAW] : clients->cgameViewangles[YAW];
	const float yawNow = clients->cgameViewangles[YAW] < 0 ? -clients->cgameViewangles[YAW] : clients->cgameViewangles[YAW];
	static int32_t oldCommandTime = clients->snap.ps.commandTime;
	static float difference = yawNow - yawPrevious;
	if (clients->snap.ps.commandTime > oldCommandTime + 50) {
		difference = yawNow - yawPrevious;
		oldCommandTime = clients->snap.ps.commandTime;
		yawPrevious = clients->cgameViewangles[YAW] < 0 ? -clients->cgameViewangles[YAW] : clients->cgameViewangles[YAW];
		
		difference = difference < 0 ? -difference : difference;
	}


	char buffer[24];

	sprintf_s(buffer, "%.2f", difference);

	r::R_DrawText(buffer, 700, 200, 2, 2, 0, vec4_t{ 1,1,1,1 }, 0);
}

void cg::Mod_DrawJumpPath()
{

	if (!analyzer.RecordingExists() && !analyzer.Segmenter_RecordingExists() || !v::mod_jumpv_path.isEnabled())
		return;

	//const auto OriginsToScreen = [](std::vector<jump_data> data, std::vector<ImVec2>* color) -> std::vector<ImVec2> {
	//	std::vector<ImVec2> points;
	//	color->clear();
	//	color->resize(1);
	//	color->erase(color->begin(), color->end());

	//	int validPoints{ 0 };
	//	vec2_t xy;

	//	for (unsigned i = 0; i < data.size(); i++) {
	//		if (r::WorldToScreen(data[i].origin, xy)) {
	//			points.push_back(ImVec2(xy[0], xy[1]));

	//			ImVec2 fcolor;

	//			float col = VALUE2COLOR(glm::length(glm::vec2(data[i].velocity[0], data[i].velocity[1])), analyzer.average_velocity);

	//			fcolor.x = 255.f - col;
	//			fcolor.y = col;
	//			if (col > 255) {
	//				fcolor.x = 0;
	//				fcolor.y = 255; //green because we got more speed
	//			}
	//			color->push_back(fcolor);
	//			validPoints += 1;
	//		}
	//	}
	//	points.resize(validPoints);
	//	color->resize(validPoints);
	//	return points;
	//};

	std::vector<ImVec2> color;
	std::vector<ImVec2> points = r::OriginsToScreen(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, &color, true);
	if (points.size() > 1)
		for (int i = 0; i < points.size() - 1; i++)
			ImGui::GetBackgroundDrawList()->AddLine(points[i], points[i + 1], IM_COL32(color[i].x, color[i].y, 0, 255), 3.f);


	vec2_t xy;
	jump_data* jData = analyzer.FetchFrameData(analyzer.isSegmenting() ? analyzer.segData : analyzer.data, analyzer.preview_frame);

	if (jData) {
		if (r::WorldToScreen(jData->origin, xy)) {
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(xy[0], xy[1]), 10.f, IM_COL32(255, 255, 255, 255), 3);
		}
	}
	


}
void cg::Mod_DrawJumpHitbox()
{
	if (!analyzer.RecordingExists() && !analyzer.Segmenter_RecordingExists() || !v::mod_jumpv_hitbox.isEnabled())
		return;

	if (!analyzer.InFreeMode() && v::mod_jumpv_forcepos.isEnabled())
		return;

	jump_data* jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);

	if (jData) {

		r::box_s box(jData->origin, jData->mins, jData->maxs);
		box.R_DrawConstructedBoxEdges(vec4_t{ 255,255,0,255 });
		box.R_DrawConstructedBox(vec4_t{ 255,255,0,50 });

	}
}
void cg::Mod_DrawJumpDirection()
{
	if (!analyzer.isPreviewing() || !analyzer.RecordingExists() && !analyzer.Segmenter_RecordingExists())
		return;

	jump_data* jData = analyzer.FetchFrameData(analyzer.Segmenter_RecordingExists() ? analyzer.segData : analyzer.data, analyzer.preview_frame);

	if (!jData)
		return;

	vec3_t velocity, origin;
	VectorCopy(jData->velocity, velocity);
	VectorCopy(jData->origin, origin);

	//VectorNormalize(velocity);
	//VectorScale(velocity, 180, velocity);

	vectoangles(velocity, velocity);


	origin[2] += jData->maxs[2] / 2;

	AnglesToForward(velocity, origin, 50, velocity);

	vec2_t org_xy, end_xy;

	if (r::WorldToScreen(origin, org_xy) && r::WorldToScreen(velocity, end_xy)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(org_xy[0], org_xy[1]), ImVec2(end_xy[0], end_xy[1]), IM_COL32(255, 255, 0, 255), 2);
		
	}


	

}
void cg::Mod_B_DrawPath()
{
	size_t indx(0);
	for (auto& a : jbuilder.segments) {

		std::vector<ImVec2> points = r::OriginsToScreen(a.jData);
		if (points.size() > 1) {
			for (int i = 0; i < points.size() - 1; i++) {
				glm::vec4 rgb;

				rgb.r = indx == jbuilder.current_segment ? 255 : 0;
				rgb.g = indx == jbuilder.current_segment ? 0 : 255;
				rgb.b = 0;


				rgb.a = 255;

				ImGui::GetBackgroundDrawList()->AddLine(points[i], points[i + 1], IM_COL32(rgb.r, rgb.g, rgb.b, rgb.a), 3.f);
			}

		}



		if (a.jData.size() > 1 && v::mod_jbuild_wasd.isEnabled()) {
			jump_data jData = a.jData[0];

			vec3_t origin, vel, ang;
			vec2_t xy, xy_end;
			VectorCopy(jData.origin, origin);
			VectorCopy(jData.velocity, vel);

			vectoangles(vel, vel);


			if (jData.rightmove > 0) {
				vel[YAW] -= 90;
			}
			else {
				vel[YAW] += 90;

			}
			vel[PITCH] = 0;
			vel[ROLL] = 0;

			AnglesToForward(vel, origin, 50, ang);

			if (r::WorldToScreen(origin, xy) && r::WorldToScreen(ang, xy_end)) {
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(xy[0], xy[1]), ImVec2(xy_end[0], xy_end[1]), IM_COL32(255, 255, 0, 255), 3);
			}
		}

		//jump_data* jData = jbuilder.FetchFrameData(jbuilder.preview_frame);

		if (jbuilder.preview_frame > a.begin && jbuilder.preview_frame < a.end && v::mod_jbuild_hitbox.isEnabled() && !v::mod_jbuild_forcepos.isEnabled()) {

			if (a.jData.size() > 1) {


				jump_data jData = a.jData[jbuilder.preview_frame - a.begin];


				r::box_s box(jData.origin, jData.mins, jData.maxs);
				box.R_DrawConstructedBoxEdges(vec4_t{ 255,102,255,255 });
				box.R_DrawConstructedBox(vec4_t{ 255,102,255,50 });
			

			}
		}
		indx++;
	}

}