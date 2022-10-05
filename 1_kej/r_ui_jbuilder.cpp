#include "pch.h"


void r::R_JumpBuilder_Main()
{

	
	ImGui::Text("Hello world! This is an example text\t\t");

	ImGui::NewLine();
	ImGui::Text("testing");
	UI_DrawGradientZone(ImVec2(150, 100));

	ImGui::Text("\t");
	ImGui::SameLine();

	ImGui::BeginGroup();

	if (ImGui::Button("Create New"))
		jbuilder.get_playerState = true;
	else if (ImGui::Button(jbuilder.isGeneratingMovement() == false ? "Generate Movement" : "Stop Generating")) {
		if (!jbuilder.isGeneratingMovement())
			jbuilder.OnStartGenerating();
		else {
			jbuilder.OnStopGenerating();
			Com_Printf(CON_CHANNEL_OBITUARY, "recorded [%i]\n", jbuilder.jData.size());
		}
	}

	ImGui::EndGroup();

}