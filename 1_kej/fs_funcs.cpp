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

bool fs::F_CreateDirectory(std::string path)
{
	return _mkdir((path).c_str()) != -1;
}
bool fs::F_CreateFile(std::string path)
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
void fs::F_FilesInThisDirectory(std::string directory, std::vector<std::string>* out)
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
std::string fs::GetFileExtension(std::string file)
{

	int extensionPos = file.find_last_of(".");

	if (extensionPos < 0)
		return "No extension";

	file = file.substr(extensionPos);


	return file;
}
std::string fs::removeFileExtension(std::string file, size_t chars)
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