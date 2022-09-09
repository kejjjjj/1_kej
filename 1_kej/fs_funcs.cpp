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
bool fs::F_DirectoryExists(std::string directory_path)
{
	return _fs::exists(directory_path);
}
bool fs::F_WriteToFile(std::fstream& fp, std::string text)
{
	if (!fp.is_open())
		return false;

	fp << text.c_str();

	return true;
}
bool fs::F_OpenFile(std::fstream& fp, std::string path, fileopen type)
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
		fp.open(path, std::ios_base::out);
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

bool fs::F_CreateDirectory(std::string path)
{
	return _mkdir((path).c_str()) != -1;
}
//assuming we are now at the character before the 0x
uint64_t fs::F_ReadAddress(std::fstream& f) 
{
	f.get();
	char ch = f.get();

	if (ch != 'x')
		return 0;

	//f.get(); //skip the x

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
		ch = fp.get();
		if (ch == end)
			break;
		txt.push_back(ch);
	}

	if (txt.size() < 1)
		return "N/A";

	

	return txt;
}