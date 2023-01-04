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



	EXP_WriteHeader(f);

	if (!EXP_ExportLeaves(f)) {
		Com_PrintError(CON_CHANNEL_OBITUARY, "EXP_MapExport(): cannot export leaves\n");
		return false;
	}

	f << "}";

	fs::F_CloseFile(f);

	Com_Printf(CON_CHANNEL_OBITUARY, "^2Success!\n");

	return true;

}
void cg::MapExport::EXP_WriteHeader(std::fstream& f)
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
bool cg::MapExport::EXP_ExportLeaves(std::fstream& f)
{
	uint32_t idx = 0;
	cLeaf_t* leaf;
	CollisionAabbTree* aabb;
	CollisionAabbTreeIndex fChild;
	CollisionPartition* partition;
	int firstTri = 0;
	int triIndice = 0;
	auto exp = this;


	const auto L_WriteMesh = [&f, this](const vec3_t A, const vec3_t B, const vec3_t C)->void{
		
		if (!A || !B || !C)
			return;

		VectorCopy(A, e.A1);
		VectorCopy(B, e.B1);
		VectorCopy(C, e.C1);

		f << "// brush " << e.brush++ << "\n {";
		f << "  mesh\n   {\n";
		f << "  toolFlags splitGeo;\n";
		f << "  caulk\n";
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


	};
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

			f << "// brush " << e.brush++ << "\n {";
			f << "  mesh\n   {\n";
			f << "  toolFlags splitGeo;\n";
			f << "  caulk\n";
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

			//L_WriteMesh(X, Y, Z);

			++firstTri;
			triIndice += 3;

			/*Sleep(1);*/


		} while (firstTri < partition->firstTri + partition->triCount);

		//break;

	}

	return true;
}