#include "pch.h"


cg::MapExport::MapExport()
{
	const std::string path = fs::GetExePath() + "\\map_source";
	const std::string fullpath = path + "\\" + Dvar_FindMalleableVar("mapname")->current.string + ".map";

	if (!fs::F_DirectoryExists(path)) {
		if (!fs::F_CreateDirectory(path)) {
			Com_PrintError(CON_CHANNEL_OBITUARY, "EXP_MapExport(): unable to create file for out operation\n");
			return;
		}

	}

	if (!fs::F_OpenFile(f, fullpath, fs::fileopen::FILE_OUT)) {
		Com_PrintError(CON_CHANNEL_OBITUARY, "EXP_MapExport(): unable to open file for out operation\n");
		return;
	}

	ready = true;



	return;
}
bool cg::MapExport::EXP_BeginExport()
{
	const bool success = EXP_BeginExportB();

	fs::F_CloseFile(f);



	return success;

}
bool cg::MapExport::EXP_BeginExportB()
{
	auto exp = this;

	if (!exp->ready) {
		Com_PrintError(CON_CHANNEL_OBITUARY, "EXP_BeginExport(): Initialization unsuccessful, not exporting...\n");
		return false;
	}



	EXP_WriteHeader();

	//if (!EXP_ExportLeaves()) {
	//	Com_PrintError(CON_CHANNEL_OBITUARY, "EXP_MapExport(): cannot export leaves\n");
	//	return false;
	//}

	EXP_ExportSurfaces();

	f << "}";

	fs::F_CloseFile(f);

	Com_Printf(CON_CHANNEL_OBITUARY, "^2Success!\n");

	return true;

}
void cg::MapExport::EXP_WriteHeader()
{
	f << "iwmap 4\n";
	f << "\"000_Global\" flags  active\n";
	f << "\"The Map\" flags\n";
	f << "// entity 0\n{\n";
	f << "\"contrastGain\" " "\"0.125\"" << '\n';
	f << "\"diffusefraction\" " "\"0.5\"" << '\n';
	f << "\"_color\" " "\"0.2 0.27 0.3 1\"" << '\n';
	f << "\"sunlight\" " "\"1\"" << '\n';
	f << "\"sundirection\" " "\"-30 -95 0\"" << '\n';
	f << "\"sundiffusecolor\" " "\"0.2 0.27 0.3 1\"" << '\n';
	f << "\"suncolor\" " "\"0.2 0.27 0.3 1\"" << '\n';
	f << "\"ambient\" " "\".1\"" << '\n';
	f << "\"bouncefraction\" " "\".7\"" << '\n';
	f << "\"classname\" \"worldspawn\"\n";
}
bool cg::MapExport::EXP_ExportLeaves()
{
	uint32_t idx = 0;
	cLeaf_t* leaf;
	CollisionAabbTree* aabb;
	CollisionAabbTreeIndex fChild;
	CollisionPartition* partition;
	int firstTri = 0;
	int triIndice = 0;
	auto exp = this;


	vec3_t mins, maxs;

	for (int j= 0; j < 3; j++) {
		mins[j] = exp_origin[j] - exp_mins[j];
		maxs[j] = exp_origin[j] + exp_maxs[j];

	}

	int index = 0;
	e.vertCount = cm->vertCount;
	while (idx <= cm->partitionCount) {

		//leaf = &cm->leafs[idx];
		
		//if (!leaf)
		//	continue;

		//if (!leaf->collAabbCount)
		//	continue;

		//aabb = &cm->aabbTrees[index + leaf->firstCollAabbIndex];

		//if (!aabb)
		//	continue;

		//fChild = aabb->u;

		//while(aabb->childCount){
		//	int v4 = 0;
		//	auto child = &cm->aabbTrees[fChild.firstChildIndex];
		//	do {
		//		++aabb;
		//		++v4;
		//	} while (v4 < aabb->childCount);
		//}
		
		if (idx++ >= cm->partitionCount-1)
			continue;

		partition = &cm->partitions[idx];

		if (!partition)
			continue;

		firstTri = partition->firstTri;

		if (!(firstTri < firstTri + partition->triCount))
			continue;
		
		int triIndice = 3 * firstTri;
		
		//if ((triIndice + (partition->triCount * 3)) >= cm->triCount) {
		//	continue;
		//}

		do
		{
			e.vert = cm->triIndices[triIndice + 2];

			bool stop = false;
			

			const vec3_t A = { cm->verts[cm->triIndices[triIndice]][0],	 cm->verts[cm->triIndices[triIndice]][1],    cm->verts[cm->triIndices[triIndice]][2] };
			const vec3_t B = { cm->verts[cm->triIndices[triIndice + 1]][0],  cm->verts[cm->triIndices[triIndice + 1]][1],  cm->verts[cm->triIndices[triIndice + 1]][2] };
			const vec3_t C = { cm->verts[cm->triIndices[triIndice + 2]][0],  cm->verts[cm->triIndices[triIndice + 2]][1],  cm->verts[cm->triIndices[triIndice + 2]][2] };

			for (int i = 0; i < 3; i++) {

				if (A[i] < mins[i] || A[i] > maxs[i] ||
					B[i] < mins[i] || B[i] > maxs[i] ||
					C[i] < mins[i] || C[i] > maxs[i]) {
					stop = true;
					break;
				}
					

			}
			if (stop)
				break;

			VectorCopy(A, e.A1);
			VectorCopy(B, e.B1);
			VectorCopy(C, e.C1);

			EXP_WriteTriangle(A, B, C, "caulk");

			//L_WriteMesh(X, Y, Z);

			++firstTri;
			triIndice += 3;

			/*Sleep(1);*/


		} while (firstTri < partition->firstTri + partition->triCount);

		//break;

	}

	return true;
}
void cg::MapExport::EXP_ExportSurfaces()
{
	static int32_t idx = 1;
	GfxSurface* surface = 0;
	int32_t iter = 0;
	uint16_t* indice;
	GfxWorldVertex* vertex;
	surface = &gfxWorld->dpvs.surfaces[0];

	vec3_t mins, maxs;

	for (int j = 0; j < 3; j++) {
		mins[j] = exp_origin[j] - exp_mins[j];
		maxs[j] = exp_origin[j] + exp_maxs[j];

	}

	while (idx < 50000) {

		indice = &gfxWorld->indices[surface->tris.baseIndex];
		vertex = &gfxWorld->vd.vertices[surface->tris.firstVertex];
		iter = 0;
		
		while (true) {
			bool stop = false;
			vec3_t A = { vertex[indice[0]].xyz[0], vertex[indice[0]].xyz[1], vertex[indice[0]].xyz[2] };
			vec3_t B = { vertex[indice[1]].xyz[0], vertex[indice[1]].xyz[1], vertex[indice[1]].xyz[2] };
			vec3_t C = { vertex[indice[2]].xyz[0], vertex[indice[2]].xyz[1], vertex[indice[2]].xyz[2] };

			for (int i = 0; i < 3; i++) {

				if (A[i] < mins[i] || A[i] > maxs[i] ||
					B[i] < mins[i] || B[i] > maxs[i] ||
					C[i] < mins[i] || C[i] > maxs[i]) {
					stop = true;
					break;
				}


			}
			if (stop)
				break;

			std::string mat = surface->material->info.name;

			mat.erase(mat.begin(), mat.begin() + 3);


			EXP_WriteTriangle(A, B, C, mat);

			indice += 3;

			if (++iter >= surface->tris.triCount)
				break;

		}
		surface = &gfxWorld->dpvs.surfaces[idx++];

	}
}

void  cg::MapExport::EXP_WriteTriangle(const vec3_t A, const vec3_t B, const vec3_t C, const std::string& texture)
{
	f << "// brush " << e.brush++ << "\n {";
	f << "  mesh\n   {\n";
	f << "  toolFlags splitGeo;\n";
	f << "  " << texture << "\n";
	f << "  lightmap_grey\n";
	f << "   smoothing smoothing_hard";
	f << "   2 2 0 8\n   (\n";
	f << "\tv " << A[0] << ' ' << A[1] << ' ' << A[2] << " t -8192 4096 -4 4\n";
	f << "\tv " << B[0] << ' ' << B[1] << ' ' << B[2] << " t -8192 4096 -4 4\n";
	f << "   )\n   (\n";
	f << "\tv " << C[0] << ' ' << C[1] << ' ' << C[2] << " t -8192 4096 -4 4\n";
	f << "\tv " << C[0] << ' ' << C[1] << ' ' << C[2] << " t -8192 4096 -4 4\n";
	f << "   )\n";
	f << "  }\n }\n";
}