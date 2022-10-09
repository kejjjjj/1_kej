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
#define VID_ACTIVE (*(BYTE*)0x0CC1B704 != 0)

#define ANGLE2SHORT( x )  ( (int)( ( x ) * 65536 / 360 ) & 65535 )
#define SHORT2ANGLE( x )  ( ( x ) * ( 360.0 / 65536 ) )

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#define PI 3.14159265f
#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorAddAll(a,b,c)		((c)[0]=(a)[0]+(b),(c)[1]=(a)[1]+(b),(c)[2]=(a)[2]+(b))
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define VectorScaleAll(a,b,c)	((c)[0]=(a)[0]*(b),(c)[1]=(a)[1]*(b),(c)[2]=(a)[2]*(b))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorClear( a )              ( ( a )[0] = ( a )[1] = ( a )[2] = 0 )

#define DEG2RAD(a) (((a) * M_PI) / 180.0F)
#define RAD2DEG(a) (((a) * 180.0f) / M_PI)
#define RAD2SHORT(a) ((a) * (32768.f / (float)M_PI))
#define SHORT2RAD(a) ((a) * ((float)M_PI / 32768.f))
#define SHORT2DEG(a) (((a) / 32768.f) * 180.0f)

// plane types are used to speed some tests
// 0-2 are axial planes
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2
#define	PLANE_NON_AXIAL	3

//hopefully the user has qwerty layout..
#define WE GetAsyncKeyState('W') < 0 && GetAsyncKeyState('E') < 0
#define WQ GetAsyncKeyState('W') < 0 && GetAsyncKeyState('Q') < 0

#define SE GetAsyncKeyState('S') < 0 && GetAsyncKeyState('E') < 0
#define SQ GetAsyncKeyState('S') < 0 && GetAsyncKeyState('Q') < 0


#define	VALUE2COLOR(x,y)	((x/y)*128)


#pragma warning(disable : 26495)

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
#include <timeapi.h>
#include <set>
#include <list>

//#include <glm/vec2.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//#include <glm/common.hpp>
#include <glm/glm.hpp>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//DIRECTX
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>

//IMGUI
#include "imGui/imgui.h"
#include "imGui/imgui_impl_dx9.h"
#include "imGui/imgui_impl_win32.h"
#include "imGui/imgui_internal.h"

#include "imgui_color_gradient.hpp"

//detours
#include "detours/detours.h"
#pragma comment(lib, "detours.lib")

#include "koukku.hpp"

#include "entry.hpp"

#include "q_math.hpp"

#include "dvar.hpp"

#include "cg_local.h"
#include "cg_offsets.h"
#include "cg_init.hpp"

#include "mod_vis.hpp"
#include "mod_analyzer.hpp"

#include "mod_jumps.hpp"
#include "mod_automation.hpp"
#include "mod_jBuilder.hpp"

#include "cg_angle.hpp"
#include "cg_main.hpp"

#include "game_funcs.hpp"

#include "g_trace.h"

#include "fs_funcs.h"
#include "fs_log.hpp"
#include "evar.h"
#include "evar_config.h"
#include "evars.h"

#include "com_channel.h"

#include "cmod_data.hpp"

#include "scr_cmd.hpp"
#include "scr_functions.hpp"
#include "scr_main.hpp"
#include "scr_obj.hpp"
#include "scr_menuresponse.hpp"

#include "menu_items.hpp"

#include "r_init.hpp"
#include "r_drawtools.hpp"
#include "r_world.hpp"
#include "r_ui.hpp"
#include "r_ui_jbuilder.hpp"
#include "r_ui_assetmanager.hpp"

#include "cl_main.hpp"

#include "sv_ccmds.hpp"

#include "bg_pmove.hpp"
#include "bg_weapon.hpp"

#include "sys_tools.hpp"


using namespace std::chrono_literals;


#endif //PCH_H
