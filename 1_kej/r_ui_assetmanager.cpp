#include "pch.h"


void r::R_AssMan_Main(bool& isOpen)
{
	if (!isOpen)
		return;

	ImGui::Begin("Asset Manager##01", &isOpen, ImGuiWindowFlags_AlwaysAutoResize);

	//static IDirect3DBaseTexture9* basemap(nullptr);
	static Material* selectedMat;
//	static ImVec2 selected_pos;

	static char searchBuf[128];
	static ass_material_s ass;

	ImGui::PushItemWidth(300);
	ImGui::InputText("search", searchBuf, 128);

	ImGui::BeginGroup();
	ImGui::BeginChild("assman##01",ImVec2(500, 670));

	for (size_t i = 0; i < rgp->materialCount; i++) {
		Material* mtl = rgp->sortedMaterials[i];

		if (mtl) {
			if (std::string(mtl->info.name).find(searchBuf) != std::string::npos || searchBuf[0] == '\0') {
				ImGui::Text("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t",mtl->info.name); //lol
				if (ImGui::IsItemHovered()) {
					if (mtl->textureTable) {
						if (mtl->textureTable->u.image) {
							//ImGui::SameLine();
							//ImGui::BeginTooltip();
							//basemap = mtl->textureTable->u.image->texture.basemap;
							selectedMat = mtl;
							ass.selectedIndex = i;
							const ImVec2 mins = ImGui::GetItemRectMin();
							const ImVec2 maxs = ImGui::GetItemRectMax();

							ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(mins.x - 3, mins.y - 3), ImVec2(mins.x + 500 - 3, maxs.y + 3), IM_COL32(255, 255, 255, 170));

							//ImGui::Image(mtl->textureTable->u.image->texture.basemap, ImVec2(128,128));
							//ImGui::EndTooltip();
						}
					}

				}

				ImGui::Separator();
			}

		}

	}
	ImGui::EndChild();
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();
	if (ButtonCentered("Edit Shader"))
		ass.shaderEdit = !ass.shaderEdit;

	ImGui::BeginChild("images##01", ImVec2(545,670), true, ImGuiWindowFlags_NoScrollbar);
	if (selectedMat) {
		for (int i = 0; i < selectedMat->textureCount; i++) {
			IDirect3DBaseTexture9* basemap = selectedMat->textureTable[i].u.image->texture.basemap;

			if (basemap) {
				ImGui::BeginGroup();
				ImGui::Image(basemap, ImVec2(256, 256));
				//ImGui::SameLine();
				const float x = ImGui::GetItemRectMax().x;
				ImGui::PushTextWrapPos(x - (ImGui::GetWindowPos().x));
				ImGui::TextUnformatted(selectedMat->textureTable[i].u.image->name);
				ImGui::PopTextWrapPos();
				
				

				ImGui::EndGroup();
				if (ImGui::IsItemHovered()) {
					const ImVec2 mins = ImGui::GetItemRectMin();
					const ImVec2 maxs = ImGui::GetItemRectMax();

					ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(mins.x - 3, mins.y - 3), ImVec2(maxs.x + 3, maxs.y + 3), IM_COL32(255, 255, 255, 170));
					ass.name = selectedMat->info.name;
					if (ImGui::IsItemClicked()) {
						ass.isEditing = !ass.isEditing;
						ass.mtl = selectedMat;
						ass.basemap = reinterpret_cast<IDirect3DBaseTexture9*>(basemap);
						ass.loadDef = reinterpret_cast<GfxImageLoadDef*>(selectedMat->textureTable[i].u.image->texture.loadDef);
						ass.selectedTextureTable = i;
						
					}
				}
				ImGui::SameLine();
				ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
			}
			
			if (i % 2 == 0)
				ImGui::SameLine();
			else
				if(i > 0)
					ImGui::Separator();

		}




	}
	else
		ImGui::Image(UI_FindImageByName("Error_no_load"), ImVec2(256, 256));

	ImGui::EndChild();
	ImGui::EndGroup();
	ImGui::Text("\t");
	ImGui::End();

	R_AssMan_EditMaterial(ass);
	R_AssMan_EditShader(ass);
	
}
void r::R_AssMan_EditMaterial(ass_material_s& _mtl)
{
	if (!_mtl.isEditing)
		return;

	static bool replaceTexture(0), replacePixelShader(0), replaceVertexShader(0);

	ImGui::Begin("Material Properties##01", &_mtl.isEditing);
	ImGui::SetWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);

	static char searchBuf[128];
	ImGui::PushItemWidth(300);
	ImGui::InputText("search", searchBuf, 128);
	ImGui::NewLine();


	size_t ImagesPerLine(0);
	for (size_t i = 0; i < rgp->materialCount; i++) {
		const Material* mtl = rgp->sortedMaterials[i];
		if (mtl) {
			if (std::string(mtl->info.name).find(searchBuf) != std::string::npos || searchBuf[0] == '\0') {
				if (!mtl->textureTable) {
					continue;
				}
				for (size_t j = 0; j < mtl->textureCount; j++) {

					if (mtl->textureTable[j].u.image) {
						IDirect3DBaseTexture9* basemap = mtl->textureTable[j].u.image->texture.basemap;

						if (basemap) {

							if (ImagesPerLine == 5)
								ImagesPerLine = 0;
							else
								ImGui::SameLine();

							ImGui::BeginGroup();

							ImGui::Image(basemap, ImVec2(128, 128));
							//ImGui::SameLine();
							const float x = ImGui::GetItemRectMax().x;
							if ((int)mtl->textureTable[j].u.image->name < 0x0D934FFF) {
								ImGui::PushTextWrapPos(x - (ImGui::GetWindowPos().x));
								ImGui::TextUnformatted(mtl->textureTable[j].u.image->name);
								ImGui::PopTextWrapPos();
							}
							//else
							//	Com_PrintError(CON_CHANNEL_CONSOLEONLY, "epic mtl->textureTable[j].u.image->name failure\n");

							ImGui::EndGroup();

							if (ImGui::IsItemHovered()) {
								const ImVec2 mins = ImGui::GetItemRectMin();
								const ImVec2 maxs = ImGui::GetItemRectMax();

								ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(mins.x - 3, mins.y - 3), ImVec2(maxs.x + 3, maxs.y + 3), IM_COL32(255, 255, 255, 170));

								if (ImGui::IsItemClicked()) {

									Material* material = rgp->sortedMaterials[_mtl.selectedIndex];

									memcpy(&material->textureTable[_mtl.selectedTextureTable].u.image->texture, &mtl->textureTable[j].u.image->texture, sizeof(GfxTexture));

									material->techniqueSet = mtl->techniqueSet;

									//mtl->textureTable[_mtl.selectedTextureTable].u.image->texture.basemap = mtl->textureTable[j].u.image->texture.basemap;
									//_mtl.loadDef = mtl->textureTable[j].u.image->texture.loadDef;


								}
							}

							ImGui::SameLine();
							ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
							++ImagesPerLine;

						}
					}




				}
			}

			
		}
	}

	ImGui::End();
}
void r::R_AssMan_EditShader(ass_material_s& mtl)
{
	if (!mtl.shaderEdit)
		return;


	char buffer[128];
	sprintf_s(buffer, "Edit shader (%s)", mtl.name);
	ImGui::Begin(buffer, &mtl.shaderEdit);
	ImGui::SetWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);

	static char searchBuf[128];
	ImGui::PushItemWidth(300);
	ImGui::InputText("search", searchBuf, 128);
	//ImGui::NewLine();

	for (size_t i = 0; i < rgp->materialCount; i++) {

		const Material* mat = rgp->sortedMaterials[i];
		if (mat) {
			if (std::string(mat->info.name).find(searchBuf) != std::string::npos || searchBuf[0] == '\0') {
				if (!mat->textureTable) {
					continue;
				}

				ImGui::Text("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t", mat->info.name); //lol

				if (ImGui::IsItemHovered()) {
					const ImVec2 mins = ImGui::GetItemRectMin();
					const ImVec2 maxs = ImGui::GetItemRectMax();

					ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(mins.x - 3, mins.y - 3), ImVec2(maxs.x + 3, maxs.y + 3), IM_COL32(255, 255, 255, 170));

					if (ImGui::IsItemClicked()) {

						Material* material = rgp->sortedMaterials[mtl.selectedIndex];
						material->techniqueSet = mat->techniqueSet;


					}
				}

			}
		}
	}


	ImGui::End();
}