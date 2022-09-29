#include "pch.h"


cbrush_t* cg::CMod_FindBrushByOrigin(vec3_t origin)
{
	cbrush_t* brush = cm->brushes;

	for (uint16_t i = 0; i < cm->numBrushes; i++) {
			
		if (brush) {

			if (	origin[0] > brush->mins[0] && origin[0] < brush->maxs[0]
				&&	origin[1] > brush->mins[1] && origin[1] < brush->maxs[1]
				&&	origin[2] > brush->mins[2] && origin[2] < brush->maxs[2]) {

				return brush;

			}

			

		}
			
		++brush;
	}
	return nullptr;
}
void cg::CMod_GetBrushOriginFromBounds(cbrush_t* brush, vec3_t out)
{
	for (int i = 0; i < 3; i++)
		out[i] = brush->mins[i] + (brush->maxs[i] - brush->mins[i]) / 2;
}

//
//will fix later when motivation kicks back in :x
//
void cg::CMod_HighlightSelected()
{
	if (NOT_SERVER)
		return;

	static cbrush_t* brush(nullptr);
	static vec3_t brush_org, mins, maxs, end2, dst;

	if (GetAsyncKeyState(VK_NEXT) & 1) {

		trace_t trace;
		vec3_t end, angles;
		
		AnglesToForward(clients->cgameViewangles, rg->viewOrg, 99999, end);
		CG_TracePoint(vec3_t{ 0,0,0 }, &trace, rg->viewOrg, vec3_t{ -1,-1,-1 }, end, cgs->clientNum, MASK_PLAYERSOLID, 0, 0);

		if (trace.fraction != 1.f) {
			system("cls");
			end[0] = rg->viewOrg[0] + trace.fraction * (end[0] - rg->viewOrg[0]);
			end[1] = rg->viewOrg[1] + trace.fraction * (end[1] - rg->viewOrg[1]);
			end[2] = rg->viewOrg[2] + trace.fraction * (end[2] - rg->viewOrg[2]);

			VectorCopy(clients->cgameViewangles, angles);

			angles[PITCH] = trace.normal[2] * 85;

			AnglesToForward(angles, end, 2, end2); //slightly clip inside of the wall

			brush = CMod_FindBrushByOrigin(end2);

			if(brush){
				CMod_GetBrushOriginFromBounds(brush, brush_org);
				VectorSubtract(brush->maxs, brush_org, maxs);
				VectorSubtract(brush->mins, brush_org, mins);

				mins[0] = mins[0] < 0 ? -mins[0] : mins[0];
				mins[1] = mins[1] < 0 ? -mins[1] : mins[1];
				mins[2] = mins[2] < 0 ? -mins[2] : mins[2];

				cbrushside_t* brushside = brush->sides;

				if (brush->numsides > 0) {
					brush = nullptr;
					return;
				}

				for (int i = 0; i < brush->numsides; i++) {
					if (brushside) {
						cplane_s* plane = brushside->plane;

						dmaterial_t mat = cm->materials[brushside->materialNum];
						std::cout << "brushside->materialNum: " << mat.material << '\n';

					}
					++brushside;
				}
				

			}



		}

	}if (brush) {

		//vec3_t angles, finalpos;

		//VectorsToAngles(brush_org, brush->maxs, angles);

		//float dist = glm::distance(glm::vec3(brush_org[0], brush_org[1], brush_org[2]), glm::vec3(brush->maxs[0], brush->maxs[1], brush->maxs[2]));


		//angles[YAW] *= 1.5;


		//AnglesToForward(angles, brush_org, dist, finalpos);

		//vec2_t start_xy, end_xy;
		//if (r::WorldToScreen(brush_org, start_xy) && r::WorldToScreen(finalpos, end_xy)) {
		//	ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(start_xy[0], start_xy[1]), 30, IM_COL32(0, 255, 0, 255), 4);
		//	ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(end_xy[0], end_xy[1]), 30, IM_COL32(255, 0, 0, 255), 4);

		//	vec2_t text_xy;


		//	//if (r::WorldToScreen(finalpos, text_xy)) {
		//	//	ImGui::GetBackgroundDrawList()->AddText(ImVec2(text_xy[0], text_xy[1]), IM_COL32(255, 255, 0, 255), std::to_string(dist).c_str());
		//	//}

		//}

		//vec3_t yMaxs, yMins;
		//VectorCopy(brush->mins, yMins);
		//VectorCopy(brush->maxs, yMaxs);

		//////yMins[0] += maxs[0] * 2;
		////yMins[1] += maxs[1] * 2;
		////yMins[2] = dst[2];
		////yMaxs[1] -= maxs[1] * 2;
		//
		//
		//r::R_DrawTriangle(dst, brush->mins, brush->maxs, vec4_t{ 0,255,0,200 });
		//r::R_DrawTriangle(dst, yMins, brush->maxs, vec4_t{ 0,255,0,200 });

		r::box_s box = r::R_ConstructBoxFromBounds(brush_org, mins, maxs);
		r::R_DrawConstructedBoxEdges(box, vec4_t{ 0,255,0,255 });
		r::R_DrawConstructedBox(box, vec4_t{ 0,255,0,50});

	}


}