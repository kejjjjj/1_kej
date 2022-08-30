// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <psapi.h>
#include <iostream>
#include <utility>
#include <filesystem>
#include <direct.h>
#include <TlHelp32.h>
#include <array>
#include <intrin.h>
#include <functional>
#include <format>
#include <stdio.h>


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

//detours
#include "detours/detours.h"
#pragma comment(lib, "detours.lib")

#include "koukku.hpp"

#include "dvar.hpp"

#include "entry.hpp"

#include "cg_local.h"
#include "cg_offsets.h"
#include "cg_init.hpp"


#include "com_channel.h"

using namespace std::chrono_literals;


#endif //PCH_H
