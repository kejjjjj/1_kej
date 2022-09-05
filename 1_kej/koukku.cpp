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
	write_addr(address, "\x90\x90\x90\x90\x90", 5);
}
void hook::write_addr(void* addr, const char* bytes, size_t len)
{
	write_addr(addr, (void*)bytes, len);
}
void hook::write_addr(void* addr, void* bytes, size_t len)
{
	DWORD oldProtect;

	VirtualProtect(addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(addr, bytes, len);
#pragma warning(suppress: 6387)
	VirtualProtect((LPVOID)addr, len, oldProtect, NULL);
}
void hook::write_addr(std::uintptr_t addr, const char* bytes, size_t len)
{
	return write_addr((void*)addr, (void*)bytes, len);
}
void hook::memcopy(void* dst, void* src, size_t len)
{
	return write_addr(dst, src, len);
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