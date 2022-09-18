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
	};
	class jAnalyzer 
	{
	public:
		jAnalyzer();
		~jAnalyzer();

		auto GetData();

		void StartRecording();
		bool isRecording();
		void StopRecording();
		void OnFrameUpdate();
		bool RecordingExists();
		bool isPreviewing();
		void setPreviewState(bool isPreviewing);
		int32_t GetTotalFrames();
		bool InFreeMode();
		void SetFreeMode(bool isTrue);
		float GetAverageVelocity();

		void SaveFrameData(jump_data& jdata);
		jump_data* FetchFrameData(uint32_t frame);

		int32_t FindBounceFrame();
		int32_t FindRpgShot();
		int32_t FindHighestPoint();

		//std::unique_ptr<analyzer_data> ptr_data;
		std::vector<jump_data> data;
		uint32_t current_frame; //when recording
		bool is_recording;
		bool is_previewing;
		bool is_free_mode;
		float average_velocity;
		int32_t preview_frame; //in frame editor
	};
	inline jAnalyzer analyzer;
}

#endif