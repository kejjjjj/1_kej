#pragma once

#ifndef koukku_
#define koukku_
#include "pch.h"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

struct hook //a VERY basic structure to do the most basic things!
{

	LONG install(PVOID* ppPointer, PVOID pDetour);

	//BYTE* install(std::uintptr_t address, void* func);
	//BYTE* install(void* address, void* func);
	//BOOL remove(void* Trampoline, void* detourFunc);
	//#endif
	void nop(std::uintptr_t address);
	void write_addr(void* addr, const char* bytes, size_t len);
	void write_addr(std::uintptr_t addr, const char* bytes, size_t len);
	void write_addr(void* addr, BYTE* byte, size_t len);

	void get_bytes(void* addr, size_t len, BYTE* buffer);

	std::uintptr_t find_pattern(std::string moduleName, std::string pattern);
	std::uintptr_t find_pattern(DWORD start_address, DWORD end_address, std::string pattern);
	const char* bytes_to_text(const char* bytes);


};

#endif