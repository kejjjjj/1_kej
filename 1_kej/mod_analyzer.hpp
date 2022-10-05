#pragma once

#ifndef modanalyzer
#define modanalyzer

#include "pch.h"

namespace cg
{
	struct jump_data
	{
		vec3_t origin;
		vec3_t velocity;
		vec3_t angles;
		char forwardmove;
		char rightmove;
		vec3_t mins;
		vec3_t maxs;
		bool rpg_fired;
		bool bounced;
		int32_t FPS;
		bool colliding;
		bool jumped;
	};
	struct segmenter_data
	{

		int32_t mergeFrame; //merge the two recordings at this frame

		bool hasStarted; //true as soon as the menuresponse has been received
		bool hasLaunched; //readyup is done
		bool isReady; //can start recording

	};
	class jAnalyzer 
	{
	public:
		jAnalyzer();
		~jAnalyzer();

				//std::unique_ptr<analyzer_data> ptr_data;
		std::vector<jump_data> data; 
		std::vector<jump_data> backup_data;
		std::vector<jump_data> segData; //recorded segmenter data
		std::set<int> bounceFrames;
		std::set<int> rpgFrames;
		std::set<int> jumpFrame;

		std::set<int> s_bounceFrames;
		std::set<int> s_rpgFrames;
		std::set<int> s_jumpFrame;

		//std::set<int> collisionFrames;
		uint32_t current_frame; //when recording
		int32_t preview_frame; //in frame editor
		int32_t segment_frame;
		bool is_playback;
		float average_velocity;

		segmenter_data segmenterData;

		auto GetData();

		void StartRecording();
		bool isRecording();
		void StopRecording();
		bool RecordingPaused();
		void PauseRecording();
		void ContinueRecording();

		void ClearData();
		void OnFrameUpdate();
		bool RecordingExists();
		bool isPreviewing();
		bool InRecordingMode();
		void SetRecordingMode(bool isRecording);
		void setPreviewState(bool isPreviewing);
		int32_t GetTotalFrames();
		int32_t GetTotalFrames(std::vector<jump_data>& storage);

		bool InFreeMode();
		void SetFreeMode(bool isTrue);
		float GetAverageVelocity();
		DWORD LastRecordingStoppedTime();
		void SetLastRecordingStopTime(DWORD time);
		bool isPlayback();

		void SaveFrameData(std::vector<jump_data>& storage, jump_data& jdata);
		jump_data* FetchFrameData(uint32_t frame);
		jump_data* FetchFrameData(std::vector<jump_data>& storage, uint32_t frame);

		int32_t FindBounceFrame();
		int32_t FindRpgShot();
		int32_t FindHighestPoint();
		int32_t FindHighestPoint(std::vector<jump_data>& storage);
		void OnStartSegment();
		void OnEndSegment();
		bool isSegmenting();
		int Segmenter_Prepare();
		bool Segmenter_RecordingExists();

		bool IO_WriteData(const std::string run_name, const std::vector<jump_data>& _data);
		bool IO_ReadData(const std::string run_name);
		bool IO_StartReadingData(std::fstream& fp);
		bool IO_ReadMapName(std::fstream& fp, const char* run_name, std::string& buffer);
		template <typename t>
		bool IO_ReadVector1(std::fstream& fp, t& value);
		bool IO_ReadVector2(std::fstream& fp, vec2_t value);
		bool IO_ReadVector3(std::fstream& fp, vec3_t value);
		bool IO_FindExistingRuns(const char* mapname, std::vector<std::string>& runs);


	private:
		bool is_recording; //currently recording a clip
		bool is_previewing;
		bool is_free_mode;
		bool in_recording_mode; //true when the recording mode keybind is toggled on 
		bool is_paused;
		bool is_afk; //true when player stays still for 2000 snapshots
		bool is_segmenting; //current recording is a segment
		DWORD time_since_last_recording;
	};
	inline jAnalyzer analyzer;
}

#endif