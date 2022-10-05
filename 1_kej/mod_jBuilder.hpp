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
	};

	struct jump_builder_s
	{
		bool get_playerState;
		builder_data_s builder_data;
		std::vector<jump_data> jData;

		void OnCreateNew();
		void OnUpdatePosition();

		void OnStartGenerating();
		void OnStopGenerating();

		bool isGeneratingMovement();
		bool MovementExists();

		void ClearData();
		void OnFrameUpdate();
		void SaveFrameData(jump_data& jData);
		int32_t GetTotalFrames();

		jump_data* FetchFrameData(int32_t frame);
		int32_t current_frame; //updated when generating movement

	private:
		bool is_generating_movement;

	};

	inline jump_builder_s jbuilder;

}


#endif