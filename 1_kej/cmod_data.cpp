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

		r::box_s box(brush_org, mins, maxs);
		box.R_DrawConstructedBoxEdges(vec4_t{ 0,255,0,255 });
		box.R_DrawConstructedBox(vec4_t{ 0,255,0,50});

	}


}


struct v3
{
	float x, y, z;
};
void cg::CMod_OnHighlightTriangle()
{
	static bool edit_mode = false;

	if ((GetAsyncKeyState(VK_NUMPAD6) & 1)) {

		edit_mode = !edit_mode;

		if(edit_mode)
			VectorCopy(clients->cgameOrigin, exp_mins);
		else {
			for (int i = 0; i < 3; i++) {
				exp_origin[i] = exp_mins[i] + (exp_maxs[i] - exp_mins[i]) / 2;
				exp_maxs[i] = fabs(exp_maxs[i] - exp_origin[i]);
				exp_mins[i] = fabs(exp_origin[i] - exp_mins[i]);
			}
		}
	}

	if (edit_mode) {
		VectorCopy(clients->cgameOrigin, exp_maxs);
	}

	r::box_s box(exp_origin, exp_mins, exp_maxs);

	box.R_DrawConstructedBoxEdges(vec4_t{ 0,255,0,255 });
	box.R_DrawConstructedBox(vec4_t{ 0,255,0,55});

	if ((GetAsyncKeyState(VK_NUMPAD5) & 1) == false) {
		return;
	}
	

	cg::MapExport map;

	map.EXP_BeginExport();

	return;
	
	static vec3_t trisA{}, trisB{}, trisC{};
	static unsigned int leafnum = 0;
	static std::vector<v3> v;
	vec2_t s;

	if (v.size() >= 3) {
		for (int i = 0; i < v.size() - 3; i += 3) {

			vec3_t tris[3];

			tris[0][0] = v[i].x;
			tris[0][1] = v[i].y;
			tris[0][2] = v[i].z;


			tris[1][0] = v[i + 1].x;
			tris[1][1] = v[i + 1].y;
			tris[1][2] = v[i + 1].z;

			tris[2][0] = v[i + 2].x;
			tris[2][1] = v[i + 2].y;
			tris[2][2] = v[i + 2].z;

			r::R_DrawTriangleOutline(tris, vec4_t{ 255,0,0,255 });
			r::R_DrawTriangle(tris, vec4_t{ 255,0,0,50 });

		}
	}

	v.clear();
	
	uint16_t model = 0;

	cLeaf_t* leaf = &cm->leafs[ImClamp<unsigned int>(++leafnum, 0, cm->numLeafs)];

	if (!leaf)
		return;

	int idx = 0;
	std::cout << "leaf["<<leafnum<<"]collAabbCount: " << leaf->collAabbCount << '\n';

	if (leaf->collAabbCount) {
			
		//do {

			CollisionAabbTree* aabb = &cm->aabbTrees[idx + leaf->firstCollAabbIndex];
			CollisionAabbTreeIndex fChild = aabb->u;

			//while(aabb->childCount){
			//	int v4 = 0;
			//	auto child = &cm->aabbTrees[fChild.firstChildIndex];

			//	do {

			//		++aabb;
			//		++v4;

			//	} while (v4 < aabb->childCount);

			//}
			fChild = aabb->u;
			CollisionPartition* partition = &cm->partitions[fChild.firstChildIndex];
			std::cout << "partition[" << fChild.firstChildIndex << "]triCount: " << (int)partition->triCount << '\n';

			int firstTri = partition->firstTri;

			if (firstTri < firstTri + partition->triCount)
			{
				int triIndice = 3 * firstTri;

				do
				{

					vec3_t X = { cm->verts[cm->triIndices[triIndice]][0],	 cm->verts[cm->triIndices[triIndice]][1],    cm->verts[cm->triIndices[triIndice]][2]   };
					vec3_t Y = { cm->verts[cm->triIndices[triIndice+1]][0],  cm->verts[cm->triIndices[triIndice+1]][1],  cm->verts[cm->triIndices[triIndice+1]][2] };
					vec3_t Z = { cm->verts[cm->triIndices[triIndice+2]][0],  cm->verts[cm->triIndices[triIndice+2]][1],  cm->verts[cm->triIndices[triIndice+2]][2] };

					v.push_back(v3{ X[0], X[1], X[2] });
					v.push_back(v3{ Y[0], Y[1], Y[2] });
					v.push_back(v3{ Z[0], Z[1], Z[2] });

					//VectorCopy(X, tris[i]);

					//std::cout << "X: " << X[0] << '\n';
					//std::cout << "Y: " << X[1] << '\n';
					//std::cout << "Z: " << X[2] << "\n\n";

					std::cout << std::format("A: {:.3f}, {:.3f}, {:.3f}\n", X[0], X[1], X[2]);
					std::cout << std::format("B: {:.3f}, {:.3f}, {:.3f}\n", Y[0], Y[1], Y[2]);
					std::cout << std::format("C: {:.3f}, {:.3f}, {:.3f}\n\n", Z[0], Z[1], Z[2]);


					++firstTri;
					triIndice += 3;

				} while (firstTri < partition->firstTri + partition->triCount);

			}


		//} while (++idx < leaf->collAabbCount);

	}

	//if (leaf) {

	//	std::cout << "cmodel->leaf.mins[0] = " << leaf->mins[0] << '\n';
	//	std::cout << "cmodel->leaf.mins[1] = " << leaf->mins[1] << '\n';
	//	std::cout << "cmodel->leaf.mins[2] = " << leaf->mins[2] << '\n';


	//}




}