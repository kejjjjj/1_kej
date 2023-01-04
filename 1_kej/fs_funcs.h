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

	struct file_s
	{
		DWORD lines_read;
		DWORD current_column;
		char current_character;

	};

	std::string GetExeFileName();
	std::string GetExePath();

	bool F_isValidFileName(const std::string file_name);

	bool F_DirectoryExists(const std::string& directory_path);
	bool F_FileExists(const std::string& directory, const std::string& file_name);

	bool F_OpenFile(std::fstream& fp, const std::string& path, fileopen type);
	bool F_CloseFile(std::fstream& fp);

	bool F_WriteToFile(std::fstream& fp, const std::string& text);
	bool F_CreateDirectory(const std::string& path);
	bool F_CreateFile(const std::string& path);

	std::string GetFileExtension(const std::string& file);


	void F_FilesInThisDirectory(const std::string& directory, std::vector<std::string>* out);
	std::string removeFileExtension(const std::string& file, size_t chars);
	std::string F_GetFileName(std::string const fullpath);
	std::string F_GoToPreviousDirectory(std::string& directory);


	uint64_t F_ReadAddress(std::fstream& fp);
	std::string F_ReadUntil(std::fstream& fp, char end);

	char F_Get(std::fstream& fp);
	void F_Reset();
	void F_SyntaxError(const char* message, ...);
	std::string _GetLastError();
	inline file_s file;

	bool F_FileAlreadyExists(const std::string& directory, const std::string& path);


	std::vector<std::pair<std::string, LPDIRECT3DTEXTURE9>>
		FS_CreatePairsForTextures();

	bool FS_AllNecessaryImagesExist(); 

}

#endif

