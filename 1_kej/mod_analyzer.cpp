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
	analyzer.backup_data.erase(analyzer.backup_data.begin(), analyzer.backup_data.end());
	analyzer.backup_data.clear();
	analyzer.backup_data.resize(0);
	analyzer.backup_data.insert(analyzer.backup_data.begin(), analyzer.data.begin(), analyzer.data.end());


	jAnalyzer::setPreviewState(false);
	jAnalyzer::SetFreeMode(false);
	ClearData();
	is_recording = true;


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
	analyzer.SetLastRecordingStopTime(clients->snap.ps.commandTime);

	

	is_recording = false;
}
void jAnalyzer::ClearData()
{
	current_frame = 0;
	preview_frame = 0;

	bounceFrames.erase(bounceFrames.begin(), bounceFrames.end());
	bounceFrames.clear();

	rpgFrames.erase(rpgFrames.begin(), rpgFrames.end());
	rpgFrames.clear();

	jumpFrame.erase(jumpFrame.begin(), jumpFrame.end());
	jumpFrame.clear();

	s_bounceFrames.erase(s_bounceFrames.begin(), s_bounceFrames.end());
	s_bounceFrames.clear();

	s_rpgFrames.erase(s_rpgFrames.begin(), s_rpgFrames.end());
	s_rpgFrames.clear();

	s_jumpFrame.erase(s_jumpFrame.begin(), s_jumpFrame.end());
	s_jumpFrame.clear();

	//collisionFrames.erase(bounceFrames.begin(), bounceFrames.end());
	//collisionFrames.clear();

	data.erase(data.begin(), data.end());
	data.clear();
	data.resize(0);

	segData.erase(segData.begin(), segData.end());
	segData.clear();
	segData.resize(0);

	//analyzer.backup_data.erase(analyzer.backup_data.begin(), analyzer.backup_data.end());
	//analyzer.backup_data.clear();
	//analyzer.backup_data.resize(0);

	SetLastRecordingStopTime(0);
	average_velocity = 0;
	is_recording = false;



}
void cg::jAnalyzer::OnFrameUpdate()
{
	//if (current_frame >= std::numeric_limits<int32_t>().max() - 1) {
	//	Com_PrintError(CON_CHANNEL_ERROR, "exceeded maximum amount of frames!\n");
	//	StopRecording();
	//}

	current_frame++;
}
void jAnalyzer::SaveFrameData(std::vector<jump_data>& storage, jump_data& jdata)
{
	if(storage.size() + 1 < storage.max_size())
		storage.push_back(jdata);
	else {
		Com_PrintError(CON_CHANNEL_ERROR, "exceeded maximum amount of frames!\n");
		StopRecording();
	}
}
jump_data* jAnalyzer::FetchFrameData(uint32_t frame)
{
	if (data.size() > frame)
		return &data[frame];

	//std::cout << data.size() << " > " << frame << '\n';
	return nullptr;
}
jump_data* jAnalyzer::FetchFrameData(std::vector<jump_data>& storage, uint32_t frame)
{
	if (storage.size() > frame)
		return &storage[frame];

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
int32_t jAnalyzer::GetTotalFrames(std::vector<jump_data>& storage)
{
	return storage.size() - 1;
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
	//float highestHeight = std::numeric_limits<float>().min();
	float highestHeight = -FLT_MAX;
	for (size_t i = 0; i < data.size(); i++) {

		if (data[i].origin[2] > highestHeight) {
			highestHeight = data[i].origin[2];
			highestFrame = i;
		}
	}
	return highestFrame;
}
int32_t jAnalyzer::FindHighestPoint(std::vector<jump_data>& storage)
{
	int32_t highestFrame(0);
	//float highestHeight = std::numeric_limits<float>().min();
	float highestHeight = -FLT_MAX;
	for (size_t i = 0; i < storage.size(); i++) {

		if (storage[i].origin[2] > highestHeight) {
			highestHeight = storage[i].origin[2];
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
bool jAnalyzer::InRecordingMode()
{
	return in_recording_mode;
}
void jAnalyzer::SetRecordingMode(bool isRecording)
{
	in_recording_mode = isRecording;
}
DWORD jAnalyzer::LastRecordingStoppedTime()
{
	return time_since_last_recording;
}
void jAnalyzer::SetLastRecordingStopTime(DWORD time)
{
	time_since_last_recording = time;
}
bool jAnalyzer::isPlayback()
{
	return is_playback;
}
bool jAnalyzer::RecordingPaused()
{
	return is_paused;
}
void jAnalyzer::PauseRecording()
{
	is_paused = true;
}
void jAnalyzer::ContinueRecording()
{
	is_paused = false;
}
void jAnalyzer::OnStartSegment()
{
	if (!RecordingExists()) {
		Com_PrintError(CON_CHANNEL_OBITUARY, "No active recording\n");
		return;
	}

	//if (Segmenter_RecordingExists()) {

	//	std::set<int>::iterator 

	//	a = rpgFrames.begin();
	//	for (size_t i = 0; i < segmenterData.oldRPGcount; i++) ++a;  rpgFrames.erase(a, rpgFrames.end());


	//	a = jumpFrame.begin();
	//	for (size_t i = 0; i < segmenterData.oldJumpcount; i++) ++a; jumpFrame.erase(a, jumpFrame.end());

	//	a = bounceFrames.begin();
	//	for (size_t i = 0; i < segmenterData.oldBouncecount; i++) ++a; bounceFrames.erase(a, bounceFrames.end());

	//}

	////store old information as a backup
	//segmenterData.oldBouncecount = bounceFrames.size();
	//segmenterData.oldRPGcount = rpgFrames.size();
	//segmenterData.oldJumpcount = jumpFrame.size();

	analyzer.backup_data.erase(analyzer.backup_data.begin(), analyzer.backup_data.end());
	analyzer.backup_data.clear();
	analyzer.backup_data.resize(0);
	analyzer.backup_data.insert(analyzer.backup_data.begin(), analyzer.segData.begin(), analyzer.segData.end());

	analyzer.segData.erase(analyzer.segData.begin(), analyzer.segData.end());
	analyzer.segData.clear();
	analyzer.segData.resize(0);

	preview_frame = NULL;


	memset(&segmenterData, 0, sizeof(segmenter_data));
	is_segmenting = true;
	segmenterData.mergeFrame = analyzer.segment_frame;

}
void jAnalyzer::OnEndSegment()
{
	is_segmenting = false;
	memset(&segmenterData, 0, sizeof(segmenter_data));

	
}
bool jAnalyzer::isSegmenting()
{
	return is_segmenting;
}

int jAnalyzer::Segmenter_Prepare()
{
	static bool needs_reset(false);
	static DWORD startTime(Sys_MilliSeconds());

	if (segmenterData.hasLaunched || !segmenterData.hasStarted) {
		startTime = Sys_MilliSeconds();
		segmenterData.hasLaunched = false;
	}

	segmenterData.hasStarted = true;
	if (segmenterData.isReady)
		return -1;


	if (segment_frame >= GetTotalFrames()+1)
		return -1;

	if ((startTime + (DWORD)(v::mod_jumpv_segtime.GetFloat() * 1000)) < Sys_MilliSeconds()) {

		jump_data* jData = FetchFrameData(segment_frame);

		if (jData) {
			Com_Printf(CON_CHANNEL_OBITUARY, "^2launch\n");
			VectorCopy(jData->origin, ps_loc->origin);
			VectorCopy(jData->velocity, ps_loc->velocity);

			CG_SetPlayerAngles(clients->cgameViewangles, jData->angles);

			ps_loc->pm_flags = ps_loc->pm_flags & 0xFFFFFE7F | PMF_JUMPING; //reset bouncing flags
			ps_loc->jumpOriginZ = jData->origin[2];

			current_frame = NULL;

			segmenterData.hasLaunched = true;
			segmenterData.isReady = true;




			return 0;
		}
	}



	return (startTime + (DWORD)(v::mod_jumpv_segtime.GetFloat() * 1000)) - Sys_MilliSeconds();
}
bool jAnalyzer::Segmenter_RecordingExists()
{
	return segData.size() > 0;
}