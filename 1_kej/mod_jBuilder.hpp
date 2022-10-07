#pragma once

#ifndef _jbuilder
#define _jbuilder

#include "pch.h"

namespace cg
{
	struct builder_data_s
	{
		pmove_t* pm;
		pml_t* pml;
		bool run_created;
	};
	struct segment_data_s
	{
		size_t begin;
		size_t end;
		int32_t framecount;
		char forwardmove;
		char rightmove;
		pmove_t end_pm; //data @ segment's last frame
		pml_t end_pml; //data @ segment's last frame
		playerState_s end_ps; //LOTS OF DATA
		std::vector<jump_data> jData; 
	};
	struct jump_builder_s
	{
		bool get_playerState;
		builder_data_s builder_data;
		std::vector<jump_data> jData;

		bool isEditing(); //true whenever the menu is open
		void SetEditMode(bool mode);

		void OnCreateNew();
		void OnDeleteProject();
		void OnUpdateAllPositions();
		void OnUpdatePosition(const bool erase);

		void OnStartGenerating();
		void OnStopGenerating();

		bool isGeneratingMovement();
		bool MovementExists();

		void OnGetSegmentData();

		void ClearData();
		void OnFrameUpdate();
		void SaveFrameData(jump_data& jData);
		void SaveFrameData(std::vector<jump_data>& container, jump_data& jData);

		size_t GetTotalFrames();

		void OnUpdateOffsets();

		void OnAddSegment();

		jump_data* FetchFrameData(int32_t frame);
		int32_t current_frame; //updated when generating movement
		int32_t preview_frame; //currently selected frame in the menu
		int32_t current_segment;
		int32_t segment_frameCount;

		std::vector<segment_data_s> segments;

	private:
		bool is_generating_movement;
		bool is_editing;
		size_t total_frames;

	};

	inline jump_builder_s jbuilder;

}


#endif