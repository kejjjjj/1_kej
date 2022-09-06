// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define ON_SERVER *(int*)0x0797520 != 0
#define GROUND *(int*)0x0797520 == 1022
#define NOT_GROUND *(int*)0x0797520 == 1023
#define NOT_SERVER *(int*)0x0797520 == 0
#define VID_ACTIVE *(BYTE*)0x0CC1B704 > 0

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#define PI 3.14159265f
#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorClear( a )              ( ( a )[0] = ( a )[1] = ( a )[2] = 0 )

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


//#include <glm/vec2.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//#include <glm/common.hpp>
#include <glm/glm.hpp>

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

#include "scr_cmd.hpp"
#include "scr_functions.hpp"
#include "scr_main.hpp"
#include "scr_obj.hpp"

#include "r_world.h"

using namespace std::chrono_literals;


#endif //PCH_H
