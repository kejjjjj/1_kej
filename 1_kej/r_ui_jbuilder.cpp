#include "pch.h"


void r::R_JumpBuilder_Main()
{

	
	if (!jbuilder.builder_data.run_created) {
		ImGui::Text("Create Project");
		UI_DrawGradientZone(ImVec2(150, 100));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (ImGui::Button("Create New"))
			jbuilder.get_playerState = true;

		ImGui::EndGroup();
	}else{

		ImGui::Text("Editing");
		UI_DrawGradientZone(ImVec2(150, 200));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		ImGui::SliderInt("Frame", &jbuilder.preview_frame, 0, 100, "%d");
		ImGui::NewLine();

		ImGui::Text("\t");
		ImGui::SameLine();
		if (ImGui::Button("W##01"));
		if (ImGui::Button("A##01"));
		ImGui::SameLine(); 		
		ImGui::Text("\t");
		ImGui::SameLine();		
		if (ImGui::Button("D##01"));

		ImGui::Text("\t");
		ImGui::SameLine();
		if (ImGui::Button("S##01"));

		ImGui::EndGroup();

	
	}
	

	

}