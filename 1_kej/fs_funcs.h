#pragma once


#ifndef fsfuncs
#define fsfuncs
#include "pch.h"
namespace _fs = std::filesystem;
namespace fs
{
	enum class fileopen
	{
		FILE_IN = 1,
		FILE_OUT = 2,
		FILE_APP = 8,
		FILE_BINARY = 32
	};

	std::string GetExeFileName();
	std::string GetExePath();

	bool F_DirectoryExists(std::string directory_path);

	bool F_OpenFile(std::fstream& fp, std::string path, fileopen type);
	bool F_CloseFile(std::fstream& fp);

	bool F_WriteToFile(std::fstream& fp, std::string text);
	bool F_CreateDirectory(std::string path);
	bool F_CreateFile(std::string path);

	std::string GetFileExtension(std::string file);

	void F_FilesInThisDirectory(std::string directory, std::vector<std::string>* out);
	std::string removeFileExtension(std::string file, size_t chars);
	std::string F_GetFileName(std::string fullpath);


	uint64_t F_ReadAddress(std::fstream& fp);
	std::string F_ReadUntil(std::fstream& fp, char end);


}

#endif

