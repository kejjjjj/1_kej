#include "pch.h"

//#ifdef _WIN64

LONG hook::install(void** ppPointer, void* pDetour)
{
	DetourTransactionBegin();
	DetourAttach(ppPointer, pDetour);
	DetourTransactionCommit();

	return 0;
}
//#else
//BYTE* hook::install(std::uintptr_t address, void* fnc)
//{
//	return DetourFunction((PBYTE)address, (PBYTE)fnc);
//}
//BYTE* hook::install(void* address, void* fnc)
//{
//	return DetourFunction((PBYTE)address, (PBYTE)fnc);
//}
//
//BOOL hook::remove(void* Trampoline, void* detourFunc)
//{
//	return DetourRemove((PBYTE)Trampoline, (PBYTE)detourFunc);
//}
//#endif
void hook::nop(std::uintptr_t address)
{
	DWORD oldProtect;

	VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)address, "\x90\x90\x90\x90\x90", 5);
#pragma warning(suppress: 6387)
	VirtualProtect((void*)address, 5, oldProtect, NULL);
}
void hook::write_addr(void* addr, const char* bytes, size_t len)
{
	DWORD oldProtect;

	VirtualProtect(addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(addr, bytes, len);
#pragma warning(suppress: 6387)
	VirtualProtect((LPVOID)addr, len, oldProtect, NULL);
}
void hook::write_addr(std::uintptr_t addr, const char* bytes, size_t len)
{
	write_addr((void*)addr, bytes, len);
}
void hook::write_addr(void* addr, BYTE* byte, size_t len)
{
	DWORD oldProtect;

	VirtualProtect(addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(addr, byte, len);
#pragma warning(suppress: 6387)
	VirtualProtect((LPVOID)addr, len, oldProtect, NULL);
}
void hook::get_bytes(void* addr, size_t len, BYTE* buffer)
{
	std::stringstream ss;
	std::string string;

	for (uint32_t i = 0; i < len; i++)
	{
		string = std::format("{:#x}", *(BYTE*)((size_t)addr + i));
		string.erase(0, 2);
		std::istringstream str(string);

		uint16_t val{};
		str >> std::hex >> val;
		buffer[i] = (BYTE)val;
	}

}
std::uintptr_t hook::find_pattern(std::string moduleName, std::string pattern)
{

	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo; K32GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;

	return find_pattern(rangeStart, rangeEnd, pattern);


}
std::uintptr_t hook::find_pattern(DWORD start_address, DWORD end_address, std::string pattern)
{
	hook* a = nullptr;
	const char* pat = pattern.c_str();
	//std::cout << "using pattern: [" << pat << "]\n";
	DWORD firstMatch = 0;
	MEMORY_BASIC_INFORMATION mbi{};
	for (DWORD pCur = start_address; pCur < end_address; pCur++)
	{
		if (!VirtualQuery((char*)pCur, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) 
			continue;

		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;    //one ?
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}
	std::cout << "pattern not found\n";
	return NULL;
}
const char* hook::bytes_to_text(const char* bytes)
{
	/*
	\x89\x45\xC1 -> 89 45 C1
	*/

	std::string result = bytes;
	std::string final_bytes;

	char buffer[1024 * 4];


	for (size_t i = 0; i < result.size(); i++) {
		if ((int)result[i] < 0) {
			snprintf(buffer, 9, "%X", result[i]);
			std::string new_result = buffer;
			new_result = new_result.substr(6);
			final_bytes.push_back(new_result[0]);
			final_bytes.push_back(new_result[1]);
			final_bytes.push_back(' ');
			continue;
		}
		else if ((int)result[i] == 0) {
			final_bytes.push_back(result[i]);
			final_bytes.push_back(' ');
			continue;
		}
		snprintf(buffer, 3, "%X", result[i]);
		final_bytes.push_back(buffer[0]);
		final_bytes.push_back(buffer[1]);
		final_bytes.push_back(' ');
	}

	//std::cout << "result: " << final_bytes << '\n';
	final_bytes.pop_back();
	const char* ret = final_bytes.c_str();

	return ret;
}