#include "pch.h"

jAnalyzer::jAnalyzer() 
{
	//data = std::unique_ptr<analyzer_data>(new analyzer_data);
}
jAnalyzer::~jAnalyzer() 
{
}

auto jAnalyzer::GetData() 
{
	return data.data();
}


void jAnalyzer::StartRecording()
{
	current_frame = 0;
	is_recording = true;
	data.clear();
}
bool jAnalyzer::isRecording()
{
	return is_recording;
}

void jAnalyzer::StopRecording()
{

	std::vector<float> avg;
	for (auto& i : data)
		avg.push_back((float)glm::length(glm::vec2(i.velocity[0], i.velocity[1])));

	if (data.size() > 0 && avg.size() > 0) {
		average_velocity = GetAverage(avg.data(), avg.size());
	}

	is_recording = false;
}
void cg::jAnalyzer::OnFrameUpdate()
{
	if (current_frame >= std::numeric_limits<int32_t>().max()) {
		Com_PrintError(CON_CHANNEL_ERROR, "exceeded maximum amount of frames!\n");
		StopRecording();
	}

	current_frame++;
}
void jAnalyzer::SaveFrameData(jump_data& jdata)
{
	data.push_back(jdata);
}
jump_data* jAnalyzer::FetchFrameData(uint32_t frame)
{
	if (data.size() > frame)
		return &data[frame];

	std::cout << data.size() << " > " << frame << '\n';
	return nullptr;
}
bool jAnalyzer::RecordingExists()
{
	return data.size() > 0;
}
int32_t jAnalyzer::GetTotalFrames()
{
	return data.size() - 1;
}
int32_t jAnalyzer::FindBounceFrame()
{
	for (int i = 0; i < data.size(); i++) {
		if (data[i].bounced)
			return i;
	}
	return 0;
}
int32_t jAnalyzer::FindRpgShot()
{
	for (int i = 0; i < data.size(); i++) {
		if (data[i].rpg_fired)
			return i;
	}
	return 0;
}
int32_t jAnalyzer::FindHighestPoint()
{
	int32_t highestFrame(0);
	float highestHeight(0);
	for (int i = 0; i < data.size(); i++) {

		if (data[i].origin[2] > highestHeight) {
			highestHeight = data[i].origin[2];
			highestFrame = i;
		}
	}
	return highestFrame;
}
bool jAnalyzer::isPreviewing()
{
	return is_previewing;
}
void jAnalyzer::setPreviewState(bool isPreviewing)
{
	is_previewing = isPreviewing;
}
bool jAnalyzer::InFreeMode()
{
	return is_free_mode;
}
void jAnalyzer::SetFreeMode(bool isTrue)
{
	is_free_mode = isTrue;
}
float jAnalyzer::GetAverageVelocity()
{
	return average_velocity;
}