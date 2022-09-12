#pragma once

#ifndef fslog
#define fslog

#include "pch.h"

enum log_level {
	LOG_NONE,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
};
struct log_s
{
	bool initialized;
};
namespace fs
{

	inline log_s _log;
	bool Log_Create(std::string path);
	bool Log_Write(log_level type, const char* msg, ...);
	bool Log_WriteWithModule(log_level type, const char* moduleName, const char* msg);
	std::string Log_LevelToText(log_level level);
}


#endif