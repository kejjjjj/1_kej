#include "pch.h"


void r::R_JumpBuilder_ConstructKey(char& direction, char value, const char* buttonName)
{

	if (ImGui::Button(buttonName)) {

		if (direction == value)
			direction = NULL;
		else
			direction = value;

		jbuilder.OnUpdateAllPositions();

	}

	if (direction == value) {
		ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImColor(0.f, 0.f, 0.f, 0.7f));
	}
}

void r::R_JumpBuilder_Main()
{
	std::vector<segment_data_s> &segments = jbuilder.segments; 
	
	if (!jbuilder.builder_data.run_created) {
		ImGui::Text("Create Project\t\t\t\t");
		UI_DrawGradientZone(ImVec2(150, 100));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (ImGui::Button("Create New"))
			jbuilder.get_playerState = true;

		ImGui::EndGroup();
	}else{

		ImGui::Text("Segments\t\t\t\t");
		UI_DrawGradientZone(ImVec2(550, 100));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		static int old_segment = jbuilder.current_segment;

		if (ImGui::SliderInt("Segment", &jbuilder.current_segment, 0, jbuilder.segments.size() - 1, "%d")) {

			if(jbuilder.current_segment != old_segment)
				jbuilder.OnUpdatePosition(true);

			old_segment = jbuilder.current_segment;
		}
		const size_t total_frames = jbuilder.GetTotalFrames();


		if (ImGui::Button("Add Segment"))
			jbuilder.OnAddSegment();

		ImGui::EndGroup();


		ImGui::Text("Editing\t\t\t\t");
		UI_DrawGradientZone(ImVec2(550, 100));

		ImGui::Text("\t");
		ImGui::SameLine();

		ImGui::BeginGroup();

		if (ImGui::SliderInt("Frame", &jbuilder.preview_frame, 0, total_frames, "%d")) {
			size_t indx(0);
			for (const auto& i : jbuilder.segments) {
				if (i.end > jbuilder.preview_frame && i.begin < jbuilder.preview_frame)
					jbuilder.current_segment = indx;
				indx++;
			}
		}

		static int old_count = segments[jbuilder.current_segment].framecount;

		if (ImGui::DragInt("Frame Count", &segments[jbuilder.current_segment].framecount, 5, 1, 2000, "%d", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_ClampOnInput)) {

			//if (segments[jbuilder.current_segment].framecount < old_count) {
			//	segments[jbuilder.current_segment];
			//}

			segments[jbuilder.current_segment].end += (segments[jbuilder.current_segment].framecount - old_count);
			old_count = segments[jbuilder.current_segment].framecount;

			jbuilder.OnUpdateOffsets();
			jbuilder.OnUpdateAllPositions();

		}

		ImVec2 rectMin, rectMax;

		ImGui::NewLine();

		ImGui::Text("\t");
		ImGui::SameLine();

		R_JumpBuilder_ConstructKey(segments[jbuilder.current_segment].forwardmove,	127,	"W##01");
		R_JumpBuilder_ConstructKey(segments[jbuilder.current_segment].rightmove,	-127,	"A##01");

		ImGui::SameLine();
		ImGui::Text("\t");
		ImGui::SameLine();

		R_JumpBuilder_ConstructKey(segments[jbuilder.current_segment].rightmove,	127,	"D##01");

		ImGui::Text("\t ");
		ImGui::SameLine();
		
		R_JumpBuilder_ConstructKey(segments[jbuilder.current_segment].forwardmove,	-127,	"S##01");

		ImGui::EndGroup();

	
	}
	ImGui::Text("Project\t\t\t\t");
	UI_DrawGradientZone(ImVec2(550, 100));

	ImGui::Text("\t");
	ImGui::SameLine();

	ImGui::BeginGroup();

	if (ImGui::Button("Delete Project"))
		jbuilder.OnDeleteProject();
	
	ImGui::EndGroup();

	

}