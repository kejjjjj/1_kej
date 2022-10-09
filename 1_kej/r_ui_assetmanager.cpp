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

	
}