#include "pch.h"

std::string fs::GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}
std::string fs::GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}
bool fs::F_DirectoryExists(const std::string& directory_path)
{
	return _fs::exists(directory_path);
}
bool fs::F_FileExists(const std::string& directory, const std::string& file_name)
{
	if (!_fs::exists(directory)) {
		return false;
	}
	for (const auto& entry : _fs::directory_iterator(directory)) {
		
		if (entry.path().filename() == file_name) {
			//Com_Printf(CON_CHANNEL_CONSOLEONLY, "F_FileExists: %s == %s\n", entry.path().filename().c_str(), file_name.c_str());
			return true;
		}
	}
	return false;
}
bool fs::F_WriteToFile(std::fstream& fp, const std::string& text)
{
	if (!fp.is_open())
		return false;

	fp << text.c_str();

	return true;
}
bool fs::F_OpenFile(std::fstream& fp, const std::string& path, fileopen type)
{
	if (fp.is_open())
		return true;

	switch (type)
	{
	case fileopen::FILE_IN:
		fp.open(path, std::ios_base::in);
		break;
	case fileopen::FILE_OUT:
		fp.open(path, std::ios_base::out);
		break;
	case fileopen::FILE_APP:
		fp.open(path, std::ios_base::app);
		break;
	case fileopen::FILE_BINARY:
		fp.open(path, std::ios_base::binary);
		break;
	default:
		return false;
	}


	if (!fp.is_open())
		return false;


	return true;
}
bool fs::F_CloseFile(std::fstream& fp)
{
	if (fp.is_open())
		fp.close();

	if (fp.is_open()) //this should not be possible..?
		return false;


	return true;
}

bool fs::F_CreateDirectory(const std::string& path)
{
	return _mkdir((path).c_str()) != -1;
}
bool fs::F_CreateFile(const std::string& path)
{
	//std::fstream f;

	//if (!F_OpenFile(f, path, fs::fileopen::FILE_OUT))
	//	return false;
	//
	//F_CloseFile(f);

	std::fstream* nf = new std::fstream(path, std::ios_base::out);
	*nf << "";
	if (nf->is_open())
		nf->close();
	delete nf;

	return true;
}
void fs::F_FilesInThisDirectory(const std::string& directory, std::vector<std::string>* out)
{
	out->clear();
	out->resize(1);
	out->erase(out->begin(), out->end());
	int i{ 0 };
	if (!_fs::exists(directory)) {
		return;
	}
	for (const auto& entry : _fs::directory_iterator(directory)) {
		if (entry.is_directory())
			continue;

		std::string str = entry.path().string();

		out->push_back(str);
		i += 1;
	}
	out->resize(i);
}
std::string fs::GetFileExtension(const std::string& file)
{

	int extensionPos = file.find_last_of(".");

	if (extensionPos < 0)
		return "No extension";

	std::string file2 = file.substr(extensionPos);


	return file2;
}
std::string fs::removeFileExtension(const std::string& file, size_t chars)
{
	return file.substr(0, file.size() - chars);
}
std::string fs::F_GetFileName(std::string fullpath)
{
	size_t pos = fullpath.find_last_of('\\');

	if (pos < 1)
		return fullpath;

	fullpath = fullpath.substr(pos + 1);


	return fullpath;
}
//assuming we are now at the character before the 0x
uint64_t fs::F_ReadAddress(std::fstream& f) 
{
	F_Get(f);
	char ch = F_Get(f);

	if (ch != 'x')
		return 0;

	//F_Get(f); //skip the x

	std::string addr = F_ReadUntil(f, '\n');

	uint64_t value;
	std::istringstream(addr) >> std::hex >> value;

	return value;

}
std::string fs::F_ReadUntil(std::fstream& fp, char end)
{
	char ch;
	std::string txt;

	while (fp.good()) {
		ch = F_Get(fp);
		if (ch == end)
			break;
		txt.push_back(ch);
	}

	if (txt.size() < 1)
		return "N/A";
	
	

	return txt;
}
bool fs::F_isValidFileName(const std::string file_name)
{
	

	for (const auto& i : file_name) {
		if (!std::isalnum(i) && i != '-' && i != '_' && i != ' ')
			return false;

	}
	return true;
}
std::string fs::_GetLastError()
{
	const DWORD errorMessageID = ::GetLastError();
	char* messageBuffer = nullptr;

	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&messageBuffer, 0, NULL);

	Com_PrintError(CON_CHANNEL_CONSOLEONLY, "IO_WriteData failed with: %s\n", messageBuffer);

	std::string output = std::string(messageBuffer, size);

	LocalFree(messageBuffer);
	return output;
}

//F_Get keeps track of read contents
char fs::F_Get(std::fstream& fp)
{

	file.current_character = fp.get();
	file.current_column++;
	if (file.current_character == '\n') {
		file.lines_read++;
		file.current_column = 0;
	}
	
	return file.current_character;
}
void fs::F_Reset()
{
	memset(&file, 0, sizeof(file_s));
}
void fs::F_SyntaxError(const char* msg, ...)
{
	char v2[4096];
	va_list va;

	va_start(va, msg);
	_vsnprintf_s(v2, 0x1000u, msg, va);
	v2[4095] = 0;

	Com_PrintError(CON_CHANNEL_CONSOLEONLY , "Syntax error on line [%i, %i] with reason: [%s]\n", file.lines_read, file.current_column, v2);

	F_Reset();


}

std::vector<std::pair<std::string, LPDIRECT3DTEXTURE9>>
fs::FS_CreatePairsForTextures()
{

	std::vector<std::pair<std::string, LPDIRECT3DTEXTURE9>> pair;

	std::string ImagePath = std::string(GetExePath() + "\\1_kej\\images");

	if (!F_DirectoryExists(ImagePath)) {
		if (!F_CreateDirectory(ImagePath)) {
			Log_Write(LOG_ERROR, "Failed to create directory [%s]\n", ImagePath.c_str());
			return pair;
		}
	}

	std::vector<std::string> files;

	F_FilesInThisDirectory(ImagePath, &files);

	if (files.size() < 1)
		return pair;

	uint16_t index{ 0 };
	std::string name, ext;

	for (const auto& i : files) {

		name = F_GetFileName(i);
		ext = GetFileExtension(name);
		//name = removeFileExtension(name, ext.size());

		if (ext.find(".png") == std::string::npos && ext.find(".jpg") == std::string::npos) {
			Com_PrintWarning(CON_CHANNEL_CONSOLEONLY, "FS_CreatePairsForTextures: unsupported filetype '%s' for file '%s'\n", ext.c_str(), name.c_str());
			continue;
		}

		//name += ".png";

		pair.push_back(std::make_pair(name, r::tabs[index]));


		index++;

	}

	return pair;



}
bool fs::F_FileAlreadyExists(const std::string& directory, const std::string& file)
{
	std::vector<std::string> files;

	F_FilesInThisDirectory(directory, &files);
	std::string const full = directory + "\\" + file + ".kej";

	for (const auto& i : files) {

		if (!i.compare(full))
			return true;

	}

	return false;
}
bool fs::FS_AllNecessaryImagesExist()
{
	const char* should_exist[10] = {
		"Automation",
		"Error_no_load",
		"Game",
		"Home",
		"Jump Builder",
		"Jump Preview",
		"Jumping",
		"Rpg",
		"Settings_no_load",
		"Visuals"
	};

	for (size_t j = 0; j < IM_ARRAYSIZE(should_exist); j++) {
		bool exists(false);

		for (auto& i : r::imagePairs) {
			if (i.first.find(should_exist[j]) != std::string::npos) {
				exists = true;
				break;
			}


		}
		if (!exists) {
			Log_Write(LOG_FATAL, "Couldn't find image '%s' from '%s'\n", should_exist[j], std::string(GetExePath() + "\\1_kej\\images").c_str());
			return false;
		}


	}

	return true;
}