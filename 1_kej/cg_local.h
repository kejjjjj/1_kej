#pragma once

#ifndef STRUCTS_H
#define STRUCTS_H
#include "pch.h"
#define MAX_CVAR_OPTIONSTRS    6
#define	PITCH					0		// up / down
#define	YAW						1		// left / right
#define	ROLL					2		// fall over

#define EF_CROUCHING		0x04
//#define EF_PRONE			0x08

#define	GENTITYNUM_BITS			10
#define	MAX_GENTITIES			(1<<GENTITYNUM_BITS)

#define MAX_PLAYERS				64

#define MAX_WEAPONS				28
#define Q_COLOR_ESCAPE	'^'
#define Q_IsColorString(p)		( p && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) != Q_COLOR_ESCAPE )

#define Sound(a)				CreateThread(0,0, killSound, (void*)a, 0, 0)

#define MakeThread(a)			CreateThread(0,0, a, 0, 0, 0)
#define MakeThreadArg(a, b)		CreateThread(0,0, a, (LPVOID)b, 0, 0)

#define NullVector( Rec ) { Rec[0] = NULL; Rec[1] = NULL; Rec[2] = NULL; }
#define RemoveRecoil( Rec ) { NullVector( Rec[0] ); NullVector( Rec[1] ); NullVector( Rec[2] ); }

#define	ENTITYNUM_NONE			(MAX_GENTITIES - 1)

// lower bits are stronger, and will eat weaker brushes completely
#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

#pragma once

// This allows us to compile our structures in IDA, for easier reversing :3
//MOST OF THIS IS FROM IW3XO SOURCE CODE!!
//https://github.com/xoxor4d/iw3xo-dev/blob/master/

#ifdef __cplusplus
namespace cg
{
#else
#define COD4
#define PC
#endif

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

typedef unsigned __int16 ScriptString;

typedef void(*xfunction_t)();

typedef struct scr_function_s
{
	struct scr_function_s* next;
	char* name;
	xfunction_t				function;
	bool					developer;
} scr_function_t;

enum PM_MTYPE
{
	STOCK = 0x0,
	DEFRAG = 0x1,
	CS = 0x2,
};

enum XO_SHADEROVERLAY
{
	NONE = 0x0,
	Z_SHADER_SSAO = 0x1,
	Z_SHADER_POSTFX_CELLSHADING = 0x2,
	Z_SHADER_POSTFX_OUTLINER = 0x3,
	FLOATZ_DISPLAY = 0x4,
	CUSTOM = 0x5,
};
enum pmflags_t
{
	PMF_NONE = 0x0,
	PMF_PRONE = 0x1,
	PMF_DUCKED = 0x2,
	PMF_MANTLE = 0x4,
	PMF_LADDER = 0x8,
	PMF_SIGHT_AIMING = 0x10,
	PMF_BACKWARDS_RUN = 0x20,
	PMF_LADDER_DOWN = 0x30,
	PMF_WALKING = 0x40,
	PMF_TIME_LAND = 0x80,
	PMF_TIME_KNOCKBACK = 0x100,
	PMF_PRONEMOVE_OVERRIDDEN = 0x200,
	PMF_RESPAWNED = 0x400,
	PMF_FROZEN = 0x800,
	PMF_PRONE_BLOCKED = 0x1000,
	PMF_LADDER_FALL = 0x2000,
	PMF_JUMPING = 0x4000,
	PMF_SPRINTING = 0x8000,
	PMF_SHELLSHOCKED = 0x10000,
	PMF_MELEE_CHARGE = 0x20000,
	PMF_NO_SPRINT = 0x40000,
	PMF_NO_JUMP = 0x80000,
	PMF_VEHICLE_ATTACHED = 0x100000,
};
enum surfTraceType_t
{
	SURF_NODAMAGE = 0x1,
	SURF_SLICK = 0x2,
	SURF_SKY = 0x4,
	SURF_LADDER = 0x8,
	SURF_NOIMPACT = 0x10,
	SURF_NOMARKS = 0x20,
	SURF_NODRAW = 0x80,
	SURF_NOPENETRATE = 0x100,
	SURF_NOLIGHTMAP = 0x400,
	SURF_NOSTEPS = 0x2000,
	SURF_NONSOLID = 0x4000,
	SURF_NODLIGHT = 0x20000,
	SURF_NOCASTSHADOW = 0x40000,
	SURF_MANTLEON = 0x2000000,
	SURF_MANTLEOVER = 0x4000000,
	SURF_PORTAL = 0x80000000,
	SURF_BARK = 0x100000,
	SURF_BRICK = 0x200000,
	SURF_CARPET = 0x300000,
	SURF_CLOTH = 0x400000,
	SURF_CONCRETE = 0x500000,
	SURF_DIRT = 0x600000,
	SURF_FLESH = 0x700000,
	SURF_FOLIAGE = 0x800000,
	SURF_GLASS = 0x900000,
	SURF_GRASS = 0xA00000,
	SURF_GRAVEL = 0xB00000,
	SURF_ICE = 0xC00000,
	SURF_METAL = 0xD00000,
	SURF_MUD = 0xE00000,
	SURF_PAPER = 0xF00000,
	SURF_PLASTER = 0x1000000,
	SURF_ROCK = 0x1100000,
	SURF_SAND = 0x1200000,
	SURF_SNOW = 0x1300000,
	SURF_WATER = 0x1400000,
	SURF_WOOD = 0x1500000,
	SURF_ASPHALT = 0x1600000,
	SURF_CERAMIC = 0x1700000,
	SURF_PLASTIC = 0x1800000,
	SURF_RUBBER = 0x1900000,
	SURF_CUSHION = 0x1A00000,
	SURF_FRUIT = 0x1B00000,
	SURF_PAINTEDMETAL = 0x1C00000,
};

enum pmtype_t
{
	PM_NORMAL = 0x0,
	PM_NORMAL_LINKED = 0x1,
	PM_NOCLIP = 0x2,
	PM_UFO = 0x3,
	PM_SPECTATOR = 0x4,
	PM_INTERMISSION = 0x5,
	PM_LASTSTAND = 0x6,
	PM_DEAD = 0x7,
	PM_DEAD_LINKED = 0x8,
};
enum pmeflags_t
{
	EF_TELEPORT_BIT = 0x2,
	EF_DUCKED = 0x4,
	EF_PRONE = 0x8,
	EF_NOT_STANDING = 0xC,
	EF_NODRAW = 0x20,
	EF_FIRING = 0x40,
	EF_TURRET_ACTIVE_PRONE = 0x100,
	EF_TURRET_ACTIVE_DUCK = 0x200,
	EF_TURRET_ACTIVE = 0x300,
	EF_AIM_ASSIST = 0x800,
	EF_VEHICLE_ACTIVE = 0x4000,
	EF_TIMED_OBJECT = 0x10000,
	EF_DEAD = 0x20000,
	EF_ADS = 0x40000,
	EF_VOTED = 0x100000,
	EF_TALK = 0x200000,
};

enum weaponstate_t
{
	WEAPON_READY = 0x0,
	WEAPON_RAISING = 0x1,
	WEAPON_RAISING_ALTSWITCH = 0x2,
	WEAPON_DROPPING = 0x3,
	WEAPON_DROPPING_QUICK = 0x4,
	WEAPON_FIRING = 0x5,
	WEAPON_RECHAMBERING = 0x6,
	WEAPON_RELOADING = 0x7,
	WEAPON_RELOADING_INTERUPT = 0x8,
	WEAPON_RELOAD_START = 0x9,
	WEAPON_RELOAD_START_INTERUPT = 0xA,
	WEAPON_RELOAD_END = 0xB,
	WEAPON_MELEE_INIT = 0xC,
	WEAPON_MELEE_FIRE = 0xD,
	WEAPON_MELEE_END = 0xE,
	WEAPON_OFFHAND_INIT = 0xF,
	WEAPON_OFFHAND_PREPARE = 0x10,
	WEAPON_OFFHAND_HOLD = 0x11,
	WEAPON_OFFHAND_START = 0x12,
	WEAPON_OFFHAND = 0x13,
	WEAPON_OFFHAND_END = 0x14,
	WEAPON_DETONATING = 0x15,
	WEAPON_SPRINT_RAISE = 0x16,
	WEAPON_SPRINT_LOOP = 0x17,
	WEAPON_SPRINT_DROP = 0x18,
	WEAPON_NIGHTVISION_WEAR = 0x19,
	WEAPON_NIGHTVISION_REMOVE = 0x1A,
	WEAPONSTATES_NUM = 0x1B,
};
enum Q3WeaponNames
{
	Q3_NONE = 0x0,
	Q3_ROCKET = 0x1,
	Q3_PLASMA = 0x2,
};

enum GfxRenderTargetId
{
	R_RENDERTARGET_SAVED_SCREEN = 0x0,
	R_RENDERTARGET_FRAME_BUFFER = 0x1,
	R_RENDERTARGET_SCENE = 0x2,
	R_RENDERTARGET_RESOLVED_POST_SUN = 0x3,
	R_RENDERTARGET_RESOLVED_SCENE = 0x4,
	R_RENDERTARGET_FLOAT_Z = 0x5,
	R_RENDERTARGET_DYNAMICSHADOWS = 0x6,
	R_RENDERTARGET_PINGPONG_0 = 0x7,
	R_RENDERTARGET_PINGPONG_1 = 0x8,
	R_RENDERTARGET_SHADOWCOOKIE = 0x9,
	R_RENDERTARGET_SHADOWCOOKIE_BLUR = 0xA,
	R_RENDERTARGET_POST_EFFECT_0 = 0xB,
	R_RENDERTARGET_POST_EFFECT_1 = 0xC,
	R_RENDERTARGET_SHADOWMAP_SUN = 0xD,
	R_RENDERTARGET_SHADOWMAP_SPOT = 0xE,
	R_RENDERTARGET_COUNT = 0xF,
	R_RENDERTARGET_NONE = 0x10,
};

enum hitLocation_t
{
	HITLOC_NONE = 0x0,
	HITLOC_HELMET = 0x1,
	HITLOC_HEAD = 0x2,
	HITLOC_NECK = 0x3,
	HITLOC_TORSO_UPR = 0x4,
	HITLOC_TORSO_LWR = 0x5,
	HITLOC_R_ARM_UPR = 0x6,
	HITLOC_L_ARM_UPR = 0x7,
	HITLOC_R_ARM_LWR = 0x8,
	HITLOC_L_ARM_LWR = 0x9,
	HITLOC_R_HAND = 0xA,
	HITLOC_L_HAND = 0xB,
	HITLOC_R_LEG_UPR = 0xC,
	HITLOC_L_LEG_UPR = 0xD,
	HITLOC_R_LEG_LWR = 0xE,
	HITLOC_L_LEG_LWR = 0xF,
	HITLOC_R_FOOT = 0x10,
	HITLOC_L_FOOT = 0x11,
	HITLOC_GUN = 0x12,
	HITLOC_NUM = 0x13,
};

enum scriptAnimEventTypes_t
{
	ANIM_ET_PAIN = 0x0,
	ANIM_ET_DEATH = 0x1,
	ANIM_ET_FIREWEAPON = 0x2,
	ANIM_ET_JUMP = 0x3,
	ANIM_ET_JUMPBK = 0x4,
	ANIM_ET_LAND = 0x5,
	ANIM_ET_DROPWEAPON = 0x6,
	ANIM_ET_RAISEWEAPON = 0x7,
	ANIM_ET_CLIMB_MOUNT = 0x8,
	ANIM_ET_CLIMB_DISMOUNT = 0x9,
	ANIM_ET_RELOAD = 0xA,
	ANIM_ET_CROUCH_TO_PRONE = 0xB,
	ANIM_ET_PRONE_TO_CROUCH = 0xC,
	ANIM_ET_STAND_TO_CROUCH = 0xD,
	ANIM_ET_CROUCH_TO_STAND = 0xE,
	ANIM_ET_STAND_TO_PRONE = 0xF,
	ANIM_ET_PRONE_TO_STAND = 0x10,
	ANIM_ET_MELEEATTACK = 0x11,
	ANIM_ET_KNIFE_MELEE = 0x12,
	ANIM_ET_KNIFE_MELEE_CHARGE = 0x13,
	ANIM_ET_SHELLSHOCK = 0x14,
	NUM_ANIM_EVENTTYPES = 0x15,
};

struct ScreenPlacement
{
	float scaleVirtualToReal[2];
	float scaleVirtualToFull[2];
	float scaleRealToVirtual[2];
	float virtualViewableMin[2];
	float virtualViewableMax[2];
	float realViewportSize[2];
	float realViewableMin[2];
	float realViewableMax[2];
	float subScreenLeft;
};

struct Message
{
	int startTime;
	int endTime;
};

struct MessageLine
{
	int messageIndex;
	int textBufPos;
	int textBufSize;
	int typingStartTime;
	int lastTypingSoundTime;
	int flags;
};

struct MessageWindow
{
	MessageLine* lines;
	Message* messages;
	char* circularTextBuffer;
	int textBufSize;
	int lineCount;
	int padding;
	int scrollTime;
	int fadeIn;
	int fadeOut;
	int textBufPos;
	int firstLineIndex;
	int activeLineCount;
	int messageIndex;
};

struct MessageBuffer
{
	char gamemsgText[4][2048];
	MessageWindow gamemsgWindows[4];
	MessageLine gamemsgLines[4][12];
	Message gamemsgMessages[4][12];
	char miniconText[4096];
	MessageWindow miniconWindow;
	MessageLine miniconLines[100];
	Message miniconMessages[100];
	char errorText[1024];
	MessageWindow errorWindow;
	MessageLine errorLines[5];
	Message errorMessages[5];
};

struct field_t
{
	int cursor;
	int scroll;
	int drawWidth;
	int widthInPixels;
	float charHeight;
	int fixedSize;
	char buffer[256];
};
struct VariableStackBuffer
{
	const char* pos;
	unsigned __int16 size;
	unsigned __int16 bufLen;
	unsigned __int16 localId;
	char time;
	char buf[1];
};
union VariableUnion
{
	int intValue;
	float floatValue;
	unsigned int stringValue;
	const float* vectorValue;
	const char* codePosValue;
	unsigned int pointerValue;
	VariableStackBuffer* stackValue;
	unsigned int entityOffset;
};
struct VariableValue
{
	VariableUnion u;
	int type;
};

struct Console
{
	int initialized;
	MessageWindow consoleWindow;
	MessageLine consoleLines[1024];
	Message consoleMessages[1024];
	char consoleText[32768];
	char textTempLine[512];
	unsigned int lineOffset;
	int displayLineOffset;
	int prevChannel;
	bool outputVisible;
	int fontHeight;
	int visibleLineCount;
	int visiblePixelWidth;
	float screenMin[2];
	float screenMax[2];
	MessageBuffer messageBuffer[1];
	float color[4];
};
struct GfxWindowTarget
{
	HWND__* hwnd;
	void* swapChain;
	int width;
	int height;
};
struct __declspec(align(8)) DxGlobals
{
	HINSTANCE__* hinst;
	IDirect3D9* d3d9;
	IDirect3DDevice9* device;
	unsigned int adapterIndex;
	bool adapterNativeIsValid;
	int adapterNativeWidth;
	int adapterNativeHeight;
	int adapterFullscreenWidth;
	int adapterFullscreenHeight;
	int depthStencilFormat;
	unsigned int displayModeCount;
	void* displayModes[256];
	const char* resolutionNameTable[257];
	const char* refreshRateNameTable[257];
	char modeText[5120];
	void* fencePool[8];
	unsigned int nextFence;
	int gpuSync;
	int multiSampleType;
	unsigned int multiSampleQuality;
	int sunSpriteSamples;
	void* singleSampleDepthStencilSurface;
	bool deviceLost;
	bool inScene;
	int targetWindowIndex;
	int windowCount;
	GfxWindowTarget windows[1];
	int flushGpuQueryCount;
	void* flushGpuQuery;
	unsigned __int64 gpuSyncDelay;
	unsigned __int64 gpuSyncStart;
	unsigned __int64 gpuSyncEnd;
	bool flushGpuQueryIssued;
	int linearNonMippedMinFilter;
	int linearNonMippedMagFilter;
	int linearMippedMinFilter;
	int linearMippedMagFilter;
	int anisotropicMinFilter;
	int anisotropicMagFilter;
	int linearMippedAnisotropy;
	int anisotropyFor2x;
	int anisotropyFor4x;
	int mipFilterMode;
	unsigned int mipBias;
	void* swapFence;
};
struct conAddons_CursorPos
{
	float x;
	float y;
};

struct fltCon_Dimensions
{
	float width;
	float height;
};

struct fltCon_Anker
{
	float left;
	float top;
	float right;
	float bottom;
};

struct fltCon_borderClip
{
	bool left;
	bool top;
	bool right;
	bool bottom;
};

struct fltCon_s
{
	bool				flt_initialized;
	bool				flt_enabled;
	bool				flt_isMoving;
	bool				flt_wasUsed;
	bool				flt_wasReset;
	bool				flt_isResizing;
	fltCon_borderClip	fltClippedAtBorder;
	fltCon_Anker		fltAnker;
	fltCon_Dimensions	fltDimensions;
	fltCon_Dimensions	fltMinDimensions;
};

struct conItem_slider
{
	float x;
	float y;
	float w;
	float h;
	float padding;
};

struct conItem_text
{
	float x;
	float y;
	float h;
};

struct conItem_box
{
	float x;
	float y;
	float w;
	float h;
};

struct conItems_conType
{
	conItem_box			inputBox;
	conItem_box			outputBox;
	conItem_text		outputText;
	conItem_slider		outputSlider;
	conItem_box			hintBoxUpper;
	conItem_text		hintBoxUpperText;
	conItem_box			hintBoxLower;
	conItem_text		hintBoxLowerText;
	conItem_box			hintBoxTotal;
	conItem_box			resizeBtnTrigger;
};

struct conItems_s
{
	conItems_conType	smallCon;
	conItems_conType	fullCon;
};

struct Console_Addons
{
	fltCon_s			fltCon;
	conItems_s			conItems;
	conAddons_CursorPos	cursorPos;
	conAddons_CursorPos	cursorPosSaved;
	conAddons_CursorPos	cursorPosSavedOnClick;
	fltCon_Dimensions	viewportRes;
	bool				fullConFirstFrame;
	int					cursorToggleTimeout;
};

struct ConDrawInputGlob
{
	char autoCompleteChoice[64];
	int matchIndex;
	int matchCount;
	const char* inputText;
	int inputTextLen;
	bool hasExactMatch;
	bool mayAutoComplete;
	float x;
	float y;
	float leftX;
	float fontHeight;
};

enum scrHorzAlignment
{
	HORZ_LEFT = 0,
	HORZ_CENTER = 1,
	HORZ_RIGHT = 2,
	HORZ_FULLSCREEN = 3,
	HORZ_NONE = 4,
	HORZ_VIRTUAL = 5,
	HORZ_CENTER_SAFE = 6,
	HORZ_CONSOLE_SPECIAL = 7,
};

enum scrVertAlignment
{
	VERT_TOP = 0,
	VERT_CENTER = 1,
	VERT_BOTTOM = 2,
	VERT_FULLSCREEN = 3,
	VERT_NONE = 4,
	VERT_VIRTUAL = 5,
	VERT_CENTER_SAFE = 6,
};

enum XAssetType
{
	ASSET_TYPE_XMODELPIECES = 0x0,
	ASSET_TYPE_PHYSPRESET = 0x1,
	ASSET_TYPE_XANIMPARTS = 0x2,
	ASSET_TYPE_XMODEL = 0x3,
	ASSET_TYPE_MATERIAL = 0x4,
	ASSET_TYPE_TECHNIQUE_SET = 0x5,
	ASSET_TYPE_IMAGE = 0x6,
	ASSET_TYPE_SOUND = 0x7,
	ASSET_TYPE_SOUND_CURVE = 0x8,
	ASSET_TYPE_LOADED_SOUND = 0x9,
	ASSET_TYPE_CLIPMAP = 0xA,
	ASSET_TYPE_CLIPMAP_PVS = 0xB,
	ASSET_TYPE_COMWORLD = 0xC,
	ASSET_TYPE_GAMEWORLD_SP = 0xD,
	ASSET_TYPE_GAMEWORLD_MP = 0xE,
	ASSET_TYPE_MAP_ENTS = 0xF,
	ASSET_TYPE_GFXWORLD = 0x10,
	ASSET_TYPE_LIGHT_DEF = 0x11,
	ASSET_TYPE_UI_MAP = 0x12,
	ASSET_TYPE_FONT = 0x13,
	ASSET_TYPE_MENULIST = 0x14,
	ASSET_TYPE_MENU = 0x15,
	ASSET_TYPE_LOCALIZE_ENTRY = 0x16,
	ASSET_TYPE_WEAPON = 0x17,
	ASSET_TYPE_SNDDRIVER_GLOBALS = 0x18,
	ASSET_TYPE_FX = 0x19,
	ASSET_TYPE_IMPACT_FX = 0x1A,
	ASSET_TYPE_AITYPE = 0x1B,
	ASSET_TYPE_MPTYPE = 0x1C,
	ASSET_TYPE_CHARACTER = 0x1D,
	ASSET_TYPE_XMODELALIAS = 0x1E,
	ASSET_TYPE_RAWFILE = 0x1F,
	ASSET_TYPE_STRINGTABLE = 0x20,
	ASSET_TYPE_COUNT = 0x21,
	ASSET_TYPE_STRING = 0x21,
	ASSET_TYPE_ASSETLIST = 0x22,
};

struct cmd_function_s
{
	cmd_function_s* next;
	const char* name;
	const char* args;			//autoCompleteDir;
	const char* description;	// autoCompleteExt
	void(__cdecl* function)();
};


enum DB_FILE_EXISTS_PATH
{
	DB_PATH_ZONE = 0,
	DB_PATH_MAIN = 1,
	DB_PATH_USERMAPS = 2
};

enum XZONE_FLAGS
{
	XZONE_ZERO = 0x0,

	XZONE_LOC_POST_GFX = 0x0,
	XZONE_LOC_POST_GFX_FREE = 0x0,

	XZONE_LOC_COMMON = 0x1,
	XZONE_LOC_COMMON_FREE = 0x0,

	XZONE_POST_GFX = 0x2,
	XZONE_POST_GFX_FREE = 0x0,

	XZONE_COMMON = 0x4,
	XZONE_COMMON_FREE = 0x0,

	XZONE_UI = 0x8,
	XZONE_UI_FREE = 0x0,
	// .. below

	XZONE_MAP = 0x8,
	XZONE_MAP_FREE = 0x8,

	XZONE_MOD = 0x10, //(0x10)
	XZONE_MOD_FREE = 0x0,

	XZONE_DEBUG = 0x40, //(0x40)
	XZONE_DEBUG_FREE = 0x40, //(0x40)

	XZONE_LOAD = 0x20, //(0x20)
	XZONE_LOAD_FREE = 0x60, //(0x60)

	XZONE_UI_FREE_INGAME = XZONE_LOAD_FREE | XZONE_UI //(0x68)
};

struct XZoneInfo
{
	const char* name;
	int allocFlags;
	int freeFlags;
};

struct dbgLinesDelaySync_t
{
	bool initialized;
	int delayInFrames;
	int delayCounter;
	bool sync;
};

struct dbgLines_t
{
	//glm::vec3 ptFrom;
	//glm::vec3 ptTo;
};

enum ServerCommandType
{
	SERVER_STRING_MSG = 0,
	SERVER_CAMERA_UPDATE = 10, // move radiant cam
	SERVER_EXPORT_SINGLE_BRUSH_FACE_INDEX = 20, // current index of face we are sending next
	SERVER_EXPORT_SINGLE_BRUSH_FACE = 21, // receive a single face
};

struct ServerCommand
{
	ServerCommandType type;
	int liveUpdateId;
	char strCommand[512];
};

enum RadiantCommandType
{
	RADIANT_COMMAND_SELECT = 0,
	RADIANT_COMMAND_DESELECT = 1,
	RADIANT_COMMAND_UPDATE_SELECTED = 2,
	RADIANT_COMMAND_UPDATE = 3,
	RADIANT_COMMAND_CREATE = 4,
	RADIANT_COMMAND_DELETE = 5,
	RADIANT_COMMAND_CAMERA = 6,
	RADIANT_COMMAND_BRUSH_SELECT = 7,		// on each new brush select / deselect
	RADIANT_COMMAND_BRUSH_COUNT = 8,		// amount of selected brushes
	RADIANT_COMMAND_BRUSH_CURRENT_NUM = 9,	// current processing brush num
	RADIANT_COMMAND_BRUSH_FACE = 10,		// parse a new face on the server
	RADIANT_COMMAND_BRUSH_FACE_COUNT = 11,	// total amount of faces per brush
	RADIANT_COMMAND_BRUSH_FACE_NORMALS = 12,// send brushface 3 & 4 to determin its angles 

	RADIANT_COMMAND_SET_DVAR = 30,
};
namespace cmdbuttons
{
	enum class Buttons
	{
		fire = 1,
		melee = 4,
		reload = 16,
		lean_left = 64,
		lean_right = 128,
		prone = 256,
		crouch = 512,
		jump = 1024,
		ads_toggle_on = 2048,
		crouch_hold = 4608,
		prone_hold = 4352,
		steady_aim = 8192,
		sprint = 8194,
		nade = 16384,
		special_grenade = 32768,
		ads_toggle_off = 524288,
		ads_hold = 526336,
		no_input = 1048576 //such as menu open or chat is open
	};

	enum class Move : char
	{
		noInput = 0,
		forward = 127,
		back = -127
	};
	enum class Strafe : char
	{
		noInput = 0,
		left = -127,
		right = 127
	};
};
struct RadiantCommand
{
	RadiantCommandType type;
	int liveUpdateId;
	char strCommand[512];
};

struct radiantFace_t
{
	vec3_t normal;
	float dist;
	int windingCount;		// amount windingPts send over remote
	vec3_t windingPts[16];	// max winding-points per face = 16
};

struct radiantBrush_t
{
	bool isSaved;
	uint32_t hash;
	int faceCount;			// amount of faces send over remote
	int nextFreeFaceIdx;	// index of the next free face (++ on each face, reset when we get an update over remote)
	radiantFace_t face[16]; // max faces per brush = 16
};

struct savedRadiantBrushes
{
	bool wasModified;
	bool brushSelected;		// true if one or more valid brushes are selected
	bool disabledCollision;
	bool resetCollision;	// flag bool to be used for first iter after "radiant_saveSelection" was called
	bool usingSaved;		// true after command "radiant_saveSelection"
	int brushSelectedCount; // amount of selected brushes
	int brushSelectedNum;	// index of current processing brush
	int brushSavedCount;
	radiantBrush_t brush[16];	// [16] max brushes? 
};

struct SpawnVar
{
	bool spawnVarsValid;
	int numSpawnVars;
	char* spawnVars[64][2];
	int numSpawnVarChars;
	char spawnVarChars[2048];
};

struct cgsAddon
{
	bool	radiantLiveConnected;
	bool	radiantCamInUse;
	bool	radiantCamSyncEnabled;
	bool	radiantCamModelSpawned;
	float	radiantCamOrigin[3];
	float	radiantCamAngles[3];
	float	radiantCamOriginOld[3];
	int		radiantCamClientTimeOld;
	int		radiantCamClientMsecPassed;
	bool	radiantCamCappedPackets;
};

struct vector2
{
	float x;
	float y;
};

struct vector3
{
	float x;
	float y;
	float z;
};

struct vector4
{
	float x;
	float y;
	float z;
	float w;
};

// fucking namespaces
union PackedUnitVec
{
	unsigned int packed;
	char array[4];
};

// fucking namespaces
union GfxColor
{
	unsigned int packed;
	char array[4];
};

// fucking namespaces
struct GfxWorldVertex
{
	float xyz[3];
	float binormalSign;
	GfxColor color;
	float texCoord[2];
	float lmapCoord[2];
	PackedUnitVec normal;
	PackedUnitVec tangent;
};

struct map_brushPlane_t
{
	vec3_t point;
};

struct map_brushSide_t
{
	int brushSideIndex;
	map_brushPlane_t brushPlane[3];
};

struct map_patchQuads_t
{
	int quadIndex;
	vec3_t coords[4];
};

struct map_patchTris_t
{
	int triIndex;
	GfxWorldVertex coords[3]; // was vec3_t
};

struct map_vec3_t
{
	float v[3];
};


enum OffhandSecondaryClass
{
	PLAYER_OFFHAND_SECONDARY_SMOKE = 0x0,
	PLAYER_OFFHAND_SECONDARY_FLASH = 0x1,
	PLAYER_OFFHAND_SECONDARIES_TOTAL = 0x2,
};

enum ViewLockTypes
{
	PLAYERVIEWLOCK_NONE = 0x0,
	PLAYERVIEWLOCK_FULL = 0x1,
	PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
	PLAYERVIEWLOCKCOUNT = 0x3,
};

enum ActionSlotType
{
	ACTIONSLOTTYPE_DONOTHING = 0x0,
	ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
	ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
	ACTIONSLOTTYPE_NIGHTVISION = 0x3,
	ACTIONSLOTTYPECOUNT = 0x4,
};

struct SprintState
{
	int sprintButtonUpRequired;
	int sprintDelay;
	int lastSprintStart;
	int lastSprintEnd;
	int sprintStartMaxLength;
};

/* 827 */
struct MantleState
{
	float yaw;
	int timer;
	int transIndex;
	int flags;
};

struct ActionSlotParam_SpecifyWeapon
{
	unsigned int index;
};

struct ActionSlotParam
{
	ActionSlotParam_SpecifyWeapon specifyWeapon;
};

enum objectiveState_t
{
	OBJST_EMPTY = 0x0,
	OBJST_ACTIVE = 0x1,
	OBJST_INVISIBLE = 0x2,
	OBJST_DONE = 0x3,
	OBJST_CURRENT = 0x4,
	OBJST_FAILED = 0x5,
	OBJST_NUMSTATES = 0x6,
};

struct objective_t
{
	objectiveState_t state;
	float origin[3];
	int entNum;
	int teamNum;
	int icon;
};

enum he_type_t
{
	HE_TYPE_FREE = 0x0,
	HE_TYPE_TEXT = 0x1,
	HE_TYPE_VALUE = 0x2,
	HE_TYPE_PLAYERNAME = 0x3,
	HE_TYPE_MAPNAME = 0x4,
	HE_TYPE_GAMETYPE = 0x5,
	HE_TYPE_MATERIAL = 0x6,
	HE_TYPE_TIMER_DOWN = 0x7,
	HE_TYPE_TIMER_UP = 0x8,
	HE_TYPE_TENTHS_TIMER_DOWN = 0x9,
	HE_TYPE_TENTHS_TIMER_UP = 0xA,
	HE_TYPE_CLOCK_DOWN = 0xB,
	HE_TYPE_CLOCK_UP = 0xC,
	HE_TYPE_WAYPOINT = 0xD,
	HE_TYPE_COUNT = 0xE,
};

struct $C96EA5EC2ACBB9C0BF22693F316ACC67
{
	char r;
	char g;
	char b;
	char a;
};

union hudelem_color_t
{
	$C96EA5EC2ACBB9C0BF22693F316ACC67 __s0;
	int rgba;
};

struct hudelem_s
{
	he_type_t type;
	float x;
	float y;
	float z;
	int targetEntNum;
	float fontScale;
	int font;
	int alignOrg;
	int alignScreen;
	hudelem_color_t color;
	hudelem_color_t fromColor;
	int fadeStartTime;
	int fadeTime;
	int label;
	int width;
	int height;
	int materialIndex;
	int offscreenMaterialIdx;
	int fromWidth;
	int fromHeight;
	int scaleStartTime;
	int scaleTime;
	float fromX;
	float fromY;
	int fromAlignOrg;
	int fromAlignScreen;
	int moveStartTime;
	int moveTime;
	int time;
	int duration;
	float value;
	int text;
	float sort;
	hudelem_color_t glowColor;
	int fxBirthTime;
	int fxLetterTime;
	int fxDecayStartTime;
	int fxDecayDuration;
	int soundID;
	int flags;
};

struct $15067B6A14D88D7E1E730369692C3A81
{
	hudelem_s current[31];
	hudelem_s archival[31];
};
// playerState_t is the information needed by both the client and server
// to predict player motion and actions
// nothing outside of pmove should modify these, or some degree of prediction error
// will occur
struct playerState_s
{
	int commandTime;
	int pm_type;
	int bobCycle;
	int pm_flags;
	int weapFlags;
	int otherFlags;
	int pm_time;
	float origin[3];
	float velocity[3];
	float oldVelocity[2];
	int weaponTime;
	int weaponDelay;
	int grenadeTimeLeft;
	int throwBackGrenadeOwner;
	int throwBackGrenadeTimeLeft;
	int weaponRestrictKickTime;
	int foliageSoundTime;
	int gravity;
	float leanf;
	int speed;
	float delta_angles[3];
	int groundEntityNum;
	float vLadderVec[3];
	int jumpTime;
	float jumpOriginZ;
	int legsTimer;
	int legsAnim;
	int torsoTimer;
	int torsoAnim;
	int legsAnimDuration;
	int torsoAnimDuration;
	int damageTimer;
	int damageDuration;
	int flinchYawAnim;
	int movementDir;
	int eFlags;
	int eventSequence;
	int events[4];
	unsigned int eventParms[4];
	int oldEventSequence;
	int clientNum;
	int offHandIndex;
	OffhandSecondaryClass offhandSecondary;
	unsigned int weapon;
	int weaponstate;
	unsigned int weaponShotCount;
	float fWeaponPosFrac;
	int adsDelayTime;
	int spreadOverride;
	int spreadOverrideState;
	int viewmodelIndex;
	float viewangles[3];
	int viewHeightTarget;
	float viewHeightCurrent;
	int viewHeightLerpTime;
	int viewHeightLerpTarget;
	int viewHeightLerpDown;
	float viewAngleClampBase[2];
	float viewAngleClampRange[2];
	int damageEvent;
	int damageYaw;
	int damagePitch;
	int damageCount;
	int stats[5];
	int ammo[128];
	int ammoclip[128];
	unsigned int weapons[4];
	unsigned int weaponold[4];
	unsigned int weaponrechamber[4];
	float proneDirection;
	float proneDirectionPitch;
	float proneTorsoPitch;
	ViewLockTypes viewlocked;
	int viewlocked_entNum;
	int cursorHint;
	int cursorHintString;
	int cursorHintEntIndex;
	int iCompassPlayerInfo;
	int radarEnabled;
	int locationSelectionInfo;
	SprintState sprintState;
	float fTorsoPitch;
	float fWaistPitch;
	float holdBreathScale;
	int holdBreathTimer;
	float moveSpeedScaleMultiplier;
	MantleState mantleState;
	float meleeChargeYaw;
	int meleeChargeDist;
	int meleeChargeTime;
	int perks;
	ActionSlotType actionSlotType[4];
	ActionSlotParam actionSlotParam[4];
	int entityEventSequence;
	int weapAnim;
	float aimSpreadScale;
	int shellshockIndex;
	int shellshockTime;
	int shellshockDuration;
	float dofNearStart;
	float dofNearEnd;
	float dofFarStart;
	float dofFarEnd;
	float dofNearBlur;
	float dofFarBlur;
	float dofViewmodelStart;
	float dofViewmodelEnd;
	int hudElemLastAssignedSoundID;
	objective_t objective[16];
	char weaponmodels[128];
	int deltaTime;
	int killCamEntity;
	$15067B6A14D88D7E1E730369692C3A81 hud;
};

struct areaParms_t
{
	const float* mins;
	const float* maxs;
	int* list;
	int count;
	int maxcount;
	int contentmask;
};
//
// usercmd_t->button bits, many of which are generated by the client system,
// so they aren't game/cgame only definitions
//
struct usercmd_s
{
	int serverTime;
	int buttons;
	int angles[3];
	char weapon;
	char offHandIndex;
	char forwardmove; //buttonsVertical |||| -127 = back | 127 = forward
	char rightmove; //buttonsHorizontal |||| -127 = left | 127 = right
	float meleeChargeYaw;
	char meleeChargeDist;
	char selectedLocation[2];
};
struct TraceExtents
{
	float start[3];
	float end[3];
	float invDelta[3];
};
struct IgnoreEntParams
{
	int baseEntity;
	int parentEntity;
	bool ignoreSelf;
	bool ignoreParent;
	bool ignoreSiblings;
	bool ignoreChildren;
};
struct pointtrace_t
{
	TraceExtents extents;
	IgnoreEntParams* ignoreEntParams;
	int contentmask;
	int bLocational;
	char* priorityMap;
};
enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
};

struct __declspec(align(4)) trace_t
{
	float fraction;
	float normal[3];
	int surfaceFlags;
	int contents;
	const char* material;
	TraceHitType hitType;
	unsigned __int16 hitId;
	unsigned __int16 modelIndex;
	unsigned __int16 partName;
	unsigned __int16 partGroup;
	bool allsolid;
	bool startsolid;
	bool walkable;
};

struct pml_t
{
	float forward[3];
	float right[3];
	float up[3];
	float frametime;
	int msec;
	int walking;
	int groundPlane;
	int almostGroundPlane;
	trace_t groundTrace;
	float impactSpeed;
	float previous_origin[3];
	float previous_velocity[3];
};
inline struct pml_t_glob
{
	float forward[3];
	float right[3];
	float up[3];
	float frametime;
	int msec;
	int walking;
	int groundPlane;
	int almostGroundPlane;
	trace_t groundTrace;
	float impactSpeed;
	float previous_origin[3];
	float previous_velocity[3];
}pml_cpy;
struct pmove_t
{
	// state (in / out)
	playerState_s* ps;
	usercmd_s cmd;
	usercmd_s oldcmd;
	int tracemask; // collide against these types of surfaces
	int numtouch;
	int touchents[32];
	float mins[3];
	float maxs[3];
	float xyspeed;
	int proneChange;
	float maxSprintTimeMultiplier;
	bool mantleStarted;
	float mantleEndPos[3];
	int mantleDuration;
	int viewChangeTime;
	float viewChange;
	char handler;
};

enum MapType
{
	MAPTYPE_NONE = 0x0,
	MAPTYPE_INVALID1 = 0x1,
	MAPTYPE_INVALID2 = 0x2,
	MAPTYPE_2D = 0x3,
	MAPTYPE_3D = 0x4,
	MAPTYPE_CUBE = 0x5,
	MAPTYPE_COUNT = 0x6,
};

struct Picmip
{
	char platform[2];
};

struct CardMemory
{
	int platform[2];
};

struct GfxImageLoadDef
{
	char levelCount;
	char flags;
	__int16 dimensions[3];
	int format;
	int resourceSize;
	char data[1];
};

union GfxTexture
{
	/*IDirect3DBaseTexture9 *basemap;
	IDirect3DTexture9 *map;
	IDirect3DVolumeTexture9 *volmap;
	IDirect3DCubeTexture9 *cubemap;*/
	GfxImageLoadDef* loadDef;
	void* data;
};

struct GfxImage
{
	MapType mapType;
	GfxTexture texture;
	Picmip picmip;
	bool noPicmip;
	char semantic;
	char track;
	CardMemory cardMemory;
	unsigned __int16 width;
	unsigned __int16 height;
	unsigned __int16 depth;
	char category;
	bool delayLoadPixels;
	const char* name;
};

enum file_image_flags_t
{
	IMG_FLAG_NOPICMIP = 0x1,
	IMG_FLAG_NOMIPMAPS = 0x2,
	IMG_FLAG_CUBEMAP = 0x4,
	IMG_FLAG_VOLMAP = 0x8,
	IMG_FLAG_STREAMING = 0x10,
	IMG_FLAG_LEGACY_NORMALS = 0x20,
	IMG_FLAG_CLAMP_U = 0x40,
	IMG_FLAG_CLAMP_V = 0x80,
	IMG_FLAG_DYNAMIC = 0x10000,
	IMG_FLAG_RENDER_TARGET = 0x20000,
	IMG_FLAG_SYSTEMMEM = 0x40000,
};

struct GfxImageFileHeader
{
	char tag[3];
	char version;
	char format;
	char flags;
	short dimensions[3];
	int fileSizeForPicmip[4];
};

struct GfxVertexShaderLoadDef
{
	unsigned int* program;
	unsigned __int16 programSize;
	unsigned __int16 loadForRenderer;
};

struct MaterialVertexShaderProgram
{
	void* vs;
	GfxVertexShaderLoadDef loadDef;
};

struct MaterialVertexShader
{
	const char* name;
	MaterialVertexShaderProgram prog;
};

class centity_t
{
public:
	char pad_0x0000[0x2]; //0x0000
	__int16 currentValid; //0x0002
	char pad_0x0004[0x18]; //0x0004
	vec3_t lerpOrigin; //0x001C
	vec3_t lerpAngles; //0x0028
	char pad_0x0034[0x40]; //0x0034
	vec3_t newOrigin; //0x0074
	char pad_0x0080[0x4C]; //0x0080
	int clientNum; //0x00CC
	DWORD eType; //0x00D0
	DWORD eFlags; //0x00D4
	char pad_0x00D8[0xC]; //0x00D8
	vec3_t oldOrigin; //0x00E4
	char pad_0x00F0[0x64]; //0x00F0
	int ItemID; //0x0154
	char pad_0x0158[0x38]; //0x0158
	int Weapon; //0x0190
	char pad_0x0194[0x2C]; //0x0194
	int isAlive; //0x01C0
	char pad_0x01C4[0x18]; //0x01C4
}; //Size=0x01DC

struct pCoordinates
{
	float x;
	float y;
	float z;
};
typedef struct
{
	vec3_t angles;
}CViewAngles;
struct GfxPixelShaderLoadDef
{
	unsigned int* program;
	unsigned __int16 programSize;
	unsigned __int16 loadForRenderer;
};

struct MaterialPixelShaderProgram
{
	void* ps;
	GfxPixelShaderLoadDef loadDef;
};

struct MaterialPixelShader
{
	const char* name;
	MaterialPixelShaderProgram prog;
};

struct MaterialConstantDef
{
	int nameHash;
	char name[12];
	vec4_t literal;
};

struct GfxStateBits
{
	unsigned int loadBits[2];
};
struct WaterWritable
{
	float floatTime;
};

struct complex_s
{
	float real;
	float imag;
};

struct water_t
{
	WaterWritable writable;
	complex_s* H0;
	float* wTerm;
	int M;
	int N;
	float Lx;
	float Lz;
	float gravity;
	float windvel;
	float winddir[2];
	float amplitude;
	float codeConstant[4];
	GfxImage* image;
};

/* MaterialTextureDef->semantic */
#define TS_2D           0x0
#define TS_FUNCTION     0x1
#define TS_COLOR_MAP    0x2
#define TS_UNUSED_1     0x3
#define TS_UNUSED_2     0x4
#define TS_NORMAL_MAP   0x5
#define TS_UNUSED_3     0x6
#define TS_UNUSED_4     0x7
#define TS_SPECULAR_MAP 0x8
#define TS_UNUSED_5     0x9
#define TS_UNUSED_6     0xA
#define TS_WATER_MAP    0xB

union MaterialTextureDefInfo
{
	GfxImage* image;	// MaterialTextureDef->semantic != TS_WATER_MAP
	water_t* water;		// MaterialTextureDef->semantic == TS_WATER_MAP
};

struct MaterialTextureDef
{
	unsigned int nameHash;
	char nameStart;
	char nameEnd;
	char samplerState;
	char semantic;
	MaterialTextureDefInfo u;
};

struct GfxDrawSurfFields
{
	unsigned __int64 objectId : 16;
	unsigned __int64 reflectionProbeIndex : 8;
	unsigned __int64 customIndex : 5;
	unsigned __int64 materialSortedIndex : 11;
	unsigned __int64 prepass : 2;
	unsigned __int64 primaryLightIndex : 8;
	unsigned __int64 surfType : 4;
	unsigned __int64 primarySortKey : 6;
	unsigned __int64 unused : 4;
};

union GfxDrawSurf
{
	GfxDrawSurfFields fields;
	unsigned long long packed;
};

struct MaterialArgumentCodeConst
{
	unsigned __int16 index;
	char firstRow;
	char rowCount;
};

union MaterialArgumentDef
{
	const float* literalConst;
	MaterialArgumentCodeConst codeConst;
	unsigned int codeSampler;
	unsigned int nameHash;
};

/* MaterialShaderArgument->type */
#define MTL_ARG_MATERIAL_VERTEX_CONST	0x0
#define MTL_ARG_LITERAL_VERTEX_CONST	0x1
#define MTL_ARG_MATERIAL_PIXEL_SAMPLER	0x2
#define MTL_ARG_CODE_VERTEX_CONST	    0x3
#define MTL_ARG_CODE_PIXEL_SAMPLER	    0x4
#define MTL_ARG_CODE_PIXEL_CONST	    0x5
#define MTL_ARG_MATERIAL_PIXEL_CONST	0x6
#define MTL_ARG_LITERAL_PIXEL_CONST	    0x7

struct MaterialShaderArgument
{
	unsigned __int16 type;
	unsigned __int16 dest;
	MaterialArgumentDef u;
};

enum ShaderCodeConstants
{
	CONST_SRC_CODE_MAYBE_DIRTY_PS_BEGIN = 0x0,
	CONST_SRC_CODE_LIGHT_POSITION = 0x0,
	CONST_SRC_CODE_LIGHT_DIFFUSE = 0x1,
	CONST_SRC_CODE_LIGHT_SPECULAR = 0x2,
	CONST_SRC_CODE_LIGHT_SPOTDIR = 0x3,
	CONST_SRC_CODE_LIGHT_SPOTFACTORS = 0x4,
	CONST_SRC_CODE_NEARPLANE_ORG = 0x5,
	CONST_SRC_CODE_NEARPLANE_DX = 0x6,
	CONST_SRC_CODE_NEARPLANE_DY = 0x7,
	CONST_SRC_CODE_SHADOW_PARMS = 0x8,
	CONST_SRC_CODE_SHADOWMAP_POLYGON_OFFSET = 0x9,
	CONST_SRC_CODE_RENDER_TARGET_SIZE = 0xA,
	CONST_SRC_CODE_LIGHT_FALLOFF_PLACEMENT = 0xB,
	CONST_SRC_CODE_DOF_EQUATION_VIEWMODEL_AND_FAR_BLUR = 0xC,
	CONST_SRC_CODE_DOF_EQUATION_SCENE = 0xD,
	CONST_SRC_CODE_DOF_LERP_SCALE = 0xE,
	CONST_SRC_CODE_DOF_LERP_BIAS = 0xF,
	CONST_SRC_CODE_DOF_ROW_DELTA = 0x10,
	CONST_SRC_CODE_PARTICLE_CLOUD_COLOR = 0x11,
	CONST_SRC_CODE_GAMETIME = 0x12,
	CONST_SRC_CODE_MAYBE_DIRTY_PS_END = 0x13,
	CONST_SRC_CODE_ALWAYS_DIRTY_PS_BEGIN = 0x13,
	CONST_SRC_CODE_PIXEL_COST_FRACS = 0x13,
	CONST_SRC_CODE_PIXEL_COST_DECODE = 0x14,
	CONST_SRC_CODE_FILTER_TAP_0 = 0x15,
	CONST_SRC_CODE_FILTER_TAP_1 = 0x16,
	CONST_SRC_CODE_FILTER_TAP_2 = 0x17,
	CONST_SRC_CODE_FILTER_TAP_3 = 0x18,
	CONST_SRC_CODE_FILTER_TAP_4 = 0x19,
	CONST_SRC_CODE_FILTER_TAP_5 = 0x1A,
	CONST_SRC_CODE_FILTER_TAP_6 = 0x1B,
	CONST_SRC_CODE_FILTER_TAP_7 = 0x1C,
	CONST_SRC_CODE_COLOR_MATRIX_R = 0x1D,
	CONST_SRC_CODE_COLOR_MATRIX_G = 0x1E,
	CONST_SRC_CODE_COLOR_MATRIX_B = 0x1F,
	CONST_SRC_CODE_ALWAYS_DIRTY_PS_END = 0x20,
	CONST_SRC_CODE_NEVER_DIRTY_PS_BEGIN = 0x20,
	CONST_SRC_CODE_SHADOWMAP_SWITCH_PARTITION = 0x20,
	CONST_SRC_CODE_SHADOWMAP_SCALE = 0x21,
	CONST_SRC_CODE_ZNEAR = 0x22,
	CONST_SRC_CODE_SUN_POSITION = 0x23,
	CONST_SRC_CODE_SUN_DIFFUSE = 0x24,
	CONST_SRC_CODE_SUN_SPECULAR = 0x25,
	CONST_SRC_CODE_LIGHTING_LOOKUP_SCALE = 0x26,
	CONST_SRC_CODE_DEBUG_BUMPMAP = 0x27,
	CONST_SRC_CODE_MATERIAL_COLOR = 0x28,
	CONST_SRC_CODE_FOG = 0x29,
	CONST_SRC_CODE_FOG_COLOR = 0x2A,
	CONST_SRC_CODE_GLOW_SETUP = 0x2B,
	CONST_SRC_CODE_GLOW_APPLY = 0x2C,
	CONST_SRC_CODE_COLOR_BIAS = 0x2D,
	CONST_SRC_CODE_COLOR_TINT_BASE = 0x2E,
	CONST_SRC_CODE_COLOR_TINT_DELTA = 0x2F,
	CONST_SRC_CODE_OUTDOOR_FEATHER_PARMS = 0x30,
	CONST_SRC_CODE_ENVMAP_PARMS = 0x31,
	CONST_SRC_CODE_SPOT_SHADOWMAP_PIXEL_ADJUST = 0x32,
	CONST_SRC_CODE_CLIP_SPACE_LOOKUP_SCALE = 0x33,
	CONST_SRC_CODE_CLIP_SPACE_LOOKUP_OFFSET = 0x34,
	CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX = 0x35,
	CONST_SRC_CODE_DEPTH_FROM_CLIP = 0x36,
	CONST_SRC_CODE_CODE_MESH_ARG_0 = 0x37,
	CONST_SRC_CODE_CODE_MESH_ARG_1 = 0x38,
	CONST_SRC_CODE_CODE_MESH_ARG_LAST = 0x38,
	CONST_SRC_CODE_BASE_LIGHTING_COORDS = 0x39,
	CONST_SRC_CODE_NEVER_DIRTY_PS_END = 0x3A,
	CONST_SRC_CODE_COUNT_FLOAT4 = 0x3A,
	CONST_SRC_FIRST_CODE_MATRIX = 0x3A,
	CONST_SRC_CODE_WORLD_MATRIX = 0x3A,
	CONST_SRC_CODE_INVERSE_WORLD_MATRIX = 0x3B,
	CONST_SRC_CODE_TRANSPOSE_WORLD_MATRIX = 0x3C,
	CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_MATRIX = 0x3D,
	CONST_SRC_CODE_VIEW_MATRIX = 0x3E,
	CONST_SRC_CODE_INVERSE_VIEW_MATRIX = 0x3F,
	CONST_SRC_CODE_TRANSPOSE_VIEW_MATRIX = 0x40,
	CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_MATRIX = 0x41,
	CONST_SRC_CODE_PROJECTION_MATRIX = 0x42,
	CONST_SRC_CODE_INVERSE_PROJECTION_MATRIX = 0x43,
	CONST_SRC_CODE_TRANSPOSE_PROJECTION_MATRIX = 0x44,
	CONST_SRC_CODE_INVERSE_TRANSPOSE_PROJECTION_MATRIX = 0x45,
	CONST_SRC_CODE_WORLD_VIEW_MATRIX = 0x46,
	CONST_SRC_CODE_INVERSE_WORLD_VIEW_MATRIX = 0x47,
	CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_MATRIX = 0x48,
	CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX = 0x49,
	CONST_SRC_CODE_VIEW_PROJECTION_MATRIX = 0x4A,
	CONST_SRC_CODE_INVERSE_VIEW_PROJECTION_MATRIX = 0x4B,
	CONST_SRC_CODE_TRANSPOSE_VIEW_PROJECTION_MATRIX = 0x4C,
	CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_PROJECTION_MATRIX = 0x4D,
	CONST_SRC_CODE_WORLD_VIEW_PROJECTION_MATRIX = 0x4E,
	CONST_SRC_CODE_INVERSE_WORLD_VIEW_PROJECTION_MATRIX = 0x4F,
	CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX = 0x50,
	CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX = 0x51,
	CONST_SRC_CODE_SHADOW_LOOKUP_MATRIX = 0x52,
	CONST_SRC_CODE_INVERSE_SHADOW_LOOKUP_MATRIX = 0x53,
	CONST_SRC_CODE_TRANSPOSE_SHADOW_LOOKUP_MATRIX = 0x54,
	CONST_SRC_CODE_INVERSE_TRANSPOSE_SHADOW_LOOKUP_MATRIX = 0x55,
	CONST_SRC_CODE_WORLD_OUTDOOR_LOOKUP_MATRIX = 0x56,
	CONST_SRC_CODE_INVERSE_WORLD_OUTDOOR_LOOKUP_MATRIX = 0x57,
	CONST_SRC_CODE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX = 0x58,
	CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX = 0x59,
	CONST_SRC_TOTAL_COUNT = 0x5A,
	CONST_SRC_NONE = 0x5B,
};

struct MaterialStreamRouting
{
	char source;
	char dest;
};

struct MaterialVertexStreamRouting
{
	MaterialStreamRouting data[16];
	void* decl[16];
};

struct MaterialVertexDeclaration
{
	char streamCount;
	bool hasOptionalSource;
	bool isLoaded;
	MaterialVertexStreamRouting routing;
};

#pragma pack(push, 4)
struct MaterialPass
{
	MaterialVertexDeclaration* vertexDecl;
	MaterialVertexShader* vertexShader;
	MaterialPixelShader* pixelShader;
	char perPrimArgCount;
	char perObjArgCount;
	char stableArgCount;
	char customSamplerFlags;
	MaterialShaderArgument* args;
};
#pragma pack(pop)

struct MaterialTechnique
{
	const char* name;
	unsigned __int16 flags;
	unsigned __int16 passCount;
	MaterialPass passArray[1];	// count = passCount
};

/* MaterialTechniqueSet->worldVertFormat */
enum MaterialWorldVertexFormat : char
{
	MTL_WORLDVERT_TEX_1_NRM_1 = 0x0,
	MTL_WORLDVERT_TEX_2_NRM_1 = 0x1,
	MTL_WORLDVERT_TEX_2_NRM_2 = 0x2,
	MTL_WORLDVERT_TEX_3_NRM_1 = 0x3,
	MTL_WORLDVERT_TEX_3_NRM_2 = 0x4,
	MTL_WORLDVERT_TEX_3_NRM_3 = 0x5,
	MTL_WORLDVERT_TEX_4_NRM_1 = 0x6,
	MTL_WORLDVERT_TEX_4_NRM_2 = 0x7,
	MTL_WORLDVERT_TEX_4_NRM_3 = 0x8,
	MTL_WORLDVERT_TEX_5_NRM_1 = 0x9,
	MTL_WORLDVERT_TEX_5_NRM_2 = 0xA,
	MTL_WORLDVERT_TEX_5_NRM_3 = 0xB,
};

/*struct MaterialTechniqueSet // org
{
	char *name;
	MaterialWorldVertexFormat worldVertFormat;
	MaterialTechnique *techniques[34];
};*/

struct MaterialTechniqueSet
{
	char* name;
	MaterialWorldVertexFormat worldVertFormat;
	bool hasBeenUploaded;
	char unused[1];
	MaterialTechniqueSet* remappedTechniqueSet;
	MaterialTechnique* techniques[34];
};

#pragma pack(push, 4)
struct MaterialInfo
{
	const char* name;
	char gameFlags;
	char sortKey;
	char textureAtlasRowCount;
	char textureAtlasColumnCount;
	GfxDrawSurf drawSurf;
	unsigned int surfaceTypeBits;
	unsigned __int16 hashIndex;
};
#pragma pack(pop)

enum MaterialTechniqueType
{
	TECHNIQUE_DEPTH_PREPASS = 0x0,
	TECHNIQUE_BUILD_FLOAT_Z = 0x1,
	TECHNIQUE_BUILD_SHADOWMAP_DEPTH = 0x2,
	TECHNIQUE_BUILD_SHADOWMAP_COLOR = 0x3,
	TECHNIQUE_UNLIT = 0x4,
	TECHNIQUE_EMISSIVE = 0x5,
	TECHNIQUE_EMISSIVE_SHADOW = 0x6,
	TECHNIQUE_LIT_BEGIN = 0x7,
	TECHNIQUE_LIT = 0x7,
	TECHNIQUE_LIT_SUN = 0x8,
	TECHNIQUE_LIT_SUN_SHADOW = 0x9,
	TECHNIQUE_LIT_SPOT = 0xA,
	TECHNIQUE_LIT_SPOT_SHADOW = 0xB,
	TECHNIQUE_LIT_OMNI = 0xC,
	TECHNIQUE_LIT_OMNI_SHADOW = 0xD,
	TECHNIQUE_LIT_INSTANCED = 0xE,
	TECHNIQUE_LIT_INSTANCED_SUN = 0xF,
	TECHNIQUE_LIT_INSTANCED_SUN_SHADOW = 0x10,
	TECHNIQUE_LIT_INSTANCED_SPOT = 0x11,
	TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW = 0x12,
	TECHNIQUE_LIT_INSTANCED_OMNI = 0x13,
	TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW = 0x14,
	TECHNIQUE_LIT_END = 0x15,
	TECHNIQUE_LIGHT_SPOT = 0x15,
	TECHNIQUE_LIGHT_OMNI = 0x16,
	TECHNIQUE_LIGHT_SPOT_SHADOW = 0x17,
	TECHNIQUE_FAKELIGHT_NORMAL = 0x18,
	TECHNIQUE_FAKELIGHT_VIEW = 0x19,
	TECHNIQUE_SUNLIGHT_PREVIEW = 0x1A,
	TECHNIQUE_CASE_TEXTURE = 0x1B,
	TECHNIQUE_WIREFRAME_SOLID = 0x1C,
	TECHNIQUE_WIREFRAME_SHADED = 0x1D,
	TECHNIQUE_SHADOWCOOKIE_CASTER = 0x1E,
	TECHNIQUE_SHADOWCOOKIE_RECEIVER = 0x1F,
	TECHNIQUE_DEBUG_BUMPMAP = 0x20,
	TECHNIQUE_DEBUG_BUMPMAP_INSTANCED = 0x21,
	//TECHNIQUE_COUNT = 0x22
};

struct infoParm_t
{
	const char* name;
	int clearSolid;
	int surfaceFlags;
	int contents;
	int toolFlags;
};

struct Material
{
	MaterialInfo info;
	char stateBitsEntry[34];
	char textureCount;
	char constantCount;
	char stateBitsCount;
	char stateFlags;
	char cameraRegion;
	MaterialTechniqueSet* techniqueSet;
	MaterialTextureDef* textureTable;
	MaterialConstantDef* constantTable;
	GfxStateBits* stateBitsTable;
};

struct cplane_s
{
	float normal[3];
	float dist;
	char type;
	char signbits;
	char pad[2];
};

#pragma pack(push, 2)
struct cbrushside_t
{
	cplane_s* plane;
	unsigned int materialNum;
	__int16 firstAdjacentSideOffset;
	char edgeCount;
};
#pragma pack(pop)

struct DObjAnimMat
{
	float quat[4];
	float trans[3];
	float transWeight;
};

struct XSurfaceVertexInfo
{
	short vertCount[4];
	unsigned short* vertsBlend;
};

struct GfxPointVertex
{
	float xyz[3];
	char color[4];
};

union PackedTexCoords
{
	unsigned int packed;
};

union float4
{
	float v[4];
	unsigned int u[4];
	PackedUnitVec unitVec[4];
};

struct __declspec(align(4)) ShowCollisionBrushPt
{
	float xyz[3];
	__int16 sideIndex[3];
};

struct winding_t
{
	int numpoints;
	float p[4][3];
};

struct GfxPackedVertex
{
	float xyz[3];
	float binormalSign;
	GfxColor color;
	PackedTexCoords texCoord;
	PackedUnitVec normal;
	PackedUnitVec tangent;
};

struct XSurfaceCollisionAabb
{
	unsigned short mins[3];
	unsigned short maxs[3];
};

struct XSurfaceCollisionNode
{
	XSurfaceCollisionAabb aabb;
	unsigned short childBeginIndex;
	unsigned short childCount;
};

struct XSurfaceCollisionLeaf
{
	unsigned short triangleBeginIndex;
};

struct XSurfaceCollisionTree
{
	float trans[3];
	float scale[3];
	unsigned int nodeCount;
	XSurfaceCollisionNode* nodes;
	unsigned int leafCount;
	XSurfaceCollisionLeaf* leafs;
};

struct XRigidVertList
{
	unsigned short boneOffset;
	unsigned short vertCount;
	unsigned short triOffset;
	unsigned short triCount;
	XSurfaceCollisionTree* collisionTree;
};

struct XSurface
{
	char tileMode;
	bool deformed;
	unsigned __int16 vertCount;
	unsigned __int16 triCount;
	char zoneHandle;
	unsigned __int16 baseTriIndex;
	unsigned __int16 baseVertIndex;
	unsigned __int16* triIndices;
	XSurfaceVertexInfo vertInfo;
	GfxPackedVertex* verts0;
	unsigned int vertListCount;
	XRigidVertList* vertList;
	int partBits[4];
};

struct BrushWrapper
{
	float mins[3];
	int contents;
	float maxs[3];
	unsigned int numsides;
	cbrushside_t* sides;
	__int16 axialMaterialNum[2][3];
	char* baseAdjacentSide;
	__int16 firstAdjacentSideOffsets[2][3];
	char edgeCount[2][3];
	int totalEdgeCount;
	cplane_s* planes;
};

struct PhysMass
{
	float centerOfMass[3];
	float momentsOfInertia[3];
	float productsOfInertia[3];
};

struct PhysGeomInfo
{
	BrushWrapper* brush;
	int type;
	float orientation[3][3];
	float offset[3];
	float halfLengths[3];
};

struct PhysGeomList
{
	unsigned int count;
	PhysGeomInfo* geoms;
	PhysMass mass;
};

struct XBoneInfo
{
	float bounds[2][3];
	float offset[3];
	float radiusSquared;
};

struct XModelHighMipBounds
{
	float mins[3];
	float maxs[3];
};

struct XModelStreamInfo
{
	XModelHighMipBounds* highMipBounds;
};

struct XModelCollTri_s
{
	float plane[4];
	float svec[4];
	float tvec[4];
};

struct XModelCollSurf_s
{
	XModelCollTri_s* collTris;
	int numCollTris;
	float mins[3];
	float maxs[3];
	int boneIdx;
	int contents;
	int surfFlags;
};

struct XModelLodInfo
{
	float dist;
	unsigned __int16 numsurfs;
	unsigned __int16 surfIndex;
	int partBits[4];
	char lod;
	char smcIndexPlusOne;
	char smcAllocBits;
	char unused;
};

#pragma pack(push, 4)
struct PhysPreset
{
	const char* name;
	int type;
	float mass;
	float bounce;
	float friction;
	float bulletForceScale;
	float explosiveForceScale;
	const char* sndAliasPrefix;
	float piecesSpreadFraction;
	float piecesUpwardVelocity;
	char tempDefaultToCylinder;
};
#pragma pack(pop)

struct XModel
{
	const char* name;
	char numBones;
	char numRootBones;
	unsigned char numsurfs;
	char lodRampType;
	unsigned __int16* boneNames;
	char* parentList;
	__int16* quats;
	float* trans;
	char* partClassification;
	DObjAnimMat* baseMat;
	XSurface* surfs;
	Material** materialHandles;
	XModelLodInfo lodInfo[4];
	XModelCollSurf_s* collSurfs;
	int numCollSurfs;
	int contents;
	XBoneInfo* boneInfo;
	float radius;
	float mins[3];
	float maxs[3];
	__int16 numLods;
	__int16 collLod;
	XModelStreamInfo streamInfo;
	int memUsage;
	char flags;
	bool bad;
	PhysPreset* physPreset;
	PhysGeomList* physGeoms;
};
struct __declspec(align(4)) GfxModelSurfaceInfo
{
	DObjAnimMat* baseMat;
	char boneIndex;
	char boneCount;
	unsigned __int16 gfxEntIndex;
	unsigned __int16 lightingHandle;
};
union $178D1D161B34F636C03EBC0CA3007D75
{
	GfxPackedVertex* skinnedVert;
	int oldSkinnedCachedOffset;
};
struct GfxModelSkinnedSurface
{
	int skinnedCachedOffset;
	XSurface* xsurf;
	GfxModelSurfaceInfo info;
	$178D1D161B34F636C03EBC0CA3007D75 ___u3;
};

union XAnimIndices
{
	char* _1;
	unsigned __int16* _2;
	void* data;
};

union XAnimDynamicFrames
{
	char(*_1)[3];
	unsigned __int16(*_2)[3];
};

union XAnimDynamicIndices
{
	char _1[1];
	unsigned __int16 _2[1];
};

#pragma pack(push, 4)
struct XAnimPartTransFrames
{
	float mins[3];
	float size[3];
	XAnimDynamicFrames frames;
	XAnimDynamicIndices indices;
};

union XAnimPartTransData
{
	XAnimPartTransFrames frames;
	float frame0[3];
};

struct XAnimPartTrans
{
	unsigned __int16 size;
	char smallTrans;
	__declspec(align(2)) XAnimPartTransData u;
};

struct XAnimDeltaPartQuatDataFrames
{
	__int16(*frames)[2];
	XAnimDynamicIndices indices;
};

union XAnimDeltaPartQuatData
{
	XAnimDeltaPartQuatDataFrames frames;
	__int16 frame0[2];
};

struct XAnimDeltaPartQuat
{
	unsigned __int16 size;
	__declspec(align(4)) XAnimDeltaPartQuatData u;
};

struct XAnimDeltaPart
{
	XAnimPartTrans* trans;
	XAnimDeltaPartQuat* quat;
};

struct XAnimNotifyInfo
{
	ScriptString name;
	float time;
};

#ifdef __cplusplus
enum XAnimPartType
{
	PART_TYPE_NO_QUAT = 0x0,
	PART_TYPE_SIMPLE_QUAT = 0x1,
	PART_TYPE_NORMAL_QUAT = 0x2,
	PART_TYPE_PRECISION_QUAT = 0x3,
	PART_TYPE_SIMPLE_QUAT_NO_SIZE = 0x4,
	PART_TYPE_NORMAL_QUAT_NO_SIZE = 0x5,
	PART_TYPE_PRECISION_QUAT_NO_SIZE = 0x6,
	PART_TYPE_SMALL_TRANS = 0x7,
	PART_TYPE_TRANS = 0x8,
	PART_TYPE_TRANS_NO_SIZE = 0x9,
	PART_TYPE_NO_TRANS = 0xA,
	PART_TYPE_ALL = 0xB,
	PART_TYPE_COUNT = 0xC,
};
#endif

#pragma pack(pop)

struct XAnimParts
{
	const char* name;
	unsigned __int16 dataByteCount;
	unsigned __int16 dataShortCount;
	unsigned __int16 dataIntCount;
	unsigned __int16 randomDataByteCount;
	unsigned __int16 randomDataIntCount;
	unsigned __int16 numframes;
	char bLoop;
	char bDelta;
	char boneCount[12];
	char notifyCount;
	char assetType;
	unsigned int randomDataShortCount;
	unsigned int indexCount;
	float framerate;
	float frequency;
	ScriptString* names;
	char* dataByte;
	__int16* dataShort;
	int* dataInt;
	__int16* randomDataShort;
	char* randomDataByte;
	int* randomDataInt;
	XAnimIndices indices;
	XAnimNotifyInfo* notify;
	XAnimDeltaPart* deltaPart;
};

struct GfxStreamingAabbTree
{
	unsigned __int16 firstItem;
	unsigned __int16 itemCount;
	unsigned __int16 firstChild;
	unsigned __int16 childCount;
	float mins[3];
	float maxs[3];
};

struct GfxWorldStreamInfo
{
	int aabbTreeCount;
	// 			GfxStreamingAabbTree *aabbTrees;
	// 			int leafRefCount;
	// 			int *leafRefs;
};

struct GfxWorldVertexData
{
	GfxWorldVertex* vertices;
	void/*IDirect3DVertexBuffer9*/* worldVb;
};

struct GfxWorldVertexLayerData
{
	char* data;
	void/*IDirect3DVertexBuffer9*/* layerVb;
};

struct SunLightParseParams
{
	char name[64];
	float ambientScale;
	float ambientColor[3];
	float diffuseFraction;
	float sunLight;
	float sunColor[3];
	float diffuseColor[3];
	char diffuseColorHasBeenSet;
	float angles[3];
};

struct __declspec(align(4)) GfxLightImage
{
	GfxImage* image;
	char samplerState;
};

struct GfxLightDef
{
	const char* name;
	GfxLightImage attenuation;
	int lmapLookupStart;
};

struct GfxLight
{
	char type;
	char canUseShadowMap;
	char unused[2];
	float color[3];
	float dir[3];
	float origin[3];
	float radius;
	float cosHalfFovOuter;
	float cosHalfFovInner;
	int exponent;
	unsigned int spotShadowIndex;
	GfxLightDef* def;
};

struct GfxReflectionProbe
{
	float origin[3];
	GfxImage* reflectionImage;
};

struct GfxWorldDpvsPlanes
{
	int cellCount;
	cplane_s* planes;
	unsigned __int16* nodes;
	unsigned int* sceneEntCellBits;
};

struct GfxAabbTree
{
	float mins[3];
	float maxs[3];
	unsigned __int16 childCount;
	unsigned __int16 surfaceCount;
	unsigned __int16 startSurfIndex;
	unsigned __int16 surfaceCountNoDecal;
	unsigned __int16 startSurfIndexNoDecal;
	unsigned __int16 smodelIndexCount;
	unsigned __int16* smodelIndexes;
	int childrenOffset;
};

struct GfxPortal;

struct GfxPortalWritable
{
	char isQueued;
	char isAncestor;
	char recursionDepth;
	char hullPointCount;
	float(*hullPoints)[2];
	GfxPortal* queuedParent;
};

struct DpvsPlane
{
	float coeffs[4];
	char side[3];
	char pad;
};

struct GfxCell;

struct GfxPortal
{
	GfxPortalWritable writable;
	DpvsPlane plane;
	GfxCell* cell;
	float(*vertices)[3];
	char vertexCount;
	float hullAxis[2][3];
};

struct GfxCell
{
	float mins[3];
	float maxs[3];
	int aabbTreeCount;
	GfxAabbTree* aabbTree;
	int portalCount;
	GfxPortal* portals;
	int cullGroupCount;
	int* cullGroups;
	char reflectionProbeCount;
	char* reflectionProbes;
};

struct GfxLightmapArray
{
	GfxImage* primary;
	GfxImage* secondary;
};

struct GfxLightGridEntry
{
	unsigned __int16 colorsIndex;
	char primaryLightIndex;
	char needsTrace;
};

struct GfxLightGridColors
{
	char rgb[56][3];
};

struct GfxLightGrid
{
	char hasLightRegions;
	unsigned int sunPrimaryLightIndex;
	unsigned __int16 mins[3];
	unsigned __int16 maxs[3];
	unsigned int rowAxis;
	unsigned int colAxis;
	unsigned __int16* rowDataStart;
	unsigned int rawRowDataSize;
	char* rawRowData;
	unsigned int entryCount;
	GfxLightGridEntry* entries;
	unsigned int colorCount;
	GfxLightGridColors* colors;
};

struct GfxBrushModelWritable
{
	float mins[3];
	float maxs[3];
};

struct __declspec(align(4)) GfxBrushModel
{
	GfxBrushModelWritable writable;
	float bounds[2][3];
	unsigned __int16 surfaceCount;
	unsigned __int16 startSurfIndex;
	unsigned __int16 surfaceCountNoDecal;
};

struct MaterialMemory
{
	Material* material;
	int memory;
};

struct Glyph
{
	unsigned __int16 letter;
	char x0;
	char y0;
	char dx;
	char pixelWidth;
	char pixelHeight;
	float s0;
	float t0;
	float s1;
	float t1;
};

struct Font_s
{
	const char* fontName;
	int pixelHeight;
	int glyphCount;
	Material* material;
	Material* glowMaterial;
	Glyph* glyphs;
};

enum DemoType
{
	DEMO_TYPE_NONE = 0x0,
	DEMO_TYPE_CLIENT = 0x1,
	DEMO_TYPE_SERVER = 0x2,
};

enum CubemapShot
{
	CUBEMAPSHOT_NONE = 0x0,
	CUBEMAPSHOT_RIGHT = 0x1,
	CUBEMAPSHOT_LEFT = 0x2,
	CUBEMAPSHOT_BACK = 0x3,
	CUBEMAPSHOT_FRONT = 0x4,
	CUBEMAPSHOT_UP = 0x5,
	CUBEMAPSHOT_DOWN = 0x6,
	CUBEMAPSHOT_COUNT = 0x7,
};

enum trType_t
{
	TR_STATIONARY = 0x0,
	TR_INTERPOLATE = 0x1,
	TR_LINEAR = 0x2,
	TR_LINEAR_STOP = 0x3,
	TR_SINE = 0x4,
	TR_GRAVITY = 0x5,
	TR_ACCELERATE = 0x6,
	TR_DECELERATE = 0x7,
	TR_PHYSICS = 0x8,
	TR_FIRST_RAGDOLL = 0x9,
	TR_RAGDOLL = 0x9,
	TR_RAGDOLL_GRAVITY = 0xA,
	TR_RAGDOLL_INTERPOLATE = 0xB,
	TR_LAST_RAGDOLL = 0xB,
};

struct trajectory_t
{
	trType_t trType;
	int trTime;
	int trDuration;
	float trBase[3];
	float trDelta[3];
};

struct LerpEntityStateEarthquake
{
	float scale;
	float radius;
	int duration;
};

struct LerpEntityStateLoopFx
{
	float cullDist;
	int period;
};

/* 807 */
struct LerpEntityStateCustomExplode
{
	int startTime;
};

/* 808 */
struct LerpEntityStateTurret
{
	float gunAngles[3];
};

/* 813 */
struct LerpEntityStateExplosion
{
	float innerRadius;
	float magnitude;
};

/* 814 */
struct LerpEntityStateBulletHit
{
	float start[3];
};

/* 815 */
struct LerpEntityStatePrimaryLight
{
	char colorAndExp[4];
	float intensity;
	float radius;
	float cosHalfFovOuter;
	float cosHalfFovInner;
};

struct LerpEntityStatePlayer
{
	float leanf;
	int movementDir;
};

struct LerpEntityStateVehicle
{
	float bodyPitch;
	float bodyRoll;
	float steerYaw;
	int materialTime;
	float gunPitch;
	float gunYaw;
	int teamAndOwnerIndex;
};

struct LerpEntityStateMissile
{
	int launchTime;
};

/* 818 */
struct LerpEntityStateSoundBlend
{
	float lerp;
};

struct LerpEntityStateExplosionJolt
{
	float innerRadius;
	float impulse[3];
};

struct LerpEntityStatePhysicsJitter
{
	float innerRadius;
	float minDisplacement;
	float maxDisplacement;
};

struct LerpEntityStateAnonymous
{
	int data[7];
};

union LerpEntityStateTypeUnion
{
	LerpEntityStateTurret turret;
	LerpEntityStateLoopFx loopFx;
	LerpEntityStatePrimaryLight primaryLight;
	LerpEntityStatePlayer player;
	LerpEntityStateVehicle vehicle;
	LerpEntityStateMissile missile;
	LerpEntityStateSoundBlend soundBlend;
	LerpEntityStateBulletHit bulletHit;
	LerpEntityStateEarthquake earthquake;
	LerpEntityStateCustomExplode customExplode;
	LerpEntityStateExplosion explosion;
	LerpEntityStateExplosionJolt explosionJolt;
	LerpEntityStatePhysicsJitter physicsJitter;
	LerpEntityStateAnonymous anonymous;
};

struct LerpEntityState
{
	int eFlags;
	trajectory_t pos;// for calculating position
	trajectory_t apos;// for calculating angles
	LerpEntityStateTypeUnion u;
};

// entityState_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way
// Different eTypes may use the information in different ways
// The messages are delta compressed, so it doesn't really matter if
// the structure size is fairly large
struct entityState_s
{
	int number;// entity index
	int eType;// entityType_t
	LerpEntityState lerp;
	int time2;
	int otherEntityNum; // shotgun sources, etc
	int attackerEntityNum;
	int groundEntityNum; // -1 = in air
	int loopSound; // constantly loop this sound
	int surfType;
	int index;
	int clientNum; // 0 to (MAX_CLIENTS - 1), for players and corpses
	int iHeadIcon;
	int iHeadIconTeam;
	int solid; // for client side prediction, trap_linkentity sets this properly
	unsigned int eventParm;
	int eventSequence;
	int events[4]; // impulse events -- muzzle flashes, footsteps, etc
	int eventParms[4];
	int weapon; // determines weapon and flash model, etc
	int weaponModel;
	int legsAnim; // mask off ANIM_TOGGLEBIT
	int torsoAnim; // mask off ANIM_TOGGLEBIT
	int indexUnion1;
	int indexUnion2;
	float fTorsoPitch;
	float fWaistPitch;
	unsigned int partBits[4];
};

enum team_t
{
	TEAM_FREE = 0x0,
	TEAM_AXIS = 0x1,
	TEAM_ALLIES = 0x2,
	TEAM_SPECTATOR = 0x3,
	TEAM_NUM_TEAMS = 0x4,
};

struct clientState_s
{
	int clientIndex;
	team_t team;
	int modelindex;
	int attachModelIndex[6];
	int attachTagIndex[6];
	char name[16]; //stolen by cod4x (DO NOT USE)
	float maxSprintTimeMultiplier;
	int rank;
	int prestige;
	int perks;
	int attachedVehEntNum;
	int attachedVehSlotIndex;
};

struct snapshot_s
{
	int snapFlags;
	int ping;
	int serverTime;
	playerState_s ps;
	int numEntities;
	int numClients;
	entityState_s entities[512];
	clientState_s clients[64];
	int serverCommandSequence;
};

struct RGBA_COLOR
{
	float r, g, b, a;
};

struct sunflare_t
{
	char hasValidData;
	Material* spriteMaterial;
	Material* flareMaterial;
	float spriteSize;
	float flareMinSize;
	float flareMinDot;
	float flareMaxSize;
	float flareMaxDot;
	float flareMaxAlpha;
	int flareFadeInTime;
	int flareFadeOutTime;
	float blindMinDot;
	float blindMaxDot;
	float blindMaxDarken;
	int blindFadeInTime;
	int blindFadeOutTime;
	float glareMinDot;
	float glareMaxDot;
	float glareMaxLighten;
	int glareFadeInTime;
	int glareFadeOutTime;
	float sunFxPosition[3];
};

struct XModelDrawInfo
{
	unsigned __int16 lod;
	unsigned __int16 surfId;
};

struct GfxSceneDynModel
{
	XModelDrawInfo info;
	unsigned __int16 dynEntId;
};

struct BModelDrawInfo
{
	unsigned __int16 surfId;
};

struct GfxSceneDynBrush
{
	BModelDrawInfo info;
	unsigned __int16 dynEntId;
};

struct GfxShadowGeometry
{
	unsigned __int16 surfaceCount;
	unsigned __int16 smodelCount;
	unsigned __int16* sortedSurfIndex;
	unsigned __int16* smodelIndex;
};

struct GfxLightRegionAxis
{
	float dir[3];
	float midPoint;
	float halfSize;
};

struct GfxLightRegionHull
{
	float kdopMidPoint[9];
	float kdopHalfSize[9];
	unsigned int axisCount;
	GfxLightRegionAxis* axis;
};

struct GfxLightRegion
{
	unsigned int hullCount;
	GfxLightRegionHull* hulls;
};

struct GfxStaticModelInst
{
	float mins[3];
	float maxs[3];
	GfxColor groundLighting;
};

struct srfTriangles_t
{
	int vertexLayerData;
	int firstVertex;
	unsigned __int16 vertexCount;
	unsigned __int16 triCount;
	int baseIndex;
};

struct GfxSurface
{
	srfTriangles_t tris;
	Material* material;
	char lightmapIndex;
	char reflectionProbeIndex;
	char primaryLightIndex;
	char flags;
	float bounds[2][3];
};

struct GfxCullGroup
{
	float mins[3];
	float maxs[3];
	int surfaceCount;
	int startSurfIndex;
};

struct GfxPackedPlacement
{
	float origin[3];
	vec3_t axis[3];
	float scale;
};

struct __declspec(align(4)) GfxStaticModelDrawInst
{
	float cullDist;
	GfxPackedPlacement placement;
	XModel* model;
	unsigned __int16 smodelCacheIndex[4];
	char reflectionProbeIndex;
	char primaryLightIndex;
	unsigned __int16 lightingHandle;
	char flags;
};

struct GfxWorldDpvsStatic
{
	unsigned int smodelCount;
	unsigned int staticSurfaceCount;
	unsigned int staticSurfaceCountNoDecal;
	unsigned int litSurfsBegin;
	unsigned int litSurfsEnd;
	unsigned int decalSurfsBegin;
	unsigned int decalSurfsEnd;
	unsigned int emissiveSurfsBegin;
	unsigned int emissiveSurfsEnd;
	unsigned int smodelVisDataCount;
	unsigned int surfaceVisDataCount;
	char* smodelVisData[3];
	char* surfaceVisData[3];
	unsigned int* lodData;
	unsigned __int16* sortedSurfIndex;
	GfxStaticModelInst* smodelInsts;
	GfxSurface* surfaces;
	GfxCullGroup* cullGroups;
	GfxStaticModelDrawInst* smodelDrawInsts;
	GfxDrawSurf* surfaceMaterials;
	unsigned int* surfaceCastsSunShadow;
	volatile int usageCount;
};

struct GfxWorldDpvsDynamic
{
	unsigned int dynEntClientWordCount[2];
	unsigned int dynEntClientCount[2];
	unsigned int* dynEntCellBits[2];
	char* dynEntVisData[2][3];
};

struct GfxWorld
{
	const char* name;
	const char* baseName;
	int planeCount;
	int nodeCount;
	int indexCount;
	unsigned __int16* indices;
	int surfaceCount;
	GfxWorldStreamInfo streamInfo;
	int skySurfCount;
	int* skyStartSurfs;
	GfxImage* skyImage;
	char skySamplerState;
	unsigned int vertexCount;
	GfxWorldVertexData vd;
	unsigned int vertexLayerDataSize;
	GfxWorldVertexLayerData vld;
	SunLightParseParams sunParse;
	GfxLight* sunLight;
	float sunColorFromBsp[3];
	unsigned int sunPrimaryLightIndex;
	unsigned int primaryLightCount;
	int cullGroupCount;
	unsigned int reflectionProbeCount;
	GfxReflectionProbe* reflectionProbes;
	GfxTexture* reflectionProbeTextures;
	GfxWorldDpvsPlanes dpvsPlanes;
	int cellBitsCount;
	GfxCell* cells;
	int lightmapCount;
	GfxLightmapArray* lightmaps;
	GfxLightGrid lightGrid;
	GfxTexture* lightmapPrimaryTextures;
	GfxTexture* lightmapSecondaryTextures;
	int modelCount;
	GfxBrushModel* models;
	float mins[3];
	float maxs[3];
	unsigned int checksum;
	int materialMemoryCount;
	MaterialMemory* materialMemory;
	sunflare_t sun;
	float outdoorLookupMatrix[4][4];
	GfxImage* outdoorImage;
	unsigned int* cellCasterBits;
	GfxSceneDynModel* sceneDynModel;
	GfxSceneDynBrush* sceneDynBrush;
	unsigned int* primaryLightEntityShadowVis;
	unsigned int* primaryLightDynEntShadowVis[2];
	char* nonSunPrimaryLightForModelDynEnt;
	GfxShadowGeometry* shadowGeom;
	GfxLightRegion* lightRegion;
	GfxWorldDpvsStatic dpvs;
	GfxWorldDpvsDynamic dpvsDyn;
};

struct cStaticModelWritable
{
	unsigned __int16 nextModelInWorldSector;
};

struct cStaticModel_s
{
	cStaticModelWritable writable;
	XModel* xmodel;
	float origin[3];
	float invScaledAxis[3][3];
	float absmin[3];
	float absmax[3];
};

struct dmaterial_t
{
	char material[64];
	int surfaceFlags;
	int contentFlags;
};

struct cNode_t
{
	cplane_s* plane;
	__int16 children[2];
};

#pragma pack(push, 4)
struct cLeaf_t
{
	unsigned __int16 firstCollAabbIndex;
	unsigned __int16 collAabbCount;
	int brushContents;
	int terrainContents;
	float mins[3];
	float maxs[3];
	int leafBrushNode;
	__int16 cluster;
};
#pragma pack(pop)

struct cLeafBrushNodeLeaf_t
{
	unsigned __int16* brushes;
};

struct cLeafBrushNodeChildren_t
{
	float dist;
	float range;
	unsigned __int16 childOffset[2];
};

union cLeafBrushNodeData_t
{
	cLeafBrushNodeLeaf_t leaf;
	cLeafBrushNodeChildren_t children;
};

struct cLeafBrushNode_s
{
	char axis;
	__int16 leafBrushCount;
	int contents;
	cLeafBrushNodeData_t data;
};

struct CollisionBorder
{
	float distEq[3];
	float zBase;
	float zSlope;
	float start;
	float length;
};

struct CollisionPartition
{
	char triCount;
	char borderCount;
	int firstTri;
	CollisionBorder* borders;
};

union CollisionAabbTreeIndex
{
	int firstChildIndex;
	int partitionIndex;
};

struct CollisionAabbTree
{
	float origin[3];
	float halfSize[3];
	unsigned __int16 materialIndex;
	unsigned __int16 childCount;
	CollisionAabbTreeIndex u;
};

/* 860 */
struct cmodel_t
{
	float mins[3];
	float maxs[3];
	float radius;
	cLeaf_t leaf;
};

//		/* 861 */
//#pragma pack(push, 16)
//		struct cbrush_t
//		{
//			float mins[3];
//			int contents;
//			float maxs[3];
//			unsigned int numsides;
//			cbrushside_t *sides;
//			__int16 axialMaterialNum[2][3];
//			char *baseAdjacentSide;
//			__int16 firstAdjacentSideOffsets[2][3];
//			char edgeCount[2][3];
//			char pad[8];
//		};
//#pragma pack(pop)

				/* 861 */
#pragma pack(push, 16)
struct cbrush_t
{
	float mins[3];
	int contents;
	float maxs[3];
	unsigned int numsides;
	cbrushside_t* sides;
	__int16 axialMaterialNum[2][3];
	char* baseAdjacentSide;
	__int16 firstAdjacentSideOffsets[2][3];
	char edgeCount[2][3];
	__int16 colorCounter;
	__int16 cmBrushIndex;
	//float distFromCam;
	__int16 cmSubmodelIndex;
	bool isSubmodel;
	bool pad;
};
#pragma pack(pop)
//
//		/* 861 */
//#pragma pack(push, 16)
//		struct cbrush_collision_t
//		{
//			float mins[3];
//			int contents;
//			float maxs[3];
//			unsigned int numsides;
//			cbrushside_t *sides;
//			__int16 axialMaterialNum[2][3];
//			char *baseAdjacentSide;
//			__int16 firstAdjacentSideOffsets[2][3];
//			char edgeCount[2][3];
//			int colorCounter;
//			char pad[4];
//		};
//#pragma pack(pop)

struct Bounds
{
	vec3_t midPoint;
	vec3_t halfSize;
};

struct TriggerModel
{
	int contents;
	unsigned __int16 hullCount;
	unsigned __int16 firstHull;
};

/* 2376 */
struct TriggerHull
{
	Bounds bounds;
	int contents;
	unsigned __int16 slabCount;
	unsigned __int16 firstSlab;
};

/* 2377 */
struct TriggerSlab
{
	float dir[3];
	float midPoint;
	float halfSize;
};

/* 2378 */
struct MapTriggers
{
	unsigned int count;
	TriggerModel* models;
	unsigned int hullCount;
	TriggerHull* hulls;
	unsigned int slabCount;
	TriggerSlab* slabs;
};

struct MapEnts
{
	const char* name;
	char* entityString;
	int numEntityChars;
	MapTriggers trigger;
	// this goes on for a while but we don't need any of it
};

struct GfxPlacement
{
	float quat[4];
	float origin[3];
};

struct FxEffectDef_Placeholder
{
	const char* name;
};

struct DynEntityDef
{
	int type;
	GfxPlacement pose;
	XModel* xModel;
	unsigned __int16 brushModel;
	unsigned __int16 physicsBrushModel;
	FxEffectDef_Placeholder* destroyFx;
	/*XModelPieces*/ void* destroyPieces;
	PhysPreset* physPreset;
	int health;
	PhysMass mass;
	int contents;
};

struct clipMap_t
{
	const char* name;
	int isInUse;
	int planeCount;
	cplane_s* planes;
	unsigned int numStaticModels;
	cStaticModel_s* staticModelList;
	unsigned int numMaterials;
	dmaterial_t* materials;
	unsigned int numBrushSides;
	cbrushside_t* brushsides;
	unsigned int numBrushEdges;
	char* brushEdges;
	unsigned int numNodes;
	cNode_t* nodes;
	unsigned int numLeafs;
	cLeaf_t* leafs;
	unsigned int leafbrushNodesCount;
	cLeafBrushNode_s* leafbrushNodes;
	unsigned int numLeafBrushes;
	unsigned __int16* leafbrushes;
	unsigned int numLeafSurfaces;
	unsigned int* leafsurfaces;
	unsigned int vertCount;
	float(*verts)[3];
	int triCount;
	unsigned __int16* triIndices;
	char* triEdgeIsWalkable;
	int borderCount;
	CollisionBorder* borders;
	int partitionCount;
	CollisionPartition* partitions;
	int aabbTreeCount;
	CollisionAabbTree* aabbTrees;
	unsigned int numSubModels;
	cmodel_t* cmodels;
	unsigned __int16 numBrushes;
	cbrush_t* brushes;
	int numClusters;
	int clusterBytes;
	char* visibility;
	int vised;
	MapEnts* mapEnts;
	cbrush_t* box_brush;
	cmodel_t box_model;
	unsigned __int16 dynEntCount[2];
	DynEntityDef* dynEntDefList[2];
	/*DynEntityPose*/ void* dynEntPoseList[2];
	/*DynEntityClient*/ void* dynEntClientList[2];
	/*DynEntityColl*/ void* dynEntCollList[2];
	unsigned int checksum;
};

struct RawFile
{
	const char* name;
	int len;
	const char* buffer;
};

struct ComPrimaryLight
{
	char type;
	char canUseShadowMap;
	char exponent;
	char unused;
	float color[3];
	float dir[3];
	float origin[3];
	float radius;
	float cosHalfFovOuter;
	float cosHalfFovInner;
	float cosHalfFovExpanded;
	float rotationLimit;
	float translationLimit;
	const char* defName;
};

struct ComWorld
{
	const char* name;
	int isInUse;
	unsigned int primaryLightCount;
	ComPrimaryLight* primaryLights;
};

struct FxSpawnDefLooping
{
	int intervalMsec;
	int count;
};

struct FxIntRange
{
	int base;
	int amplitude;
};

struct FxSpawnDefOneShot
{
	FxIntRange count;
};

union FxSpawnDef
{
	FxSpawnDefLooping looping;
	FxSpawnDefOneShot oneShot;
};

struct FxFloatRange
{
	float base;
	float amplitude;
};

struct FxElemAtlas
{
	char behavior;
	char index;
	char fps;
	char loopCount;
	char colIndexBits;
	char rowIndexBits;
	__int16 entryCount;
};

struct FxElemVec3Range
{
	float base[3];
	float amplitude[3];
};

struct FxElemVelStateInFrame
{
	FxElemVec3Range velocity;
	FxElemVec3Range totalDelta;
};

const struct FxElemVelStateSample
{
	FxElemVelStateInFrame local;
	FxElemVelStateInFrame world;
};

struct FxElemVisualState
{
	char color[4];
	float rotationDelta;
	float rotationTotal;
	float size[2];
	float scale;
};

const struct FxElemVisStateSample
{
	FxElemVisualState base;
	FxElemVisualState amplitude;
};

struct FxEffectDef;

union FxEffectDefRef
{
	FxEffectDef* handle;
	const char* name;
};

union FxElemVisuals
{
	const void* anonymous;
	Material* material;
	XModel* model;
	FxEffectDefRef effectDef;
	const char* soundName;
};

struct FxElemMarkVisuals
{
	Material* materials[2];
};

union FxElemDefVisuals
{
	FxElemMarkVisuals* markArray;
	FxElemVisuals* array;
	FxElemVisuals instance;
};

struct FxTrailVertex
{
	float pos[2];
	float normal[2];
	float texCoord;
};

struct FxTrailDef
{
	int scrollTimeMsec;
	int repeatDist;
	int splitDist;
	int vertCount;
	FxTrailVertex* verts;
	int indCount;
	unsigned __int16* inds;
};

const struct FxElemDef
{
	int flags;
	FxSpawnDef spawn;
	FxFloatRange spawnRange;
	FxFloatRange fadeInRange;
	FxFloatRange fadeOutRange;
	float spawnFrustumCullRadius;
	FxIntRange spawnDelayMsec;
	FxIntRange lifeSpanMsec;
	FxFloatRange spawnOrigin[3];
	FxFloatRange spawnOffsetRadius;
	FxFloatRange spawnOffsetHeight;
	FxFloatRange spawnAngles[3];
	FxFloatRange angularVelocity[3];
	FxFloatRange initialRotation;
	FxFloatRange gravity;
	FxFloatRange reflectionFactor;
	FxElemAtlas atlas;
	char elemType;
	char visualCount;
	char velIntervalCount;
	char visStateIntervalCount;
	FxElemVelStateSample* velSamples;
	FxElemVisStateSample* visSamples;
	FxElemDefVisuals visuals;
	float collMins[3];
	float collMaxs[3];
	FxEffectDefRef effectOnImpact;
	FxEffectDefRef effectOnDeath;
	FxEffectDefRef effectEmitted;
	FxFloatRange emitDist;
	FxFloatRange emitDistVariance;
	FxTrailDef* trailDef;
	char sortOrder;
	char lightingFrac;
	char useItemClip;
	char unused[1];
};

struct FxEffectDef
{
	const char* name;
	int flags;
	int totalSize;
	int msecLoopingLife;
	int elemDefCountLooping;
	int elemDefCountOneShot;
	int elemDefCountEmission;
	FxElemDef* elemDefs;
};

enum FxElemType : char
{
	FX_ELEM_TYPE_SPRITE_BILLBOARD = 0x0,
	FX_ELEM_TYPE_SPRITE_ORIENTED = 0x1,
	FX_ELEM_TYPE_TAIL = 0x2,
	FX_ELEM_TYPE_TRAIL = 0x3,
	FX_ELEM_TYPE_CLOUD = 0x4,
	FX_ELEM_TYPE_MODEL = 0x5,
	FX_ELEM_TYPE_OMNI_LIGHT = 0x6,
	FX_ELEM_TYPE_SPOT_LIGHT = 0x7,
	FX_ELEM_TYPE_SOUND = 0x8,
	FX_ELEM_TYPE_DECAL = 0x9,
	FX_ELEM_TYPE_RUNNER = 0xA,
	FX_ELEM_TYPE_COUNT = 0xB,
	FX_ELEM_TYPE_LAST_SPRITE = 0x3,
	FX_ELEM_TYPE_LAST_DRAWN = 0x7,
};

union XAssetHeader
{
	void* data;
	// 			XModelPieces *xmodelPieces;
	PhysPreset* physPreset;
	XAnimParts* parts;
	XModel* model;
	Material* material;
	// 			MaterialPixelShader *pixelShader;
	// 			MaterialVertexShader *vertexShader;
	MaterialTechniqueSet* techniqueSet;
	GfxImage* image;
	// 			snd_alias_list_t *sound;
	// 			SndCurve *sndCurve;
	clipMap_t* clipMap;
	ComWorld* comWorld;
	// 			GameWorldSp *gameWorldSp;
	// 			GameWorldMp *gameWorldMp;
	MapEnts* mapEnts;
	GfxWorld* gfxWorld;
	GfxLightDef* lightDef;
	// 			Font_s *font;
	// 			MenuList *menuList;
	// 			menuDef_t *menu;
	// 			LocalizeEntry *localize;
	// 			WeaponDef *weapon;
	// 			SndDriverGlobals *sndDriverGlobals;
	FxEffectDef* fx;
	// 			FxImpactTable *impactFx;
	RawFile* rawfile;
	// 			StringTable *stringTable;
};

struct XAsset
{
	XAssetType type;
	XAssetHeader header;
};

struct XAssetEntry
{
	XAsset asset;
	char zoneIndex;
	char inuse;
	unsigned __int16 nextHash;
	unsigned __int16 nextOverride;
	unsigned __int16 usageFrame;
};

struct XBlock
{
	char* data;
	unsigned int size;
};


struct XZoneMemory
{
	XBlock blocks[9];
	char* lockedVertexData;
	char* lockedIndexData;
	void* vertexBuffer;
	void* indexBuffer;
};

struct XZone
{
	char name[64];
	int flags;
	int allocType;
	XZoneMemory mem;
	int fileSize;
	char modZone;
};

struct gentity_s;

struct EntHandle
{
	unsigned __int16 number;
	unsigned __int16 infoIndex;
};

struct entityShared_t
{
	char linked;
	char bmodel;
	char svFlags;
	int clientMask[2];
	char inuse;
	int broadcastTime;
	float mins[3];
	float maxs[3];
	int contents;
	float absmin[3];
	float absmax[3];
	float currentOrigin[3];
	float currentAngles[3];
	EntHandle ownerNum;
	int eventTime;
};

enum sessionState_t
{
	SESS_STATE_PLAYING = 0x0,
	SESS_STATE_DEAD = 0x1,
	SESS_STATE_SPECTATOR = 0x2,
	SESS_STATE_INTERMISSION = 0x3,
};

enum clientConnected_t
{
	CON_DISCONNECTED = 0x0,
	CON_CONNECTING = 0x1,
	CON_CONNECTED = 0x2,
};

struct playerTeamState_t
{
	int location;
};

enum weapType_t
{
	WEAPTYPE_BULLET = 0x0,
	WEAPTYPE_GRENADE = 0x1,
	WEAPTYPE_PROJECTILE = 0x2,
	WEAPTYPE_BINOCULARS = 0x3,
	WEAPTYPE_NUM = 0x4,
};

enum weapClass_t
{
	WEAPCLASS_RIFLE = 0x0,
	WEAPCLASS_MG = 0x1,
	WEAPCLASS_SMG = 0x2,
	WEAPCLASS_SPREAD = 0x3,
	WEAPCLASS_PISTOL = 0x4,
	WEAPCLASS_GRENADE = 0x5,
	WEAPCLASS_ROCKETLAUNCHER = 0x6,
	WEAPCLASS_TURRET = 0x7,
	WEAPCLASS_NON_PLAYER = 0x8,
	WEAPCLASS_ITEM = 0x9,
	WEAPCLASS_NUM = 0xA,
};

enum PenetrateType
{
	PENETRATE_TYPE_NONE = 0x0,
	PENETRATE_TYPE_SMALL = 0x1,
	PENETRATE_TYPE_MEDIUM = 0x2,
	PENETRATE_TYPE_LARGE = 0x3,
	PENETRATE_TYPE_COUNT = 0x4,
};

enum ImpactType
{
	IMPACT_TYPE_NONE = 0x0,
	IMPACT_TYPE_BULLET_SMALL = 0x1,
	IMPACT_TYPE_BULLET_LARGE = 0x2,
	IMPACT_TYPE_BULLET_AP = 0x3,
	IMPACT_TYPE_SHOTGUN = 0x4,
	IMPACT_TYPE_GRENADE_BOUNCE = 0x5,
	IMPACT_TYPE_GRENADE_EXPLODE = 0x6,
	IMPACT_TYPE_ROCKET_EXPLODE = 0x7,
	IMPACT_TYPE_PROJECTILE_DUD = 0x8,
	IMPACT_TYPE_COUNT = 0x9,
};

enum weapInventoryType_t
{
	WEAPINVENTORY_PRIMARY = 0x0,
	WEAPINVENTORY_OFFHAND = 0x1,
	WEAPINVENTORY_ITEM = 0x2,
	WEAPINVENTORY_ALTMODE = 0x3,
	WEAPINVENTORYCOUNT = 0x4,
};

enum weapFireType_t
{
	WEAPON_FIRETYPE_FULLAUTO = 0x0,
	WEAPON_FIRETYPE_SINGLESHOT = 0x1,
	WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
	WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
	WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
	WEAPON_FIRETYPECOUNT = 0x5,
};

enum OffhandClass
{
	OFFHAND_CLASS_NONE = 0x0,
	OFFHAND_CLASS_FRAG_GRENADE = 0x1,
	OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
	OFFHAND_CLASS_FLASH_GRENADE = 0x3,
	OFFHAND_CLASS_COUNT = 0x4,
};

enum weapStance_t
{
	WEAPSTANCE_STAND = 0x0,
	WEAPSTANCE_DUCK = 0x1,
	WEAPSTANCE_PRONE = 0x2,
	WEAPSTANCE_NUM = 0x3,
};

struct snd_alias_list_t
{
	/*const char *aliasName;
	snd_alias_t *head;
	int count;*/
};

enum activeReticleType_t
{
	VEH_ACTIVE_RETICLE_NONE = 0x0,
	VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
	VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
	VEH_ACTIVE_RETICLE_COUNT = 0x3,
};

enum weaponIconRatioType_t
{
	WEAPON_ICON_RATIO_1TO1 = 0x0,
	WEAPON_ICON_RATIO_2TO1 = 0x1,
	WEAPON_ICON_RATIO_4TO1 = 0x2,
	WEAPON_ICON_RATIO_COUNT = 0x3,
};

enum ammoCounterClipType_t
{
	AMMO_COUNTER_CLIP_NONE = 0x0,
	AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
	AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
	AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
	AMMO_COUNTER_CLIP_ROCKET = 0x4,
	AMMO_COUNTER_CLIP_BELTFED = 0x5,
	AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
	AMMO_COUNTER_CLIP_COUNT = 0x7,
};

enum weapOverlayReticle_t
{
	WEAPOVERLAYRETICLE_NONE = 0x0,
	WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
	WEAPOVERLAYRETICLE_NUM = 0x2,
};

enum WeapOverlayInteface_t
{
	WEAPOVERLAYINTERFACE_NONE = 0x0,
	WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
	WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
	WEAPOVERLAYINTERFACECOUNT = 0x3,
};

enum weapProjExposion_t
{
	WEAPPROJEXP_GRENADE = 0x0,
	WEAPPROJEXP_ROCKET = 0x1,
	WEAPPROJEXP_FLASHBANG = 0x2,
	WEAPPROJEXP_NONE = 0x3,
	WEAPPROJEXP_DUD = 0x4,
	WEAPPROJEXP_SMOKE = 0x5,
	WEAPPROJEXP_HEAVY = 0x6,
	WEAPPROJEXP_NUM = 0x7,
};

enum WeapStickinessType
{
	WEAPSTICKINESS_NONE = 0x0,
	WEAPSTICKINESS_ALL = 0x1,
	WEAPSTICKINESS_GROUND = 0x2,
	WEAPSTICKINESS_GROUND_WITH_YAW = 0x3,
	WEAPSTICKINESS_COUNT = 0x4,
};

enum guidedMissileType_t
{
	MISSILE_GUIDANCE_NONE = 0x0,
	MISSILE_GUIDANCE_SIDEWINDER = 0x1,
	MISSILE_GUIDANCE_HELLFIRE = 0x2,
	MISSILE_GUIDANCE_JAVELIN = 0x3,
	MISSILE_GUIDANCE_COUNT = 0x4,
};

struct clientSession_t
{
	sessionState_t sessionState;
	int forceSpectatorClient;
	int killCamEntity;
	int status_icon;
	int archiveTime;
	int score;
	int deaths;
	int kills;
	int assists;
	unsigned __int16 scriptPersId;
	clientConnected_t connected;
	usercmd_s cmd;
	usercmd_s oldcmd;
	int localClient;
	int predictItemPickup;
	char newnetname[16];
	int maxHealth;
	int enterTime;
	playerTeamState_t teamState;
	int voteCount;
	int teamVoteCount;
	float moveSpeedScaleMultiplier;
	int viewmodelIndex;
	int noSpectate;
	int teamInfo;
	clientState_s cs;
	int psOffsetTime;
};



struct gclient_s
{
	playerState_s ps;
	clientSession_t sess;
	int spectatorClient;
	int noclip;
	int ufo;
	int bFrozen;
	int lastCmdTime;
	int buttons;
	int oldbuttons;
	int latched_buttons;
	int buttonsSinceLastFrame;
	float oldOrigin[3];
	float fGunPitch;
	float fGunYaw;
	int damage_blood;
	float damage_from[3];
	int damage_fromWorld;
	int accurateCount;
	int accuracy_shots;
	int accuracy_hits;
	int inactivityTime;
	int inactivityWarning;
	int lastVoiceTime;
	int switchTeamTime;
	float currentAimSpreadScale;
	gentity_s* persistantPowerup;
	int portalID;
	int dropWeaponTime;
	int sniperRifleFiredTime;
	float sniperRifleMuzzleYaw;
	int PCSpecialPickedUpCount;
	EntHandle useHoldEntity;
	int useHoldTime;
	int useButtonDone;
	int iLastCompassPlayerInfoEnt;
	int compassPingTime;
	int damageTime;
	float v_dmg_roll;
	float v_dmg_pitch;
	float swayViewAngles[3];
	float swayOffset[3];
	float swayAngles[3];
	float vLastMoveAng[3];
	float fLastIdleFactor;
	float vGunOffset[3];
	float vGunSpeed[3];
	int weapIdleTime;
	int lastServerTime;
	int lastSpawnTime;
	unsigned int lastWeapon;
	bool previouslyFiring;
	bool previouslyUsingNightVision;
	bool previouslySprinting;
	int hasRadar;
	int lastStand;
	int lastStandTime;
};

struct turretInfo_s
{
	int inuse;
	int flags;
	int fireTime;
	float arcmin[2];
	float arcmax[2];
	float dropPitch;
	int stance;
	int prevStance;
	int fireSndDelay;
	float userOrigin[3];
	float playerSpread;
	float pitchCap;
	int triggerDown;
	char fireSnd;
	char fireSndPlayer;
	char stopSnd;
	char stopSndPlayer;
};

struct scr_vehicle_s
{
	/*vehicle_pathpos_t pathPos;
	vehicle_physic_t phys;
	int entNum;
	__int16 infoIdx;
	int flags;
	int team;
	VehicleMoveState moveState;
	__int16 waitNode;
	float waitSpeed;
	VehicleTurret turret;
	VehicleJitter jitter;
	VehicleHover hover;
	int drawOnCompass;
	unsigned __int16 lookAtText0;
	unsigned __int16 lookAtText1;
	int manualMode;
	float manualSpeed;
	float manualAccel;
	float manualDecel;
	float manualTime;
	float speed;
	float maxDragSpeed;
	float turningAbility;
	int hasTarget;
	int hasTargetYaw;
	int hasGoalYaw;
	int stopAtGoal;
	int stopping;
	int targetEnt;
	EntHandle lookAtEnt;
	float targetOrigin[3];
	float targetOffset[3];
	float targetYaw;
	float goalPosition[3];
	float goalYaw;
	float prevGoalYaw;
	float yawOverShoot;
	int yawSlowDown;
	float nearGoalNotifyDist;
	float joltDir[2];
	float joltTime;
	float joltWave;
	float joltSpeed;
	float joltDecel;
	int playEngineSound;
	EntHandle idleSndEnt;
	EntHandle engineSndEnt;
	float idleSndLerp;
	float engineSndLerp;
	VehicleTags boneIndex;
	int turretHitNum;
	float forcedMaterialSpeed;*/
};

struct item_ent_t
{
	int ammoCount;
	int clipAmmoCount;
	int index;
};

struct __declspec(align(4)) trigger_ent_t
{
	int threshold;
	int accumulate;
	int timestamp;
	int singleUserEntIndex;
	bool requireLookAt;
};

struct mover_ent_t
{
	float decelTime;
	float aDecelTime;
	float speed;
	float aSpeed;
	float midTime;
	float aMidTime;
	float pos1[3];
	float pos2[3];
	float pos3[3];
	float apos1[3];
	float apos2[3];
	float apos3[3];
};

struct corpse_ent_t
{
	int deathAnimStartTime;
};

enum MissileStage
{
	MISSILESTAGE_SOFTLAUNCH = 0x0,
	MISSILESTAGE_ASCENT = 0x1,
	MISSILESTAGE_DESCENT = 0x2,
};

enum MissileFlightMode
{
	MISSILEFLIGHTMODE_TOP = 0x0,
	MISSILEFLIGHTMODE_DIRECT = 0x1,
};

struct missile_ent_t
{
	float time;
	int timeOfBirth;
	float travelDist;
	float surfaceNormal[3];
	team_t team;
	float curvature[3];
	float targetOffset[3];
	MissileStage stage;
	MissileFlightMode flightMode;
};

union $4C7580D783CB81EAAF8D9BB4061D1D71
{
	item_ent_t item[2];
	trigger_ent_t trigger;
	mover_ent_t mover;
	corpse_ent_t corpse;
	missile_ent_t missile;
};

struct tagInfo_s
{
	gentity_s* parent;
	gentity_s* next;
	unsigned __int16 name;
	int index;
	float axis[4][3];
	float parentInvAxis[4][3];
};

struct gentity_s
{
	entityState_s s;
	entityShared_t r;
	gclient_s* client;
	turretInfo_s* pTurretInfo;
	scr_vehicle_s* scr_vehicle;
	unsigned __int16 model;
	char physicsObject;
	char takedamage;
	char active;
	char nopickup;
	char handler;
	char team;
	unsigned __int16 classname;
	unsigned __int16 target;
	unsigned __int16 targetname;
	unsigned int attachIgnoreCollision;
	int spawnflags;
	int flags;
	int eventTime;
	int freeAfterEvent;
	int unlinkAfterEvent;
	int clipmask;
	int processedFrame;
	EntHandle parent;
	int nextthink;
	int health;
	int maxHealth;
	int damage;
	int count;
	gentity_s* chain;
	$4C7580D783CB81EAAF8D9BB4061D1D71 ___u30;
	EntHandle missileTargetEnt;
	tagInfo_s* tagInfo;
	gentity_s* tagChildren;
	unsigned __int16 attachModelNames[19];
	unsigned __int16 attachTagNames[19];
	int useCount;
	gentity_s* nextFree;
};
struct BulletTraceResults
{
	trace_t trace;
	gentity_s* hitEnt;
	float hitPos[3];
	bool ignoreHitEnt;
	int depthSurfaceType;
};
struct BulletFireParams
{
	int weaponEntIndex;
	int ignoreEntIndex;
	float damageMultiplier;
	int methodOfDeath;
	float origStart[3];
	float start[3];
	float end[3];
	float dir[3];
};

struct TraceInfo
{
	int GroundEntityNum;
	int StateNumber;
	int arr[5];
	int start[3];
	int end[3];
	int pad[27];
};
struct BuiltinMethodDef
{
	const char* actionString;
	void(__cdecl* actionFunc)(int);
	int type;
};

struct WeaponDef
{
	const char* szInternalName;
	const char* szDisplayName;
	const char* szOverlayName;
	XModel* gunXModel[16];
	XModel* handXModel;
	const char* szXAnims[33];
	const char* szModeName;
	unsigned __int16 hideTags[8];
	unsigned __int16 notetrackSoundMapKeys[16];
	unsigned __int16 notetrackSoundMapValues[16];
	int playerAnimType;
	weapType_t weapType;
	weapClass_t weapClass;
	PenetrateType penetrateType;
	ImpactType impactType;
	weapInventoryType_t inventoryType;
	weapFireType_t fireType;
	OffhandClass offhandClass;
	weapStance_t stance;
	FxEffectDef* viewFlashEffect;
	FxEffectDef* worldFlashEffect;
	snd_alias_list_t* pickupSound;
	snd_alias_list_t* pickupSoundPlayer;
	snd_alias_list_t* ammoPickupSound;
	snd_alias_list_t* ammoPickupSoundPlayer;
	snd_alias_list_t* projectileSound;
	snd_alias_list_t* pullbackSound;
	snd_alias_list_t* pullbackSoundPlayer;
	snd_alias_list_t* fireSound;
	snd_alias_list_t* fireSoundPlayer;
	snd_alias_list_t* fireLoopSound;
	snd_alias_list_t* fireLoopSoundPlayer;
	snd_alias_list_t* fireStopSound;
	snd_alias_list_t* fireStopSoundPlayer;
	snd_alias_list_t* fireLastSound;
	snd_alias_list_t* fireLastSoundPlayer;
	snd_alias_list_t* emptyFireSound;
	snd_alias_list_t* emptyFireSoundPlayer;
	snd_alias_list_t* meleeSwipeSound;
	snd_alias_list_t* meleeSwipeSoundPlayer;
	snd_alias_list_t* meleeHitSound;
	snd_alias_list_t* meleeMissSound;
	snd_alias_list_t* rechamberSound;
	snd_alias_list_t* rechamberSoundPlayer;
	snd_alias_list_t* reloadSound;
	snd_alias_list_t* reloadSoundPlayer;
	snd_alias_list_t* reloadEmptySound;
	snd_alias_list_t* reloadEmptySoundPlayer;
	snd_alias_list_t* reloadStartSound;
	snd_alias_list_t* reloadStartSoundPlayer;
	snd_alias_list_t* reloadEndSound;
	snd_alias_list_t* reloadEndSoundPlayer;
	snd_alias_list_t* detonateSound;
	snd_alias_list_t* detonateSoundPlayer;
	snd_alias_list_t* nightVisionWearSound;
	snd_alias_list_t* nightVisionWearSoundPlayer;
	snd_alias_list_t* nightVisionRemoveSound;
	snd_alias_list_t* nightVisionRemoveSoundPlayer;
	snd_alias_list_t* altSwitchSound;
	snd_alias_list_t* altSwitchSoundPlayer;
	snd_alias_list_t* raiseSound;
	snd_alias_list_t* raiseSoundPlayer;
	snd_alias_list_t* firstRaiseSound;
	snd_alias_list_t* firstRaiseSoundPlayer;
	snd_alias_list_t* putawaySound;
	snd_alias_list_t* putawaySoundPlayer;
	snd_alias_list_t** bounceSound;
	FxEffectDef* viewShellEjectEffect;
	FxEffectDef* worldShellEjectEffect;
	FxEffectDef* viewLastShotEjectEffect;
	FxEffectDef* worldLastShotEjectEffect;
	Material* reticleCenter;
	Material* reticleSide;
	int iReticleCenterSize;
	int iReticleSideSize;
	int iReticleMinOfs;
	activeReticleType_t activeReticleType;
	float vStandMove[3];
	float vStandRot[3];
	float vDuckedOfs[3];
	float vDuckedMove[3];
	float vDuckedRot[3];
	float vProneOfs[3];
	float vProneMove[3];
	float vProneRot[3];
	float fPosMoveRate;
	float fPosProneMoveRate;
	float fStandMoveMinSpeed;
	float fDuckedMoveMinSpeed;
	float fProneMoveMinSpeed;
	float fPosRotRate;
	float fPosProneRotRate;
	float fStandRotMinSpeed;
	float fDuckedRotMinSpeed;
	float fProneRotMinSpeed;
	XModel* worldModel[16];
	XModel* worldClipModel;
	XModel* rocketModel;
	XModel* knifeModel;
	XModel* worldKnifeModel;
	Material* hudIcon;
	weaponIconRatioType_t hudIconRatio;
	Material* ammoCounterIcon;
	weaponIconRatioType_t ammoCounterIconRatio;
	ammoCounterClipType_t ammoCounterClip;
	int iStartAmmo;
	const char* szAmmoName;
	int iAmmoIndex;
	const char* szClipName;
	int iClipIndex;
	int iMaxAmmo;
	int iClipSize;
	int shotCount;
	const char* szSharedAmmoCapName;
	int iSharedAmmoCapIndex;
	int iSharedAmmoCap;
	int damage;
	int playerDamage;
	int iMeleeDamage;
	int iDamageType;
	int iFireDelay;
	int iMeleeDelay;
	int meleeChargeDelay;
	int iDetonateDelay;
	int iFireTime;
	int iRechamberTime;
	int iRechamberBoltTime;
	int iHoldFireTime;
	int iDetonateTime;
	int iMeleeTime;
	int meleeChargeTime;
	int iReloadTime;
	int reloadShowRocketTime;
	int iReloadEmptyTime;
	int iReloadAddTime;
	int iReloadStartTime;
	int iReloadStartAddTime;
	int iReloadEndTime;
	int iDropTime;
	int iRaiseTime;
	int iAltDropTime;
	int iAltRaiseTime;
	int quickDropTime;
	int quickRaiseTime;
	int iFirstRaiseTime;
	int iEmptyRaiseTime;
	int iEmptyDropTime;
	int sprintInTime;
	int sprintLoopTime;
	int sprintOutTime;
	int nightVisionWearTime;
	int nightVisionWearTimeFadeOutEnd;
	int nightVisionWearTimePowerUp;
	int nightVisionRemoveTime;
	int nightVisionRemoveTimePowerDown;
	int nightVisionRemoveTimeFadeInStart;
	int fuseTime;
	int aiFuseTime;
	int requireLockonToFire;
	int noAdsWhenMagEmpty;
	int avoidDropCleanup;
	float autoAimRange;
	float aimAssistRange;
	float aimAssistRangeAds;
	float aimPadding;
	float enemyCrosshairRange;
	int crosshairColorChange;
	float moveSpeedScale;
	float adsMoveSpeedScale;
	float sprintDurationScale;
	float fAdsZoomFov;
	float fAdsZoomInFrac;
	float fAdsZoomOutFrac;
	Material* overlayMaterial;
	Material* overlayMaterialLowRes;
	weapOverlayReticle_t overlayReticle;
	WeapOverlayInteface_t overlayInterface;
	float overlayWidth;
	float overlayHeight;
	float fAdsBobFactor;
	float fAdsViewBobMult;
	float fHipSpreadStandMin;
	float fHipSpreadDuckedMin;
	float fHipSpreadProneMin;
	float hipSpreadStandMax;
	float hipSpreadDuckedMax;
	float hipSpreadProneMax;
	float fHipSpreadDecayRate;
	float fHipSpreadFireAdd;
	float fHipSpreadTurnAdd;
	float fHipSpreadMoveAdd;
	float fHipSpreadDuckedDecay;
	float fHipSpreadProneDecay;
	float fHipReticleSidePos;
	int iAdsTransInTime;
	int iAdsTransOutTime;
	float fAdsIdleAmount;
	float fHipIdleAmount;
	float adsIdleSpeed;
	float hipIdleSpeed;
	float fIdleCrouchFactor;
	float fIdleProneFactor;
	float fGunMaxPitch;
	float fGunMaxYaw;
	float swayMaxAngle;
	float swayLerpSpeed;
	float swayPitchScale;
	float swayYawScale;
	float swayHorizScale;
	float swayVertScale;
	float swayShellShockScale;
	float adsSwayMaxAngle;
	float adsSwayLerpSpeed;
	float adsSwayPitchScale;
	float adsSwayYawScale;
	float adsSwayHorizScale;
	float adsSwayVertScale;
	int bRifleBullet;
	int armorPiercing;
	int bBoltAction;
	int aimDownSight;
	int bRechamberWhileAds;
	float adsViewErrorMin;
	float adsViewErrorMax;
	int bCookOffHold;
	int bClipOnly;
	int adsFireOnly;
	int cancelAutoHolsterWhenEmpty;
	int suppressAmmoReserveDisplay;
	int enhanced;
	int laserSightDuringNightvision;
	Material* killIcon;
	weaponIconRatioType_t killIconRatio;
	int flipKillIcon;
	Material* dpadIcon;
	weaponIconRatioType_t dpadIconRatio;
	int bNoPartialReload;
	int bSegmentedReload;
	int iReloadAmmoAdd;
	int iReloadStartAdd;
	const char* szAltWeaponName;
	unsigned int altWeaponIndex;
	int iDropAmmoMin;
	int iDropAmmoMax;
	int blocksProne;
	int silenced;
	int iExplosionRadius;
	int iExplosionRadiusMin;
	int iExplosionInnerDamage;
	int iExplosionOuterDamage;
	float damageConeAngle;
	int iProjectileSpeed;
	int iProjectileSpeedUp;
	int iProjectileSpeedForward;
	int iProjectileActivateDist;
	float projLifetime;
	float timeToAccelerate;
	float projectileCurvature;
	XModel* projectileModel;
	weapProjExposion_t projExplosion;
	FxEffectDef* projExplosionEffect;
	int projExplosionEffectForceNormalUp;
	FxEffectDef* projDudEffect;
	snd_alias_list_t* projExplosionSound;
	snd_alias_list_t* projDudSound;
	int bProjImpactExplode;
	WeapStickinessType stickiness;
	int hasDetonator;
	int timedDetonation;
	int rotate;
	int holdButtonToThrow;
	int freezeMovementWhenFiring;
	float lowAmmoWarningThreshold;
	float parallelBounce[29];
	float perpendicularBounce[29];
	FxEffectDef* projTrailEffect;
	float vProjectileColor[3];
	guidedMissileType_t guidedMissileType;
	float maxSteeringAccel;
	int projIgnitionDelay;
	FxEffectDef* projIgnitionEffect;
	snd_alias_list_t* projIgnitionSound;
	float fAdsAimPitch;
	float fAdsCrosshairInFrac;
	float fAdsCrosshairOutFrac;
	int adsGunKickReducedKickBullets;
	float adsGunKickReducedKickPercent;
	float fAdsGunKickPitchMin;
	float fAdsGunKickPitchMax;
	float fAdsGunKickYawMin;
	float fAdsGunKickYawMax;
	float fAdsGunKickAccel;
	float fAdsGunKickSpeedMax;
	float fAdsGunKickSpeedDecay;
	float fAdsGunKickStaticDecay;
	float fAdsViewKickPitchMin;
	float fAdsViewKickPitchMax;
	float fAdsViewKickYawMin;
	float fAdsViewKickYawMax;
	float fAdsViewKickCenterSpeed;
	float fAdsViewScatterMin;
	float fAdsViewScatterMax;
	float fAdsSpread;
	int hipGunKickReducedKickBullets;
	float hipGunKickReducedKickPercent;
	float fHipGunKickPitchMin;
	float fHipGunKickPitchMax;
	float fHipGunKickYawMin;
	float fHipGunKickYawMax;
	float fHipGunKickAccel;
	float fHipGunKickSpeedMax;
	float fHipGunKickSpeedDecay;
	float fHipGunKickStaticDecay;
	float fHipViewKickPitchMin;
	float fHipViewKickPitchMax;
	float fHipViewKickYawMin;
	float fHipViewKickYawMax;
	float fHipViewKickCenterSpeed;
	float fHipViewScatterMin;
	float fHipViewScatterMax;
	float fightDist;
	float maxDist;
	const char* accuracyGraphName[2];
	float(*accuracyGraphKnots[2])[2];
	float(*originalAccuracyGraphKnots[2])[2];
	int accuracyGraphKnotCount[2];
	int originalAccuracyGraphKnotCount[2];
	int iPositionReloadTransTime;
	float leftArc;
	float rightArc;
	float topArc;
	float bottomArc;
	float accuracy;
	float aiSpread;
	float playerSpread;
	float minTurnSpeed[2];
	float maxTurnSpeed[2];
	float pitchConvergenceTime;
	float yawConvergenceTime;
	float suppressTime;
	float maxRange;
	float fAnimHorRotateInc;
	float fPlayerPositionDist;
	const char* szUseHintString;
	const char* dropHintString;
	int iUseHintStringIndex;
	int dropHintStringIndex;
	float horizViewJitter;
	float vertViewJitter;
	const char* szScript;
	float fOOPosAnimLength[2];
	int minDamage;
	int minPlayerDamage;
	float fMaxDamageRange;
	float fMinDamageRange;
	float destabilizationRateTime;
	float destabilizationCurvatureMax;
	int destabilizeDistance;
	float locationDamageMultipliers[19];
	const char* fireRumble;
	const char* meleeImpactRumble;
	float adsDofStart;
	float adsDofEnd;
};

struct weaponParms
{
	float forward[3];
	float right[3];
	float up[3];
	float muzzleTrace[3];
	float gunForward[3];
	WeaponDef* weapDef;
};

///////////////////// server

struct archivedEntityShared_t
{
	int svFlags;
	int clientMask[2];
	float absmin[3];
	float absmax[3];
};

struct archivedEntity_s
{
	entityState_s s;
	archivedEntityShared_t r;
};

struct cachedSnapshot_t
{
	int archivedFrame;
	int time;
	int num_entities;
	int first_entity;
	int num_clients;
	int first_client;
	int usesDelta;
};

enum netsrc_t
{
	NS_CLIENT1 = 0x0,
	NS_SERVER = 0x1,
	NS_MAXCLIENTS = 0x1,
	NS_PACKET = 0x2,
};

enum netadrtype_t
{
	NA_BOT = 0x0,
	NA_BAD = 0x1,
	NA_LOOPBACK = 0x2,
	NA_BROADCAST = 0x3,
	NA_IP = 0x4,
	NA_IPX = 0x5,
	NA_BROADCAST_IPX = 0x6,
};

struct netadr_t
{
	netadrtype_t type;
	char ip[4];
	unsigned __int16 port;
	char ipx[10];
};

struct netProfilePacket_t
{
	int iTime;
	int iSize;
	int bFragment;
};

struct netProfileStream_t
{
	netProfilePacket_t packets[60];
	int iCurrPacket;
	int iBytesPerSecond;
	int iLastBPSCalcTime;
	int iCountedPackets;
	int iCountedFragments;
	int iFragmentPercentage;
	int iLargestPacket;
	int iSmallestPacket;
};

struct netProfileInfo_t
{
	netProfileStream_t send;
	netProfileStream_t recieve;
};
/*
Netchan handles packet fragmentation and out of order / duplicate suppression
*/

struct netchan_t
{
	int outgoingSequence;
	netsrc_t sock;
	int dropped;				// between last packet and previous
	int incomingSequence;
	netadr_t remoteAddress;
	int qport;					// qport value to write when transmitting
	int fragmentSequence;
	int fragmentLength;
	char* fragmentBuffer;
	int fragmentBufferSize;
	int unsentFragments;
	int unsentFragmentStart;
	int unsentLength;
	char* unsentBuffer;
	int unsentBufferSize;
	netProfileInfo_t prof;
};

struct clientHeader_t
{
	int state;
	int sendAsActive;
	int deltaMessage;
	int rateDelayed;
	netchan_t netchan;
	float predictedOrigin[3];
	int predictedOriginServerTime;
};

struct svscmd_info_t
{
	char cmd[1024];
	int time;
	int type;
};

struct clientSnapshot_t
{
	playerState_s ps;
	int num_entities;
	int num_clients;
	int first_entity;
	int first_client;
	int messageSent;
	int messageAcked;
	int messageSize;
	int serverTime;
};

struct __declspec() VoicePacket_t
{
	char talker;
	char data[256];
	int dataSize;
};

struct clientConnection_t
{
	int qport;
	int clientNum;
	int lastPacketSentTime;				// for retransmits during connection
	int lastPacketTime;					// for timeouts
	netadr_t serverAddress;
	int connectTime;					// for connection retransmits
	int connectPacketCount;
	char serverMessage[256];
	int challenge;
	int checksumFeed;
	int reliableSequence;
	int reliableAcknowledge;			// the last one the server has executed
	char reliableCommands[128][1024];
	int serverMessageSequence;			// message sequence is used by both the network layer and the delta compression layer
	int serverCommandSequence;
	int lastExecutedServerCommand;
	char serverCommands[128][1024];
	bool isServerRestarting;
	int lastClientArchiveIndex;
	char demoName[64];
	int demorecording;
	int demoplaying;
	int isTimeDemo;
	int demowaiting;					// don't record until a non-delta message is received
	int firstDemoFrameSkipped;
	int demofile;						//file handle
	int timeDemoLog;
	int timeDemoFrames;					// counter of rendered frames
	int timeDemoStart;					// cls.realtime before first frame
	int timeDemoPrev;
	int timeDemoBaseTime;				// each frame will be at this time + frameNum * 50
	netchan_t netchan;
	char netchanOutgoingBuffer[2048];
	char netchanIncomingBuffer[131072];
	netProfileInfo_t OOBProf;
	char statPacketsToSend;
	int statPacketSendTime[7];
};
struct recorder_cmds
{
	UINT frame;
	int serverTime;
	int buttons;
	int angles[3];
	char forwardmove;
	char rightmove;
	float fps;
	float origin[3];
	float velocity[3];
	char weapon;
};
struct recorder_once
{
	float startpos[3];
	float endpos[3];
};
enum entityType_t
{
	ET_GENERAL = 0x0,
	ET_PLAYER = 0x1,
	ET_PLAYER_CORPSE = 0x2,
	ET_ITEM = 0x3,
	ET_MISSILE = 0x4,
	ET_INVISIBLE = 0x5,
	ET_SCRIPTMOVER = 0x6,
	ET_SOUND_BLEND = 0x7,
	ET_FX = 0x8,
	ET_LOOP_FX = 0x9,
	ET_PRIMARY_LIGHT = 0xA,
	ET_MG42 = 0xB,
	ET_HELICOPTER = 0xC,
	ET_PLANE = 0xD,
	ET_VEHICLE = 0xE,
	ET_VEHICLE_COLLMAP = 0xF,
	ET_VEHICLE_CORPSE = 0x10,
	ET_EVENTS = 0x11,
};

struct __declspec() client_t
{
	clientHeader_t header;
	const char* dropReason;
	char userinfo[1024];
	svscmd_info_t reliableCommandInfo[128];
	int reliableSequence;
	int reliableAcknowledge;
	int reliableSent;
	int messageAcknowledge;
	int gamestateMessageNum;
	int challenge;
	usercmd_s lastUsercmd;
	int lastClientCommand;
	char lastClientCommandString[1024];
	gentity_s* gentity;
	char name[16];
	int downloading;
	char downloadName[64];
	int download;
	int downloadSize;
	int downloadCount;
	int downloadClientBlock;
	int downloadCurrentBlock;
	int downloadXmitBlock;
	char* downloadBlocks[8];
	int downloadBlockSize[8];
	int downloadEOF;
	int downloadSendTime;
	char downloadURL[256];
	int wwwOk;
	int downloadingWWW;
	int clientDownloadingWWW;
	int wwwFallback;
	int nextReliableTime;
	int lastPacketTime;
	int lastConnectTime;
	int nextSnapshotTime;
	int timeoutCount;
	clientSnapshot_t frames[32];
	int ping;
	int rate;
	int snapshotMsec;
	int snapshotBackoffCount;
	int pureAuthentic;
	char netchanOutgoingBuffer[131072];
	char netchanIncomingBuffer[2048];
	char cdkeyHash[33];
	unsigned __int16 scriptId;
	int bIsTestClient;
	int serverId;
	VoicePacket_t voicePackets[40];
	int voicePacketCount;
	bool muteList[64];
	bool sendVoice;
	char stats[8192];
	char statPacketsReceived;
	bool tempPacketDebugging;
};

struct archivedSnapshot_s
{
	int start;
	int size;
};

struct cachedClient_s
{
	int playerStateExists;
	clientState_s cs;
	playerState_s ps;
};

struct __declspec(align(4)) challenge_t
{
	netadr_t adr;
	int challenge;
	int time;
	int pingTime;
	int firstTime;
	int firstPing;
	int connected;
	char cdkeyHash[33];
};

struct tempBanSlot_t
{
	char cdkeyHash[32];
	int banTime;
};

struct __declspec() serverStatic_t
{
	//cachedSnapshot_t cachedSnapshotFrames[512];
	//archivedEntity_s cachedSnapshotEntities[16384];
	int initialized;
	int time;
	int snapFlagServerBit;
	client_t clients[64];
	int numSnapshotEntities;
	int numSnapshotClients;
	int nextSnapshotEntities;
	int nextSnapshotClients;
	entityState_s snapshotEntities[172032];
	clientState_s snapshotClients[131072];
	int nextArchivedSnapshotFrames;
	archivedSnapshot_s archivedSnapshotFrames[1200];
	char archivedSnapshotBuffer[33554432];
	int nextArchivedSnapshotBuffer;
	int nextCachedSnapshotEntities;
	int nextCachedSnapshotClients;
	int nextCachedSnapshotFrames;
	cachedClient_s cachedSnapshotClients[4096];
	int nextHeartbeatTime;
	int nextStatusResponseTime;
	challenge_t challenges[1024];
	netadr_t redirectAddress;
	netadr_t authorizeAddress;
	int sv_lastTimeMasterServerCommunicated;
	netProfileInfo_t OOBProf;
	tempBanSlot_t tempBans[16];
	float mapCenter[3];
};

struct ServerProfileTimes
{
	float frameTime;
	float wallClockTime;
};

struct svEntity_s
{
	unsigned __int16 worldSector;
	unsigned __int16 nextEntityInWorldSector;
	archivedEntity_s baseline;
	int numClusters;
	int clusternums[16];
	int lastCluster;
	int linkcontents;
	float linkmin[2];
	float linkmax[2];
};

enum serverState_t
{
	SS_DEAD = 0x0,
	SS_LOADING = 0x1,
	SS_GAME = 0x2,
};

struct server_t
{
	serverState_t state;
	int timeResidual;
	bool inFrame;
	int restarting;
	int start_frameTime;
	int checksumFeed;
	cmodel_t* models[512];
	unsigned __int16 emptyConfigString;
	unsigned __int16 configstrings[2442];
	svEntity_s svEntities[1024];
	gentity_s* gentities;
	int gentitySize;
	int num_entities;
	playerState_s* gameClients;
	int gameClientSize;
	int skelTimeStamp;
	int skelMemPos;
	int bpsWindow[20];
	int bpsWindowSteps;
	int bpsTotalBytes;
	int bpsMaxBytes;
	int ubpsWindow[20];
	int ubpsTotalBytes;
	int ubpsMaxBytes;
	float ucompAve;
	int ucompNum;
	ServerProfileTimes profile;
	volatile float serverFrameTimeMin;
	volatile float serverFrameTimeMax;
	char gametype[64];
	bool killServer;
	const char* killReason;
};

struct GfxMatrix
{
	float m[4][4];
};

struct GfxScaledPlacement
{
	GfxPlacement base;
	float scale;
};

struct GfxParticleCloud
{
	GfxScaledPlacement placement;
	float endpos[3];
	GfxColor color;
	float radius[2];
	unsigned int pad[2];
};

struct GfxViewParms
{
	GfxMatrix viewMatrix;
	GfxMatrix projectionMatrix;
	GfxMatrix viewProjectionMatrix;
	GfxMatrix inverseViewProjectionMatrix;
	float origin[4];
	float axis[3][3];
	float depthHackNearClip;
	float zNear;
	float zFar;
};

/*struct GfxViewParms
{
	GfxMatrix viewMatrix;
	GfxMatrix projectionMatrix;
	GfxMatrix viewProjectionMatrix;
	GfxMatrix inverseViewProjectionMatrix;
	float origin[4];
	float axis[3][3];
	float depthHackNearClip;
	float zNear;
	float zFar;
	int pad;
};*/

struct FxCodeMeshData
{
	unsigned int triCount;
	unsigned __int16* indices;
	unsigned __int16 argOffset;
	unsigned __int16 argCount;
	unsigned int pad;
};

struct GfxVertexBufferState
{
	volatile int used;
	int total;
	//int IDirect3DVertexBuffer9; // 
	//IDirect3DVertexBuffer9* buffer;
	char* verts;
};

struct GfxMeshData
{
	unsigned int indexCount;
	unsigned int totalIndexCount;
	unsigned __int16* indices;
	GfxVertexBufferState vb;
	unsigned int vertSize;
};

union PackedLightingCoords
{
	unsigned int packed;
	char array[4];
};
typedef struct
{
	char			unknown0[72];
	vec3_t			Recoil[3];
	vec2_t			Screen;
	char			unknown1[36];
	vec3_t			ViewAxis[3];
	vec3_t			viewOrigin;
}viewMatrix_t;
struct GfxSModelCachedVertex
{
	float xyz[3];
	GfxColor color;
	PackedTexCoords texCoord;
	PackedUnitVec normal;
	PackedUnitVec tangent;
	PackedLightingCoords baseLighting;
};

struct GfxModelLightingPatch
{
	unsigned __int16 modelLightingIndex;
	char primaryLightWeight;
	char colorsCount;
	char groundLighting[4];
	unsigned __int16 colorsWeight[8];
	unsigned __int16 colorsIndex[8];
};

struct GfxBackEndPrimitiveData
{
	int hasSunDirChanged;
};

struct GfxEntity
{
	unsigned int renderFxFlags;
	float materialTime;
};

struct FxMarkMeshData
{
	unsigned int triCount;
	unsigned __int16* indices;
	unsigned __int16 modelIndex;
	char modelTypeAndSurf;
	char pad0;
	unsigned int pad1;
};

struct GfxFog
{
	int startTime;
	int finishTime;
	GfxColor color;
	float fogStart;
	float density;
};

struct GfxCmdHeader
{
	unsigned __int16 id;
	unsigned __int16 byteCount;
};

struct GfxCmdArray
{
	char* cmds;
	int usedTotal;
	int usedCritical;
	GfxCmdHeader* lastCmd;
};

struct GfxSceneDef
{
	int time;
	float floatTime;
	float viewOffset[3];
};

struct GfxViewport
{
	int x;
	int y;
	int width;
	int height;
};

enum ShadowType
{
	SHADOW_NONE = 0x0,
	SHADOW_COOKIE = 0x1,
	SHADOW_MAP = 0x2,
};

struct GfxViewInfo;

struct GfxDrawSurfListInfo
{
	GfxDrawSurf* drawSurfs;
	unsigned int drawSurfCount;
	MaterialTechniqueType baseTechType;
	GfxViewInfo* viewInfo;
	float viewOrigin[4];
	GfxLight* light;
	int cameraView;
};

#pragma warning(push)
#pragma warning(disable: 4324)
struct __declspec(align(16)) ShadowCookie
{
	GfxMatrix shadowLookupMatrix;
	float boxMin[3];
	float boxMax[3];
	GfxViewParms* shadowViewParms;
	float fade;
	unsigned int sceneEntIndex;
	__declspec(align(1)) GfxDrawSurfListInfo casterInfo;
	__declspec(align(1)) GfxDrawSurfListInfo receiverInfo;
};

struct __declspec(align(16)) ShadowCookieList
{
	ShadowCookie cookies[24];
	unsigned int cookieCount;
};
#pragma warning(pop)

struct PointLightPartition
{
	GfxLight light;
	GfxDrawSurfListInfo info;
};

struct GfxDepthOfField
{
	float viewModelStart;
	float viewModelEnd;
	float nearStart;
	float nearEnd;
	float farStart;
	float farEnd;
	float nearBlur;
	float farBlur;
};

struct GfxFilm
{
	bool enabled;
	float brightness;
	float contrast;
	float desaturation;
	bool invert;
	float tintDark[3];
	float tintLight[3];
};

struct GfxGlow
{
	bool enabled;
	float bloomCutoff;
	float bloomDesaturation;
	float bloomIntensity;
	float radius;
};


struct GfxSunShadowBoundingPoly
{
	float snapDelta[2];
	int pointCount;
	float points[9][2];
	int pointIsNear[9];
};

struct __declspec() GfxSunShadowPartition
{
	GfxViewParms shadowViewParms;
	int partitionIndex;
	GfxViewport viewport;
	__declspec(align(1)) GfxDrawSurfListInfo info;
	GfxSunShadowBoundingPoly boundingPoly;
};

struct GfxSunShadowProjection
{
	float viewMatrix[4][4];
	float switchPartition[4];
	float shadowmapScale[4];
};

struct GfxSunShadow
{
	GfxMatrix lookupMatrix;
	GfxSunShadowProjection sunProj;
	GfxSunShadowPartition partition[2];
};

struct __declspec() GfxSpotShadow
{
	GfxViewParms shadowViewParms;
	GfxMatrix lookupMatrix;
	char shadowableLightIndex;
	char pad[3];
	GfxLight* light;
	float fade;
	__declspec(align(1)) GfxDrawSurfListInfo info;
	GfxViewport viewport;
	GfxImage* image;
	GfxRenderTargetId renderTargetId;
	float pixelAdjust[4];
	int clearScreen;
	GfxMeshData* clearMesh;
};

struct GfxQuadMeshData
{
	float x;
	float y;
	float width;
	float height;
	GfxMeshData meshData;
};

struct GfxDebugPoly
{
	float color[4];
	int firstVert;
	int vertCount;
};

struct trDebugString_t
{
	float xyz[3];
	float color[4];
	float scale;
	char text[96];
};

struct trDebugLine_t
{
	float start[3];
	float end[3];
	float color[4];
	int depthTest;
};

struct GfxDebugPlume
{
	float origin[3];
	float color[4];
	int score;
	int startTime;
	int duration;
};

struct DebugGlobals
{
	float(*verts)[3];
	int vertCount;
	int vertLimit;
	GfxDebugPoly* polys;
	int polyCount;
	int polyLimit;
	trDebugString_t* strings;
	int stringCount;
	int stringLimit;
	trDebugString_t* externStrings;
	int externStringCount;
	int externMaxStringCount;
	trDebugLine_t* lines;
	int lineCount;
	int lineLimit;
	trDebugLine_t* externLines;
	int externLineCount;
	int externMaxLineCount;
	GfxDebugPlume* plumes;
	int plumeCount;
	int plumeLimit;
};

struct clientDebugStringInfo_t
{
	int max;
	int num;
	trDebugString_t* strings;
	int* durations;
};

#pragma warning( push )
#pragma warning( disable : 4324 )
struct __declspec(align(16)) GfxBackEndData // align by 16
{
	char surfsBuffer[131072];
	FxCodeMeshData codeMeshes[2048];
	unsigned int primDrawSurfsBuf[65536];
	GfxViewParms viewParms[28]; // GfxViewParms either has pad or zFar
	char primaryLightTechType[13][256];
	float codeMeshArgs[256][4];
	GfxParticleCloud clouds[256];
	GfxDrawSurf drawSurfs[32768];
	GfxMeshData codeMesh;
	GfxSModelCachedVertex smcPatchVerts[8192];
	unsigned __int16 smcPatchList[256];
	unsigned int smcPatchCount;
	unsigned int smcPatchVertsUsed;
	GfxModelLightingPatch modelLightingPatchList[4096];
	volatile int modelLightingPatchCount;
	GfxBackEndPrimitiveData prim;
	unsigned int shadowableLightHasShadowMap[8];
	unsigned int frameCount;
	int drawSurfCount;
	volatile int surfPos;
	volatile int gfxEntCount;
	GfxEntity gfxEnts[128];
	volatile int cloudCount;
	volatile int codeMeshCount;
	volatile int codeMeshArgsCount;
	volatile int markMeshCount;
	FxMarkMeshData markMeshes[1536];
	GfxMeshData markMesh;
	GfxVertexBufferState* skinnedCacheVb;
	int IDirect3DQuery9; //IDirect3DQuery9 *endFence
	char* tempSkinBuf;
	volatile int tempSkinPos;
	int IDirect3DIndexBuffer9; // IDirect3DIndexBuffer9 *preTessIb
	int viewParmCount;
	GfxFog fogSettings;
	GfxCmdArray* commands;
	unsigned int viewInfoIndex;
	unsigned int viewInfoCount;
	GfxViewInfo* viewInfo;
	const void* cmds;
	GfxLight sunLight;
	int hasApproxSunDirChanged;
	volatile int primDrawSurfPos;
	unsigned int* staticModelLit;
	DebugGlobals debugGlobals;
	unsigned int drawType;
};


struct __declspec(align(8)) GfxCmdBufInput
{
	float consts[58][4];
	GfxImage* codeImages[27];
	char codeImageSamplerStates[27];
	GfxBackEndData* data;
};

struct GfxViewInfo
{
	GfxViewParms viewParms;
	GfxSceneDef sceneDef;
	GfxViewport sceneViewport;
	GfxViewport displayViewport;
	GfxViewport scissorViewport;
	ShadowType dynamicShadowType;
	__declspec(align(16)) ShadowCookieList shadowCookieList;
	int localClientNum;
	int isRenderingFullScreen;
	bool needsFloatZ;
	GfxLight shadowableLights[255];
	unsigned int shadowableLightCount;
	PointLightPartition pointLightPartitions[4];
	GfxMeshData pointLightMeshData[4];
	int pointLightCount;
	unsigned int emissiveSpotLightIndex;
	GfxLight emissiveSpotLight;
	int emissiveSpotDrawSurfCount;
	GfxDrawSurf* emissiveSpotDrawSurfs;
	unsigned int emissiveSpotLightCount;
	float blurRadius;
	float frustumPlanes[4][4];
	GfxDepthOfField dof;
	GfxFilm film;
	GfxGlow glow;
	const void* cmds;
	GfxSunShadow sunShadow;
	unsigned int spotShadowCount;
	__declspec() GfxSpotShadow spotShadows[4];
	GfxQuadMeshData* fullSceneViewMesh;
	__declspec(align(1)) GfxDrawSurfListInfo litInfo;
	__declspec(align(1)) GfxDrawSurfListInfo decalInfo;
	__declspec(align(1)) GfxDrawSurfListInfo emissiveInfo;
	GfxCmdBufInput input;
};
#pragma warning( pop )

struct GfxCodeMatrices
{
	GfxMatrix matrix[32];
};

enum GfxViewMode
{
	VIEW_MODE_NONE = 0x0,
	VIEW_MODE_3D = 0x1,
	VIEW_MODE_2D = 0x2,
	VIEW_MODE_IDENTITY = 0x3,
};

enum GfxViewportBehavior
{
	GFX_USE_VIEWPORT_FOR_VIEW = 0x0,
	GFX_USE_VIEWPORT_FULL = 0x1,
};

enum CODEIMAGES
{
	blackSampler = 0x0,
	whiteSampler = 0x1,
	identityNormalMapSampler = 0x2,
	null3 = 0x3,
	null4 = 0x4,
	null5 = 0x5,
	shadowCookieSampler = 0x6,
	shadowmapSamplerSun = 0x7,
	shadowmapSamplerSpot = 0x8,
	feedbackSampler = 0x9,
	resolvedPostSun = 0xA,
	resolvedScene = 0xB,
	postEffect0 = 0xC,
	postEffect1 = 0xD,
	skySampler = 0xE,
	attenuationSampler = 0xF,
	dynamicShadowSampler = 0x10,
	outdoorSampler = 0x11,
	floatzSampler = 0x12,
	processedFloatZSampler = 0x13,
	rawFloatZSampler = 0x14,
	caseTextureSampler = 0x15,
	cinematicY = 0x16,
	cinematicCr = 0x17,
	cinematicCb = 0x18,
	cinematicA = 0x19,
	null26 = 0x1A,
	null27 = 0x1B,
};


#pragma warning( push )
#pragma warning( disable : 4324 )
struct __declspec(align(16)) GfxCmdBufSourceState
{
	GfxCodeMatrices matrices;
	GfxCmdBufInput input;
	GfxViewParms viewParms;
	GfxMatrix shadowLookupMatrix;
	unsigned __int16 constVersions[90];
	unsigned __int16 matrixVersions[8];
	float eyeOffset[4];
	unsigned int shadowableLightForShadowLookupMatrix;
	GfxScaledPlacement* objectPlacement;
	GfxViewParms* viewParms3D;
	unsigned int depthHackFlags;
	GfxScaledPlacement skinnedPlacement;
	int cameraView;
	GfxViewMode viewMode;
	GfxSceneDef sceneDef;
	GfxViewport sceneViewport;
	float materialTime;
	GfxViewportBehavior viewportBehavior;
	int renderTargetWidth;
	int renderTargetHeight;
	bool viewportIsDirty;
	unsigned int shadowableLightIndex;
};
#pragma warning( pop )

struct GfxImageFilterPass
{
	Material* material;
	float srcWidth;
	float srcHeight;
	int dstWidth;
	int dstHeight;
	int tapHalfCount;
	float tapOffsetsAndWeights[8][4];
};

struct GfxImageFilter
{
	int passCount;
	GfxImageFilterPass passes[32];
	GfxImage* sourceImage;
	GfxRenderTargetId finalTarget;
};

struct gfxVertexSteamsUnk
{
	unsigned int stride;
	int* vb; // IDirect3DVertexBuffer9
	unsigned int offset;
};

enum GfxDepthRangeType
{
	GFX_DEPTH_RANGE_SCENE = 0x0,
	GFX_DEPTH_RANGE_VIEWMODEL = 0x2,
	GFX_DEPTH_RANGE_FULL = 0xFFFFFFFF,
};

enum MaterialVertexDeclType
{
	VERTDECL_GENERIC = 0x0,
	VERTDECL_PACKED = 0x1,
	VERTDECL_WORLD = 0x2,
	VERTDECL_WORLD_T1N0 = 0x3,
	VERTDECL_WORLD_T1N1 = 0x4,
	VERTDECL_WORLD_T2N0 = 0x5,
	VERTDECL_WORLD_T2N1 = 0x6,
	VERTDECL_WORLD_T2N2 = 0x7,
	VERTDECL_WORLD_T3N0 = 0x8,
	VERTDECL_WORLD_T3N1 = 0x9,
	VERTDECL_WORLD_T3N2 = 0xA,
	VERTDECL_WORLD_T4N0 = 0xB,
	VERTDECL_WORLD_T4N1 = 0xC,
	VERTDECL_WORLD_T4N2 = 0xD,
	VERTDECL_POS_TEX = 0xE,
	VERTDECL_STATICMODELCACHE = 0xF,
	VERTDECL_COUNT = 0x10,
};

struct GfxCmdBufPrimState
{
	int* device; // IDirect3DDevice9
	int* indexBuffer; // IDirect3DIndexBuffer9
	MaterialVertexDeclType vertDeclType;
	gfxVertexSteamsUnk streams[2];
	int* vertexDecl; // IDirect3DVertexDeclaration9
};

struct GfxCmdBufState
{
	char refSamplerState[16];
	unsigned int samplerState[16];
	GfxTexture* samplerTexture[16];
	GfxCmdBufPrimState prim;
	Material* material;
	MaterialTechniqueType techType;
	MaterialTechnique* technique;
	MaterialPass* pass;
	unsigned int passIndex;
	GfxDepthRangeType depthRangeType;
	float depthRangeNear;
	float depthRangeFar;
	unsigned __int64 vertexShaderConstState[32];
	unsigned __int64 pixelShaderConstState[256];
	char alphaRef;
	unsigned int refStateBits[2];
	unsigned int activeStateBits[2];
	MaterialPixelShader* pixelShader;
	MaterialVertexShader* vertexShader;
	GfxViewport viewport;
	GfxRenderTargetId renderTargetId;
	Material* origMaterial;
	MaterialTechniqueType origTechType;
};

struct GfxVertex
{
	float xyzw[4];
	GfxColor color;
	float texCoord[2];
	PackedUnitVec normal;
};

//struct GfxRenderTargetSurface
//{
//	IDirect3DSurface9* color;
//	IDirect3DSurface9* depthStencil;
//};

struct GfxRenderTarget
{
	GfxImage* image;
	//GfxRenderTargetSurface surface;
	unsigned int width;
	unsigned int height;
};

struct __declspec() materialCommands_t
{
	GfxVertex verts[5450];
	unsigned __int16 indices[1048576];
	MaterialVertexDeclType vertDeclType;
	unsigned int vertexSize;
	int indexCount;
	int vertexCount;
	int firstVertex;
	int lastVertex;
	bool finishedFilling;
};

struct clientLogo_t
{
	int startTime;
	int duration;
	int fadein;
	int fadeout;
	Material* material[2];
};

struct serverInfo_t
{
	netadr_t adrr;
	char allowAnonymous;
	char bPassword;
	char pure;
	char consoleDisabled;
	char netType;
	char clients;
	char maxClients;
	char dirty;
	char friendlyfire;
	char killcam;
	char hardware;
	char mod;
	char voice;
	char punkbuster;
	char requestCount;
	bool unk;
	__int16 unk2;
	__int16 minPing;
	__int16 maxPing;
	__int16 ping;
	char pad_0x002C[0x5]; //0x002C
	char hostName[32];
	char mapName[32];
	char game[24];
	char gameType[16];
	char pad_0x0099[0x3]; //0x0099
}; //Size=0x009C

struct __declspec(align(4)) vidConfig_t
{
	unsigned int sceneWidth;
	unsigned int sceneHeight;
	unsigned int displayWidth;
	unsigned int displayHeight;
	unsigned int displayFrequency;
	int isFullscreen;
	float aspectRatioWindow;
	float aspectRatioScenePixel;
	float aspectRatioDisplayPixel;
	unsigned int maxTextureSize;
	unsigned int maxTextureMaps;
	bool deviceSupportsGamma;
};

struct clientDebugLineInfo_t
{
	int max;
	int num;
	trDebugLine_t* lines;
	int* durations;
};

struct clientDebug_t
{
	int prevFromServer;
	int fromServer;
	clientDebugStringInfo_t clStrings;
	clientDebugStringInfo_t svStringsBuffer;
	clientDebugStringInfo_t svStrings;
	clientDebugLineInfo_t clLines;
	clientDebugLineInfo_t svLinesBuffer;
	clientDebugLineInfo_t svLines;
};

struct clientStatic_t
{
	int quit;
	int hunkUsersStarted;
	char servername[256];
	int rendererStarted;
	int soundStarted;
	int uiStarted;
	int frametime;
	int realtime;
	int realFrametime;
	clientLogo_t logo;
	float mapCenter[3];
	int numlocalservers;
	serverInfo_t localServers[128];
	int ui_displayedServerAmount;
	int ui_totalServerAmount;
	int ui_someothercrap;
	int waitglobalserverresponse;
	int numglobalservers;
	serverInfo_t globalServers[20000];
	int numfavoriteservers;
	serverInfo_t favoriteServers[128];
	int pingUpdateSource;
	netadr_t updateServer;
	char updateChallenge[1024];
	char updateInfoString[1024];
	netadr_t authorizeServer;
	Material* whiteMaterial;
	Material* consoleMaterial;
	Font_s* consoleFont;
	char autoupdateServerNames[5][64];
	netadr_t autoupdateServer;
	vidConfig_t vidConfig;
	clientDebug_t debug;
	int download;
	char downloadTempName[256];
	char downloadName[256];
	int downloadNumber;
	int downloadBlock;
	int downloadCount;
	int downloadSize;
	char downloadList[1024];
	int downloadRestart;
	int gameDirChanged;
	int wwwDlDisconnected;
	int wwwDlInProgress;
	int downloadFlags;
	char originalDownloadName[64];
	float debugRenderPos[3];
};

struct fileInIwd_s
{
	unsigned int pos;
	char* name;
	fileInIwd_s* next;
};

struct iwd_t
{
	char iwdFilename[256];
	char iwdBasename[256];
	char iwdGamename[256];
	char* handle;
	int checksum;
	int pure_checksum;
	volatile int hasOpenFile;
	int numfiles;
	char referenced;
	unsigned int hashSize;
	fileInIwd_s** hashTable;
	fileInIwd_s* buildBuffer;
};

struct directory_t
{
	char path[256];
	char gamedir[256];
};

struct searchpath_s
{
	searchpath_s* next;
	iwd_t* iwd;
	directory_t* dir;
	int bLocalized;
	int ignore;
	int ignorePureCheck;
	int language;
};

struct rectDef_s
{
	float x;
	float y;
	float w;
	float h;
	int horzAlign;
	int vertAlign;
};

struct windowDef_t
{
	const char* name;
	rectDef_s rect;
	rectDef_s rectClient;
	const char* group;
	int style;
	int border;
	int ownerDraw;
	int ownerDrawFlags;
	float borderSize;
	int staticFlags;
	int dynamicFlags[1];
	int nextTime;
	float foreColor[4];
	float backColor[4];
	float borderColor[4];
	float outlineColor[4];
	Material* background;
};

union operandInternalDataUnion
{
	int intVal;
	float floatVal;
	const char* string;
};

enum expDataType
{
	VAL_INT = 0x0,
	VAL_FLOAT = 0x1,
	VAL_STRING = 0x2,
};

struct Operand
{
	expDataType dataType;
	operandInternalDataUnion internals;
};

union entryInternalData
{
	//operationEnum op; // $8F00D86C453A25D588E012916CBB9FA9 operationEnum;
	int operationEnum;
	Operand operand;
};

struct expressionEntry
{
	int type;
	entryInternalData data;
};

struct statement_s
{
	int numEntries;
	expressionEntry** entries;
};

struct ItemKeyHandler
{
	int key;
	const char* action;
	ItemKeyHandler* next;
};

struct columnInfo_s
{
	int pos;
	int width;
	int maxChars;
	int alignment;
};

struct listBoxDef_s
{
	int mousePos;
	int startPos[1];
	int endPos[1];
	int drawPadding;
	float elementWidth;
	float elementHeight;
	int elementStyle;
	int numColumns;
	columnInfo_s columnInfo[16];
	const char* doubleClick;
	int notselectable;
	int noScrollBars;
	int usePaging;
	float selectBorder[4];
	float disableColor[4];
	Material* selectIcon;
};

struct editFieldDef_s
{
	float minVal;
	float maxVal;
	float defVal;
	float range;
	int maxChars;
	int maxCharsGotoNext;
	int maxPaintChars;
	int paintOffset;
};

struct multiDef_s
{
	const char* dvarList[32];
	const char* dvarStr[32];
	float dvarValue[32];
	int count;
	int strDef;
};

union itemDefData_t
{
	listBoxDef_s* listBox;
	editFieldDef_s* editField;
	multiDef_s* multi;
	const char* enumDvarName;
	void* data;
};

struct itemDef_s;

struct menuDef_t
{
	windowDef_t window;
	const char* font;
	int fullScreen;
	int itemCount;
	int fontIndex;
	int cursorItem[1];
	int fadeCycle;
	float fadeClamp;
	float fadeAmount;
	float fadeInAmount;
	float blurRadius;
	const char* onOpen;
	const char* onClose;
	const char* onESC;
	ItemKeyHandler* onKey;
	statement_s visibleExp;
	const char* allowedBinding;
	const char* soundName; //soundloop
	int imageTrack;
	float focusColor[4];
	float disableColor[4];
	statement_s rectXExp;
	statement_s rectYExp;
	itemDef_s** items;
};

struct itemDef_s
{
	windowDef_t window;
	rectDef_s textRect[1];
	int type;
	int dataType;
	int alignment;
	int fontEnum;
	int textAlignMode;
	float textalignx;
	float textaligny;
	float textscale;
	int textStyle;
	int gameMsgWindowIndex;
	int gameMsgWindowMode;
	const char* text;
	int textSavegame; //original name: itemFlags
	menuDef_t* parent;
	const char* mouseEnterText;
	const char* mouseExitText;
	const char* mouseEnter;
	const char* mouseExit;
	const char* action;
	const char* onAccept;
	const char* onFocus;
	const char* leaveFocus;
	const char* dvar;
	const char* dvarTest;
	ItemKeyHandler* onKey;
	const char* enableDvar;
	int dvarFlags;
	snd_alias_list_t* focusSound;
	int feeder; //float feeder; //original name: special
	int cursorPos[1];
	itemDefData_t typeData;
	int imageTrack;
	statement_s visibleExp;
	statement_s textExp;
	statement_s materialExp;
	statement_s rectXExp;
	statement_s rectYExp;
	statement_s rectWExp;
	statement_s rectHExp;
	statement_s forecolorAExp;
};

struct MenuList
{
	const char* name;
	int menuCount;
	menuDef_t** menus;
};

struct cursor_t // $38C3DEC81229B66F67FB6D350D75FF5A
{
	float x;
	float y;
};

enum UILocalVarType
{
	UILOCALVAR_INT = 0x0,
	UILOCALVAR_FLOAT = 0x1,
	UILOCALVAR_STRING = 0x2,
};

union $B42A88463653BDCDFC5664844B4491DA
{
	int integer;
	float value;
	const char* string;
};
struct UILocalVar
{
	UILocalVarType type;
	const char* name;
	$B42A88463653BDCDFC5664844B4491DA u;
};

struct UILocalVarContext
{
	UILocalVar table[256];
};

struct UiContext
{
	int localClientNum;
	float bias;
	int realTime;
	int frameTime;
	cursor_t cursor;
	int isCursorVisible;
	int screenWidth;
	int screenHeight;
	float screenAspect;
	float FPS;
	float blurRadiusOut;
	menuDef_t* Menus[640];
	int menuCount;
	menuDef_t* menuStack[16];
	int openMenuCount;
	UILocalVarContext localVars;
};

enum LocSelInputState
{
	LOC_SEL_INPUT_NONE = 0x0,
	LOC_SEL_INPUT_CONFIRM = 0x1,
	LOC_SEL_INPUT_CANCEL = 0x2,
};

struct KeyState
{
	int down;
	int repeats;
	const char* binding;
};

struct PlayerKeyState
{
	/*field_t chatField;*/
	int chat_team;			// 0x8F1DB8
	int overstrikeMode;
	int anyKeyDown;
	KeyState keys[256];
	LocSelInputState locSelInputState;
};

enum connstate_t
{
	CA_DISCONNECTED = 0x0,
	CA_CINEMATIC = 0x1,
	CA_LOGO = 0x2,
	CA_CONNECTING = 0x3,
	CA_CHALLENGING = 0x4,
	CA_CONNECTED = 0x5,
	CA_SENDINGSTATS = 0x6,
	CA_LOADING = 0x7,
	CA_PRIMED = 0x8,
	CA_ACTIVE = 0x9,
};

struct clientUIActive_t
{
	bool active;
	bool isRunning;
	bool cgameInitialized;
	bool cgameInitCalled;
	int keyCatchers;
	bool displayHUDWithKeycatchUI;
	connstate_t connectionState;
};

struct score_t
{
	int client;
	int score;
	int ping;
	int deaths;
	int team;
	int kills;
	int rank;
	int assists;
	Material* hStatusIcon;
	Material* hRankIcon;
};

struct refdef_s
{
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
	float tanHalfFovX;
	float tanHalfFovY;
	float vieworg[3];
	float viewaxis[3][3];
	float viewOffset[3];
	int time;
	float zNear;
	float blurRadius;
	GfxDepthOfField dof;
	GfxFilm film;
	GfxGlow glow;
	GfxLight primaryLights[255];
	GfxViewport scissorViewport;
	bool useScissorViewport;
	int localClientNum;
};

struct playerEntity_t
{
	float fLastWeaponPosFrac;
	int bPositionToADS;
	float vPositionLastOrg[3];
	float fLastIdleFactor;
	float vLastMoveOrg[3];
	float vLastMoveAng[3];
};

struct GfxSkinCacheEntry
{
	unsigned int frameCount;
	int skinnedCachedOffset;
	unsigned __int16 numSkinnedVerts;
	unsigned __int16 ageCount;
};

struct cpose_t
{
	unsigned __int16 lightingHandle;
	char eType;
	char eTypeUnion;
	char localClientNum;
	int cullIn;
	char isRagdoll;
	int ragdollHandle;
	int killcamRagdollHandle;
	int physObjId;
	float origin[3];
	float angles[3];
	GfxSkinCacheEntry skinCacheEntry;
	//$EAE81CC4C8A7A2F7E95AA09AC9F9F9C0 ___u12;
	char pad[0x24];
};

struct centity_s
{
	cpose_t pose;
	LerpEntityState currentState;
	entityState_s nextState;
	bool nextValid;
	bool bMuzzleFlash;
	bool bTrailMade;
	int previousEventSequence;
	int miscTime;
	float lightingOrigin[3];
	void* tree; // XAnimTree_s
};

//enum CubemapShot
//{
//	CUBEMAPSHOT_NONE = 0x0,
//	CUBEMAPSHOT_RIGHT = 0x1,
//	CUBEMAPSHOT_LEFT = 0x2,
//	CUBEMAPSHOT_BACK = 0x3,
//	CUBEMAPSHOT_FRONT = 0x4,
//	CUBEMAPSHOT_UP = 0x5,
//	CUBEMAPSHOT_DOWN = 0x6,
//	CUBEMAPSHOT_COUNT = 0x7,
//};

//enum DemoType
//{
//	DEMO_TYPE_NONE = 0x0,
//	DEMO_TYPE_CLIENT = 0x1,
//	DEMO_TYPE_SERVER = 0x2,
//};

enum InvalidCmdHintType
{
	INVALID_CMD_NONE = 0x0,
	INVALID_CMD_NO_AMMO_BULLETS = 0x1,
	INVALID_CMD_NO_AMMO_FRAG_GRENADE = 0x2,
	INVALID_CMD_NO_AMMO_SPECIAL_GRENADE = 0x3,
	INVALID_CMD_NO_AMMO_FLASH_GRENADE = 0x4,
	INVALID_CMD_STAND_BLOCKED = 0x5,
	INVALID_CMD_CROUCH_BLOCKED = 0x6,
	INVALID_CMD_TARGET_TOO_CLOSE = 0x7,
	INVALID_CMD_LOCKON_REQUIRED = 0x8,
	INVALID_CMD_NOT_ENOUGH_CLEARANCE = 0x9,
};

struct $F6DFD6D87F75480A1EF1906639406DF5
{
	int time;
	int duration;
};

struct shellshock_t
{
	void* parms; //shellshock_parms_t
	int startTime;
	int duration;
	int loopEndTime;
	float sensitivity;
	float viewDelta[2];
	int hasSavedScreen;
};

struct viewDamage_t
{
	int time;
	int duration;
	float yaw;
};

struct animScriptCommand_t
{
	__int16 bodyPart[2];
	__int16 animIndex[2];
	__int16 animDuration[2];
	snd_alias_list_t* soundAlias;
};

struct animScriptCondition_t
{
	int index;
	unsigned int value[2];
};

struct animScriptItem_t
{
	int numConditions;
	animScriptCondition_t conditions[10];
	int numCommands;
	animScriptCommand_t commands[8];
};

struct animScript_t
{
	int numItems;
	animScriptItem_t* items[128];
};

struct __declspec(align(8)) animation_s
{
	char name[64];
	int initialLerp;
	float moveSpeed;
	int duration;
	int nameHash;
	int flags;
	__int64 movetype;
	int noteType;
};

struct scr_animtree_t
{
	void* anims; //XAnim_s
};

struct __declspec(align(8)) animScriptData_t
{
	animation_s animations[512];
	unsigned int numAnimations;
	animScript_t scriptAnims[1][43];
	animScript_t scriptCannedAnims[1][43];
	animScript_t scriptStateChange[1][1];
	animScript_t scriptEvents[21];
	animScriptItem_t scriptItems[2048];
	int numScriptItems;
	scr_animtree_t animTree;
	unsigned __int16 torsoAnim;
	unsigned __int16 legsAnim;
	unsigned __int16 turningAnim;
	snd_alias_list_t* (__cdecl* soundAlias)(const char*);
	int(__cdecl* playSoundAlias)(int, snd_alias_list_t*);
};
enum entity_event_t
{
	EV_NONE = 0x0,
	EV_FOLIAGE_SOUND = 0x1,
	EV_STOP_WEAPON_SOUND = 0x2,
	EV_SOUND_ALIAS = 0x3,
	EV_SOUND_ALIAS_AS_MASTER = 0x4,
	EV_STOPSOUNDS = 0x5,
	EV_STANCE_FORCE_STAND = 0x6,
	EV_STANCE_FORCE_CROUCH = 0x7,
	EV_STANCE_FORCE_PRONE = 0x8,
	EV_ITEM_PICKUP = 0x9,
	EV_AMMO_PICKUP = 0xA,
	EV_NOAMMO = 0xB,
	EV_EMPTYCLIP = 0xC,
	EV_EMPTY_OFFHAND = 0xD,
	EV_RESET_ADS = 0xE,
	EV_RELOAD = 0xF,
	EV_RELOAD_FROM_EMPTY = 0x10,
	EV_RELOAD_START = 0x11,
	EV_RELOAD_END = 0x12,
	EV_RELOAD_START_NOTIFY = 0x13,
	EV_RELOAD_ADDAMMO = 0x14,
	EV_RAISE_WEAPON = 0x15,
	EV_FIRST_RAISE_WEAPON = 0x16,
	EV_PUTAWAY_WEAPON = 0x17,
	EV_WEAPON_ALT = 0x18,
	EV_PULLBACK_WEAPON = 0x19,
	EV_FIRE_WEAPON = 0x1A,
	EV_FIRE_WEAPON_LASTSHOT = 0x1B,
	EV_RECHAMBER_WEAPON = 0x1C,
	EV_EJECT_BRASS = 0x1D,
	EV_MELEE_SWIPE = 0x1E,
	EV_FIRE_MELEE = 0x1F,
	EV_PREP_OFFHAND = 0x20,
	EV_USE_OFFHAND = 0x21,
	EV_SWITCH_OFFHAND = 0x22,
	EV_MELEE_HIT = 0x23,
	EV_MELEE_MISS = 0x24,
	EV_MELEE_BLOOD = 0x25,
	EV_FIRE_WEAPON_MG42 = 0x26,
	EV_FIRE_QUADBARREL_1 = 0x27,
	EV_FIRE_QUADBARREL_2 = 0x28,
	EV_BULLET_HIT = 0x29,
	EV_BULLET_HIT_CLIENT_SMALL = 0x2A,
	EV_BULLET_HIT_CLIENT_LARGE = 0x2B,
	EV_GRENADE_BOUNCE = 0x2C,
	EV_GRENADE_EXPLODE = 0x2D,
	EV_ROCKET_EXPLODE = 0x2E,
	EV_ROCKET_EXPLODE_NOMARKS = 0x2F,
	EV_FLASHBANG_EXPLODE = 0x30,
	EV_CUSTOM_EXPLODE = 0x31,
	EV_CUSTOM_EXPLODE_NOMARKS = 0x32,
	EV_CHANGE_TO_DUD = 0x33,
	EV_DUD_EXPLODE = 0x34,
	EV_DUD_IMPACT = 0x35,
	EV_BULLET = 0x36,
	EV_PLAY_FX = 0x37,
	EV_PLAY_FX_ON_TAG = 0x38,
	EV_PHYS_EXPLOSION_SPHERE = 0x39,
	EV_PHYS_EXPLOSION_CYLINDER = 0x3A,
	EV_PHYS_EXPLOSION_JOLT = 0x3B,
	EV_PHYS_JITTER = 0x3C,
	EV_EARTHQUAKE = 0x3D,
	EV_GRENADE_SUICIDE = 0x3E,
	EV_DETONATE = 0x3F,
	EV_NIGHTVISION_WEAR = 0x40,
	EV_NIGHTVISION_REMOVE = 0x41,
	EV_OBITUARY = 0x42,
	EV_NO_FRAG_GRENADE_HINT = 0x43,
	EV_NO_SPECIAL_GRENADE_HINT = 0x44,
	EV_TARGET_TOO_CLOSE_HINT = 0x45,
	EV_TARGET_NOT_ENOUGH_CLEARANCE = 0x46,
	EV_LOCKON_REQUIRED_HINT = 0x47,
	EV_FOOTSTEP_SPRINT = 0x48,
	EV_FOOTSTEP_RUN = 0x49,
	EV_FOOTSTEP_WALK = 0x4A,
	EV_FOOTSTEP_PRONE = 0x4B,
	EV_JUMP = 0x4C,
	EV_LANDING_FIRST = 0x4D,
	EV_LANDING_LAST = 0x69,
	EV_LANDING_PAIN_FIRST = 0x6A,
	EV_LANDING_PAIN_LAST = 0x86,
	EV_MAX_EVENTS = 0x87,
};

struct $0867E0FC4F8157A276DAB76B1612E229
{
	scr_animtree_t tree;
	int torso; //scr_anim_s
	int legs; //scr_anim_s
	int turning; //scr_anim_s
};

struct lerpFrame_t
{
	float yawAngle;
	int yawing;
	float pitchAngle;
	int pitching;
	int animationNumber;
	void* animation; //animation_s
	int animationTime;
	float oldFramePos[3];
	float animSpeedScale;
	int oldFrameSnapshotTime;
};

struct clientControllers_t
{
	float angles[6][3];
	float tag_origin_angles[3];
	float tag_origin_offset[3];
};

struct __declspec(align(4)) clientInfo_t
{
	int infoValid;
	int nextValid;
	int clientNum;
	char name[16];
	team_t team;
	team_t oldteam;
	int rank;
	int prestige;
	int perks;
	int score;
	int location;
	int health;
	char model[64];
	char attachModelNames[6][64];
	char attachTagNames[6][64];
	lerpFrame_t legs;
	lerpFrame_t torso;
	float lerpMoveDir;
	float lerpLean;
	float playerAngles[3];
	int leftHandGun;
	int dobjDirty;
	clientControllers_t control;
	unsigned int clientConditions[10][2];
	void* pXAnimTree; //XAnimTree_s
	int iDObjWeapon;
	char weaponModel;
	int stanceTransitionTime;
	int turnAnimEndTime;
	char turnAnimType;
	int attachedVehEntNum;
	int attachedVehSlotIndex;
	bool hideWeapon;
	bool usingKnife;
};

//struct __declspec(align(2)) DObjModel_s
//{
//	XModel* model;
//	unsigned __int16 boneName;
//	bool ignoreCollision;
//};

struct XAnimTree_s;

struct bgs_t
{
	animScriptData_t animScriptData;
	$0867E0FC4F8157A276DAB76B1612E229 generic_human;
	int time;
	int latestSnapshotTime;
	int frametime;
	int anim_user;
	XModel* (__cdecl* GetXModel)(const char*);
	void* CreateDObj; //void(__cdecl* CreateDObj)(DObjModel_s*, unsigned __int16, XAnimTree_s*, int, int, clientInfo_t*);
	unsigned __int16 AttachWeapon; //unsigned __int16 (__cdecl *AttachWeapon)(DObjModel_s *, unsigned __int16, clientInfo_t *);
	void* DObj; //DObj_s *(__cdecl *GetDObj)(int, int);
	void(__cdecl* SafeDObjFree)(int, int);
	void* (__cdecl* AllocXAnim)(int);
	clientInfo_t clientinfo[64];
};

struct visionSetVars_t
{
	bool glowEnable;
	float glowBloomCutoff;
	float glowBloomDesaturation;
	float glowBloomIntensity0;
	float glowBloomIntensity1;
	float glowRadius0;
	float glowRadius1;
	float glowSkyBleedIntensity0;
	float glowSkyBleedIntensity1;
	bool filmEnable;
	float filmBrightness;
	float filmContrast;
	float filmDesaturation;
	bool filmInvert;
	float filmLightTint[3];
	float filmDarkTint[3];
};

enum visionSetLerpStyle_t
{
	VISIONSETLERP_UNDEFINED = 0x0,
	VISIONSETLERP_NONE = 0x1,
	VISIONSETLERP_TO_LINEAR = 0x2,
	VISIONSETLERP_TO_SMOOTH = 0x3,
	VISIONSETLERP_BACKFORTH_LINEAR = 0x4,
	VISIONSETLERP_BACKFORTH_SMOOTH = 0x5,
};

struct visionSetLerpData_t
{
	int timeStart;
	int timeDuration;
	visionSetLerpStyle_t style;
};

struct $BE9F66374A020A9809EEAF403416A176
{
	float aimSpreadScale;
};

struct hudElemSoundInfo_t
{
	int lastPlayedTime;
};

struct cg_s
{
	int clientNum;
	int localClientNum;
	DemoType demoType;
	CubemapShot cubemapShot;
	int cubemapSize;
	int renderScreen;
	int latestSnapshotNum;
	int latestSnapshotTime;
	snapshot_s* snap;
	snapshot_s* nextSnap;
	snapshot_s activeSnapshots[2];
	float frameInterpolation;
	int frametime;
	int time;
	int oldTime;
	int physicsTime;
	int mapRestart;
	int renderingThirdPerson;
	playerState_s predictedPlayerState;
	centity_s predictedPlayerEntity;
	playerEntity_t playerEntity;
	int predictedErrorTime;
	float predictedError[3];
	float landChange;
	int landTime;
	float heightToCeiling;
	refdef_s refdef;
	float refdefViewAngles[3];
	float lastVieworg[3];
	float swayViewAngles[3];
	float swayAngles[3];
	float swayOffset[3];
	int iEntityLastType[1024];
	XModel* pEntityLastXModel[1024];
	float zoomSensitivity;
	bool isLoading;
	char objectiveText[1024];
	char scriptMainMenu[256];
	int scoresRequestTime;
	int numScores;
	int teamScores[4];
	int teamPings[4];
	int teamPlayers[4];
	score_t scores[64];
	int scoreLimit;
	int showScores;
	int scoreFadeTime;
	int scoresTop;
	int scoresOffBottom;
	int scoresBottom;
	int drawHud;
	int crosshairClientNum;
	int crosshairClientLastTime;
	int crosshairClientStartTime;
	int identifyClientNum;
	int cursorHintIcon;
	int cursorHintTime;
	int cursorHintFade;
	int cursorHintString;
	int lastClipFlashTime;
	InvalidCmdHintType invalidCmdHintType;
	int invalidCmdHintTime;
	int lastHealthPulseTime;
	int lastHealthLerpDelay;
	int lastHealthClient;
	float lastHealth;
	float healthOverlayFromAlpha;
	float healthOverlayToAlpha;
	int healthOverlayPulseTime;
	int healthOverlayPulseDuration;
	int healthOverlayPulsePhase;
	bool healthOverlayHurt;
	int healthOverlayLastHitTime;
	float healthOverlayOldHealth;
	int healthOverlayPulseIndex;
	int proneBlockedEndTime;
	int lastStance;
	int lastStanceChangeTime;
	int lastStanceFlashTime;
	int voiceTime;
	unsigned int weaponSelect;
	int weaponSelectTime;
	unsigned int weaponLatestPrimaryIdx;
	int prevViewmodelWeapon;
	int equippedOffHand;
	viewDamage_t viewDamage[8];
	int damageTime;
	float damageX;
	float damageY;
	float damageValue;
	float viewFade;
	int weapIdleTime;
	int nomarks;
	int v_dmg_time;
	float v_dmg_pitch;
	float v_dmg_roll;
	float fBobCycle;
	float xyspeed;
	float kickAVel[3];
	float kickAngles[3];
	float offsetAngles[3];
	float gunPitch;
	float gunYaw;
	float gunXOfs;
	float gunYOfs;
	float gunZOfs;
	float vGunOffset[3];
	float vGunSpeed[3];
	float viewModelAxis[4][3];
	float rumbleScale;
	float compassNorthYaw;
	float compassNorth[2];
	Material* compassMapMaterial;
	float compassMapUpperLeft[2];
	float compassMapWorldSize[2];
	int compassFadeTime;
	int healthFadeTime;
	int ammoFadeTime;
	int stanceFadeTime;
	int sprintFadeTime;
	int offhandFadeTime;
	int offhandFlashTime;
	shellshock_t shellshock;
	$F6DFD6D87F75480A1EF1906639406DF5 testShock;
	int holdBreathTime;
	int holdBreathInTime;
	int holdBreathDelay;
	float holdBreathFrac;
	float radarProgress;		// correct offset
	float selectedLocation[2];
	SprintState sprintStates;	// 5 ints

	//int packetAnalysisFrameCount;
	//char bitsSent[100][13];
	//int entBitsUsed[10][18];
	//int numEntsSent[10][18];
	//int numEntFields[10][18]; ?? // 7 inbetween selectedLocation and bgs
	//int numSnapshots;
	//int adsViewErrorDone;
	//int inKillCam;

	int _unk01;
	int _unk02;

	bgs_t bgs;	// first name root
	cpose_t viewModelPose;
	visionSetVars_t visionSetPreLoaded[4];
	char visionSetPreLoadedName[4][64];
	visionSetVars_t visionSetFrom[2];
	visionSetVars_t visionSetTo[2];
	visionSetVars_t visionSetCurrent[2];
	visionSetLerpData_t visionSetLerpData[2];
	char visionNameNaked[64];
	char visionNameNight[64];
	int extraButtons;
	int lastActionSlotTime;
	bool playerTeleported;
	int stepViewStart;
	float stepViewChange;
	$BE9F66374A020A9809EEAF403416A176 lastFrame;
	hudElemSoundInfo_t hudElemSound[32];
	int vehicleFrame;
}; // should be right

struct trigger_info_t
{
	unsigned __int16 entnum;
	unsigned __int16 otherEntnum;
	int useCount;
	int otherUseCount;
};

struct com_parse_mark_t
{
	int lines;
	const char* text;
	int ungetToken;
	int backup_lines;
	const char* backup_text;
};

struct cached_tag_mat_t
{
	int time;
	int entnum;
	unsigned __int16 name;
	float tagMat[4][3];
};

struct level_locals_t
{
	gclient_s* clients;
	gentity_s* gentities;
	int gentitySize;
	int num_entities;
	gentity_s* firstFreeEnt;
	gentity_s* lastFreeEnt;
	int logFile;
	int initializing;
	int clientIsSpawning;
	objective_t objectives[16];
	int maxclients;
	int framenum;
	int time;
	int previousTime;
	int frametime;
	int startTime;
	int teamScores[4];
	int lastTeammateHealthTime;
	int bUpdateScoresForIntermission;
	bool teamHasRadar[4];
	int manualNameChange;
	int numConnectedClients;
	int sortedClients[64];
	char voteString[1024];
	char voteDisplayString[1024];
	int voteTime;
	int voteExecuteTime;
	int voteYes;
	int voteNo;
	int numVotingClients;
	SpawnVar spawnVar;
	int savepersist;
	EntHandle droppedWeaponCue[32];
	float fFogOpaqueDist;
	float fFogOpaqueDistSqrd;
	int remapCount;
	int currentPlayerClone;
	trigger_info_t pendingTriggerList[256];
	trigger_info_t currentTriggerList[256];
	int pendingTriggerListSize;
	int currentTriggerListSize;
	int finished;
	int bPlayerIgnoreRadiusDamage;
	int bPlayerIgnoreRadiusDamageLatched;
	int registerWeapons;
	int bRegisterItems;
	int currentEntityThink;
	int openScriptIOFileHandles[1];
	char* openScriptIOFileBuffers[1];
	com_parse_mark_t currentScriptIOLineMark[1];
	cached_tag_mat_t cachedTagMat;
	int scriptPrintChannel;
	float compassMapUpperLeft[2];
	float compassMapWorldSize[2];
	float compassNorth[2];
	scr_vehicle_s* vehicles;
};
typedef struct
{
	short UNKNOW;
	short active;
	short j_spine4;
	short j_helmet;
	short j_head;
	short UNKNOW_2;
	short allies;
	short axis;
	short bad_path;
	short begin_firing;
	short cancel_location;
	short confirm_location;
	short crouch;
	short current;
	short damage;
	short dead;
	short death;
	short detonate;
	short direct;
	short dlight;
	short done;
	short empty;
	short end_firing;
	short entity;
	short explode;
	short failed;
	short fraction;
	short free;
	short goal;
	short goal_changed;
	short goal_yaw;
	short grenade;
	short grenade_danger;
	short grenade_fire;
	short grenade_pullback;
	short info_notnull;
	short invisible;
	short key1;
	short key2;
	short killanimscript;
	short left;
	short light;
	short movedone;
	short noclass;
	short none;
	short normal;
	char   z_crap[4];
	short projectile_impact;
	short prone;
	short right;
	short reload;
	short reload_start;
	short rocket;
	short rotatedone;
	short script_brushmodel;
	short script_model;
	short script_origin;
	short snd_enveffectsprio_level;
	short snd_enveffectsprio_shellshock;
	short snd_channelvolprio_holdbreath;
	short snd_channelvolprio_pain;
	short snd_channelvolprio_shellshock;
	short stand;
	short suppression;
	short suppression_end;
	short surfacetype;
	short tag_aim;
	short tag_aim_animated;
	short tag_brass;
	short tag_butt;
	short tag_clip;
	short tag_flash;
	short tag_flash_11;
	short tag_flash_2;
	short tag_flash_22;
	short tag_flash_3;
	short tag_fx;
	short tag_inhand;
	short tag_knife_attach;
	short tag_knife_fx;
	short tag_laser;
	short tag_origin;
	short tag_weapon;
	short tag_cg_entities;
	short tag_camera;
	short tag_weapon_right;
	short tag_gasmask;
	short tag_gasmask2;
	short tag_sync;
	short target_script_trigger;
	short tempEntity;
	short UNKNOW_3;
	short touch;
	short trigger;
	short trigger_use;
	short trigger_use_touch;
	short trigger_damage;
	short trigger_lookat;
	short truck_cam;
	short weapon_change;
	short weapon_fired;
	short worldspawn;
	short flashbang;
	short flash;
	short smoke;
	short night_vision_on;
	short night_vision_off;
	short MOD_UNKNOWN;
	short MOD_PISTOL_BULLET;
	short MOD_RIFLE_BULLET;
	short MOD_GRENADE;
	short MOD_GRENADE_SPLASH;
	short MOD_PROJECTILE;
	short MOD_PROJECTILE_SPLASH;
	short MOD_MELEE;
	short MOD_HEAD_SHOT;
	short MOD_CRUSH;
	short MOD_TELEFRAG;
	short MOD_FALLING;
	short MOD_SUICIDE;
	short MOD_TRIGGER_HURT;
	short MOD_EXPLOSIVE;
	short MOD_IMPACT;
	short script_vehicle;
	short script_vehicle_collision;
	short script_vehicle_collmap;
	short script_vehicle_corpse;
	short turret_fire;
	short turret_on_target;
	short turret_not_on_target;
	short turret_on_vistarget;
	short turret_no_vis;
	short turret_rotate_stopped;
	short turret_deactivate;
	short turretstatechange;
	short turretownerchange;
	short reached_end_node;
	short reached_wait_node;
	short reached_wait_speed;
	short near_goal;
	short veh_collision;
	short veh_predictedcollision;
	short auto_change;
	short back_low;
	short back_mid;
	short back_up;
	short begin;
	short call_vote;
	short freelook;
	short head;
	short intermission;
	short j_head2;
	short manual_change;
	short menuresponse;
	short neck;
	short pelvis;
	short pistol;
	short plane_waypoint;
	short playing;
	short spectator;
	short vote;
	short sprint_begin;
	short sprint_end;
	short tag_driver;
	short tag_passenger;
	short tag_gunner;
	short tag_wheel_front_left;
	short tag_wheel_front_right;
	short tag_wheel_back_left;
	short tag_wheel_back_right;
	short tag_wheel_middle_left;
	short tag_wheel_middle_righ;
	short tag_detach;
	short tag_popout;
	short tag_body;
	short tag_turret;
	short tag_turret_base;
	short tag_barrel;
	short tag_engine_left;
	short tag_engine_right;
	short front_left;
	short front_right;
	short back_left;
	short back_right;
	short tag_gunner_pov;

}RE_Tags_t;//0x1406E90  size:174(DEZ.372)
struct GfxCachedShaderText
{
	const char* name;
	const char* text;
	int textSize;
};

struct MaterialString
{
	const char* string;
	unsigned int hash;
};

struct MaterialStateMapRule
{
	unsigned int stateBitsMask[2];
	unsigned int stateBitsValue[2];
	unsigned int stateBitsSet[2];
	unsigned int stateBitsClear[2];
};

struct MaterialStateMapRuleSet
{
	int ruleCount;
	MaterialStateMapRule rules[1];
};

struct MaterialStateMap
{
	const char* name;
	MaterialStateMapRuleSet* ruleSet[10];
};

struct MaterialInfoRaw
{
	unsigned int nameOffset;
	unsigned int refImageNameOffset;
	char gameFlags;
	char sortKey;
	char textureAtlasRowCount;
	char textureAtlasColumnCount;
	float maxDeformMove;
	char deformFlags;
	char usage;
	unsigned __int16 toolFlags;
	unsigned int locale;
	unsigned __int16 autoTexScaleWidth;
	unsigned __int16 autoTexScaleHeight;
	float tessSize;
	int surfaceFlags;
	int contents;
};

struct MaterialRaw
{
	MaterialInfoRaw info;
	unsigned int refStateBits[2];
	unsigned __int16 textureCount;
	unsigned __int16 constantCount;
	unsigned int techSetNameOffset;
	unsigned int textureTableOffset;
	unsigned int constantTableOffset;
};

struct MaterialLoadGlob
{
	unsigned int cachedShaderCount;
	GfxCachedShaderText* cachedShaderText;
	unsigned int vertexDeclCount;
	MaterialVertexDeclaration vertexDeclHashTable[32];
	unsigned int literalCount;
	float literalTable[16][4];
	unsigned int stringCount;
	MaterialString stringHashTable[64];
	unsigned int vertexShaderCount;
	MaterialVertexShader* vertexShaderHashTable[2][2048];
	unsigned int pixelShaderCount;
	MaterialPixelShader* pixelShaderHashTable[2][2048];
	unsigned int stateMapCount;
	MaterialStateMap* stateMapHashTable[32];
	unsigned int techniqueCount;
	MaterialTechnique* techniqueHashTable[2][4096];
	MaterialRaw* sortMtlRaw;
};

struct GfxDynamicIndices
{
	volatile int used;
	int total;
	unsigned __int16* indices;
};

struct GfxIndexBufferState
{
	volatile int used;
	int total;
	//IDirect3DIndexBuffer9* buffer;
	unsigned __int16* indices;
};

struct GfxPackedVertexNormal
{
	PackedUnitVec normal;
	PackedUnitVec tangent;
};

struct __declspec(align(4)) GfxBuffers
{
	GfxDynamicIndices smodelCache;
	//IDirect3DVertexBuffer9* smodelCacheVb;
	GfxIndexBufferState preTessIndexBufferPool[2];
	GfxIndexBufferState* preTessIndexBuffer;
	int preTessBufferFrame;
	GfxIndexBufferState dynamicIndexBufferPool[1];
	GfxIndexBufferState* dynamicIndexBuffer;
	GfxVertexBufferState skinnedCacheVbPool[2];
	char* skinnedCacheLockAddr;
	GfxVertexBufferState dynamicVertexBufferPool[1];
	GfxVertexBufferState* dynamicVertexBuffer;
	//IDirect3DVertexBuffer9* particleCloudVertexBuffer;
	//IDirect3DIndexBuffer9* particleCloudIndexBuffer;
	int dynamicBufferFrame;
	GfxPackedVertexNormal skinnedCacheNormals[2][147456];
	GfxPackedVertexNormal* skinnedCacheNormalsAddr;
	GfxPackedVertexNormal* oldSkinnedCacheNormalsAddr;
	unsigned int skinnedCacheNormalsFrameCount;
	bool fastSkin;
	bool skinCache;
};

struct GfxVisibleLight
{
	int drawSurfCount;
	GfxDrawSurf drawSurfs[1024];
};

struct GfxShadowCookie
{
	DpvsPlane planes[5];
	volatile int drawSurfCount;
	GfxDrawSurf drawSurfs[256];
};

struct GfxSkinnedXModelSurfs
{
	void* firstSurf;
};

struct GfxSceneEntityCull
{
	volatile unsigned int state;
	float mins[3];
	float maxs[3];
	char lods[32];
	GfxSkinnedXModelSurfs skinnedSurfs;
};

union GfxSceneEntityInfo
{
	cpose_t* pose;
	unsigned __int16* cachedLightingHandle;
};

struct XAnimParent
{
	unsigned __int16 flags;
	unsigned __int16 children;
};

union $2714E77E76DE9429E851020801EAFDE5
{
	XAnimParts* parts;
	XAnimParent animParent;
};

struct XAnimEntry
{
	unsigned __int16 numAnims;
	unsigned __int16 parent;
	$2714E77E76DE9429E851020801EAFDE5 ___u2;
};

struct XAnim_s
{
	const char* debugName;
	unsigned int size;
	const char** debugAnimNames;
	XAnimEntry entries[1];
};

struct __declspec(align(4)) XAnimTree_s
{
	XAnim_s* anims;
	int info_usage;
	volatile int calcRefCount;
	volatile int modifyRefCount;
	unsigned __int16 children;
};

struct DSkelPartBits
{
	int anim[4];
	int control[4];
	int skel[4];
};

struct DSkel
{
	DSkelPartBits partBits;
	int timeStamp;
	DObjAnimMat* mat;
};

struct DObj_s
{
	XAnimTree_s* tree;
	unsigned __int16 duplicateParts;
	unsigned __int16 entnum;
	char duplicatePartsSize;
	char numModels;
	char numBones;
	unsigned int ignoreCollision;
	volatile int locked;
	DSkel skel;
	float radius;
	unsigned int hidePartBits[4];
	XModel** models;
};

struct __declspec(align(4)) GfxSceneEntity
{
	float lightingOrigin[3];
	GfxScaledPlacement placement;
	GfxSceneEntityCull cull;
	unsigned __int16 gfxEntIndex;
	unsigned __int16 entnum;
	DObj_s* obj;
	GfxSceneEntityInfo info;
	char reflectionProbeIndex;
};

struct __declspec(align(4)) GfxSceneModel
{
	XModelDrawInfo info;
	XModel* model;
	DObj_s* obj;
	GfxScaledPlacement placement;
	unsigned __int16 gfxEntIndex;
	unsigned __int16 entnum;
	float radius;
	unsigned __int16* cachedLightingHandle;
	float lightingOrigin[3];
	char reflectionProbeIndex;
};

struct __declspec(align(4)) GfxSceneBrush
{
	BModelDrawInfo info;
	unsigned __int16 entnum;
	GfxBrushModel* bmodel;
	GfxPlacement placement;
	char reflectionProbeIndex;
};

union GfxEntCellRefInfo
{
	float radius;
	GfxBrushModel* bmodel;
};

struct GfxSceneDpvs
{
	unsigned int localClientNum;
	char* entVisData[7];
	unsigned __int16* sceneXModelIndex;
	unsigned __int16* sceneDObjIndex;
	GfxEntCellRefInfo* entInfo[4];
};

#pragma warning( push )
#pragma warning( disable : 4324 )
struct __declspec(align(64)) GfxScene
{
	GfxDrawSurf bspDrawSurfs[8192];
	GfxDrawSurf smodelDrawSurfsLight[8192];
	GfxDrawSurf entDrawSurfsLight[8192];
	GfxDrawSurf bspDrawSurfsDecal[512];
	GfxDrawSurf smodelDrawSurfsDecal[512];
	GfxDrawSurf entDrawSurfsDecal[512];
	GfxDrawSurf bspDrawSurfsEmissive[8192];
	GfxDrawSurf smodelDrawSurfsEmissive[8192];
	GfxDrawSurf entDrawSurfsEmissive[8192];
	GfxDrawSurf fxDrawSurfsEmissive[8192];
	GfxDrawSurf fxDrawSurfsEmissiveAuto[8192];
	GfxDrawSurf fxDrawSurfsEmissiveDecal[8192];
	GfxDrawSurf bspSunShadowDrawSurfs0[4096];
	GfxDrawSurf smodelSunShadowDrawSurfs0[4096];
	GfxDrawSurf entSunShadowDrawSurfs0[4096];
	GfxDrawSurf bspSunShadowDrawSurfs1[8192];
	GfxDrawSurf smodelSunShadowDrawSurfs1[8192];
	GfxDrawSurf entSunShadowDrawSurfs1[8192];
	GfxDrawSurf bspSpotShadowDrawSurfs0[256];
	GfxDrawSurf smodelSpotShadowDrawSurfs0[256];
	GfxDrawSurf entSpotShadowDrawSurfs0[512];
	GfxDrawSurf bspSpotShadowDrawSurfs1[256];
	GfxDrawSurf smodelSpotShadowDrawSurfs1[256];
	GfxDrawSurf entSpotShadowDrawSurfs1[512];
	GfxDrawSurf bspSpotShadowDrawSurfs2[256];
	GfxDrawSurf smodelSpotShadowDrawSurfs2[256];
	GfxDrawSurf entSpotShadowDrawSurfs2[512];
	GfxDrawSurf bspSpotShadowDrawSurfs3[256];
	GfxDrawSurf smodelSpotShadowDrawSurfs3[256];
	GfxDrawSurf entSpotShadowDrawSurfs3[512];
	GfxDrawSurf shadowDrawSurfs[512];
	unsigned int shadowableLightIsUsed[32];
	int maxDrawSurfCount[34];
	volatile int drawSurfCount[34];
	GfxDrawSurf* drawSurfs[34];
	GfxDrawSurf fxDrawSurfsLight[8192];
	GfxDrawSurf fxDrawSurfsLightAuto[8192];
	GfxDrawSurf fxDrawSurfsLightDecal[8192];
	GfxSceneDef def;
	int addedLightCount;
	GfxLight addedLight[32];
	bool isAddedLightCulled[32];
	float dynamicSpotLightNearPlaneOffset;
	GfxVisibleLight visLight[4];
	GfxVisibleLight visLightShadow[1];
	GfxShadowCookie cookie[24];
	unsigned int* entOverflowedDrawBuf;
	volatile int sceneDObjCount;
	GfxSceneEntity sceneDObj[512];
	char sceneDObjVisData[7][512];
	volatile int sceneModelCount;
	GfxSceneModel sceneModel[1024];
	char sceneModelVisData[7][1024];
	volatile int sceneBrushCount;
	GfxSceneBrush sceneBrush[512];
	char sceneBrushVisData[3][512];
	unsigned int sceneDynModelCount;
	unsigned int sceneDynBrushCount;
	DpvsPlane shadowFarPlane[2];
	DpvsPlane shadowNearPlane[2];
	GfxSceneDpvs dpvs;
};
#pragma warning( pop )

struct clSnapshot_t
{
	int valid;
	int snapFlags;// SNAPFLAG_RATE_DELAYED, etc
	int serverTime; // server time the message is valid for (in msec)
	int messageNum;
	int deltaNum;
	int ping;
	int cmdNum;
	playerState_s ps; // complete information about the current player at this time
	int numEntities;
	int numClients;
	int parseEntitiesNum;
	int parseClientsNum;
	int serverCommandNum; //usercmd count
};

struct gameState_t
{
	int stringOffsets[2442];
	char stringData[131072];
	int dataCount;
};

enum class StanceState
{
	CL_STANCE_STAND = 0x0,
	CL_STANCE_CROUCH = 0x1,
	CL_STANCE_PRONE = 0x2,
};

struct ClientArchiveData
{
	int serverTime;
	float origin[3];
	float velocity[3];
	int bobCycle;
	int movementDir;
	float viewangles[3];
};

struct outPacket_t
{
	int p_cmdNumber;		// cl.cmdNumber when packet was sent
	int p_serverTime;		// usercmd->serverTime when packet was sent
	int p_realtime;			// cls.realtime when packet was sent
};
constexpr auto CMD_MASK = 0x7F;
struct clientActive_t
{
	bool usingAds;
	int timeoutcount;
	clSnapshot_t snap;
	bool alwaysFalse;
	int serverTime;
	int oldServerTime;			// to prevent time from flowing bakcwards
	int oldFrameServerTime;		// to check tournament restarts
	int serverTimeDelta;		// cl.serverTime = cls.realtime + cl.serverTimeDelta
	int oldSnapServerTime;
	int extrapolatedSnapshot;	// set if any cgame frame has been forced to extrapolate
	int newSnapshots;			// set on parse of any valid packet
	gameState_t gameState;		// configstrings
	char mapname[64];			// extracted from CS_SERVERINFO
	int parseEntitiesNum;		// index (not anded off) into cl_parse_entities[]
	int parseClientsNum;
	int mouseDx[2];				// added to by mouse events
	int mouseDy[2];				// added to by mouse events
	int mouseIndex;
	bool stanceHeld;
	StanceState stance;
	StanceState stancePosition;
	int stanceTime;
	int cgameUserCmdWeapon;
	int cgameUserCmdOffHandIndex;
	float cgameFOVSensitivityScale;
	float cgameMaxPitchSpeed;
	float cgameMaxYawSpeed;
	float cgameKickAngles[3];
	float cgameOrigin[3];
	float cgameVelocity[3];
	float cgameViewangles[3];
	int cgameBobCycle;
	int cgameMovementDir;
	int cgameExtraButtons;
	int cgamePredictedDataServerTime;
	float viewangles[3];
	int serverId;
	int skelTimeStamp;
	volatile int skelMemPos;
	char skelMemory[262144];
	char* skelMemoryStart;
	bool allowedAllocSkel;

	// cmds[cmdNumber] is the predicted command, [cmdNumber-1] is the last
	// properly generated command
	__declspec(align(4)) usercmd_s cmds[128];
	int cmdNumber;
	ClientArchiveData clientArchive[256];
	int clientArchiveIndex;
	outPacket_t outPackets[32];
	clSnapshot_t snapshots[32];
	entityState_s entityBaselines[1024]; // for delta compression when not in previous frame
	entityState_s parseEntities[2048];
	clientState_s parseClients[2048];
	int corruptedTranslationFile;
	char translationVersion[256];
	float vehicleViewYaw;
	float vehicleViewPitch;
};
class CInput
{
public:
	usercmd_s cmds[128]; //0x0000
	int currentCmdNum; //0x1000

	usercmd_s* GetUserCmd(int cmdNum)
	{
		return &cmds[cmdNum & CMD_MASK];
	}
};//Size=0x2E44
typedef enum
{
	UNKNOW,
	CONSOLE,
	KILLPOSITION,
	CENTERED,

} prints_t;
#pragma warning( push )
#pragma warning( disable : 4324 )
struct __declspec(align(128)) r_global_permanent_t
{
	Material* sortedMaterials[2048];
	int needSortMaterials;
	int materialCount;
	GfxImage* whiteImage;
	GfxImage* blackImage;
	GfxImage* blackImage3D;
	GfxImage* blackImageCube;
	GfxImage* grayImage;
	GfxImage* identityNormalMapImage;
	GfxImage* specularityImage;
	GfxImage* outdoorImage;
	GfxImage* pixelCostColorCodeImage;
	GfxLightDef* dlightDef;
	Material* defaultMaterial;
	Material* whiteMaterial;
	Material* additiveMaterial;
	Material* pointMaterial;
	Material* lineMaterial;
	Material* lineMaterialNoDepth;
	Material* clearAlphaStencilMaterial;
	Material* shadowClearMaterial;
	Material* shadowCookieOverlayMaterial;
	Material* shadowCookieBlurMaterial;
	Material* shadowCasterMaterial;
	Material* shadowOverlayMaterial;
	Material* depthPrepassMaterial;
	Material* glareBlindMaterial;
	Material* pixelCostAddDepthAlwaysMaterial;
	Material* pixelCostAddDepthDisableMaterial;
	Material* pixelCostAddDepthEqualMaterial;
	Material* pixelCostAddDepthLessMaterial;
	Material* pixelCostAddDepthWriteMaterial;
	Material* pixelCostAddNoDepthWriteMaterial;
	Material* pixelCostColorCodeMaterial;
	Material* stencilShadowMaterial;
	Material* stencilDisplayMaterial;
	Material* floatZDisplayMaterial;
	Material* colorChannelMixerMaterial;
	Material* frameColorDebugMaterial;
	Material* frameAlphaDebugMaterial;
	GfxImage* rawImage;
	GfxWorld* world;
	Material* feedbackReplaceMaterial;
	Material* feedbackBlendMaterial;
	Material* feedbackFilmBlendMaterial;
	Material* cinematicMaterial;
	Material* dofDownsampleMaterial;
	Material* dofNearCocMaterial;
	Material* smallBlurMaterial;
	Material* postFxDofMaterial;
	Material* postFxDofColorMaterial;
	Material* postFxColorMaterial;
	Material* postFxMaterial;
	Material* symmetricFilterMaterial[8];
	Material* shellShockBlurredMaterial;
	Material* shellShockFlashedMaterial;
	Material* glowConsistentSetupMaterial;
	Material* glowApplyBloomMaterial;
	int savedScreenTimes[4];
};
#pragma warning( pop )

struct Image_MemUsage
{
	int total;
	int lightmap;
	int minspec;
};

struct trStatistics_t
{
	int c_indexes;
	int c_fxIndexes;
	int c_viewIndexes;
	int c_shadowIndexes;
	int c_vertexes;
	int c_batches;
	float dc;
	Image_MemUsage c_imageUsage;
};

struct GfxLodRamp
{
	float scale;
	float bias;
};

struct __declspec(align(4)) GfxLodParms
{
	float origin[3];
	GfxLodRamp ramp[2];
};

#pragma warning( push )
#pragma warning( disable : 4324 )
struct __declspec(align(8)) r_globals_t
{
	GfxViewParms identityViewParms;
	bool inFrame;
	bool registered;
	bool forbidDelayLoadImages;
	bool ignorePrecacheErrors;
	float viewOrg[3];
	float viewDir[3];
	unsigned int frontEndFrameCount;
	int totalImageMemory;
	Material* materialHashTable[2048];
	GfxFog fogSettings[5];
	int fogIndex;
	GfxColor color_axis;
	GfxColor color_allies;
	int team;
	trStatistics_t* stats;
	GfxLodParms lodParms;
	GfxLodParms correctedLodParms;
	bool hasAnyImageOverrides;
	bool useSunLightOverride;
	bool useSunDirOverride;
	bool useSunDirLerp;
	float sunLightOverride[3];
	float sunDirOverride[3];
	float sunDirOverrideTarget[3];
	int sunDirLerpBeginTime;
	int sunDirLerpEndTime;
	GfxScaledPlacement identityPlacement;
	GfxViewParms* debugViewParms;
	int endTime;
	bool distortion;
	bool drawSModels;
	bool drawXModels;
	bool drawBModels;
	const char* codeImageNames[27];
	unsigned int viewInfoCount;
	int sunShadowFull;
	float sunShadowmapScale;
	float sunShadowmapScaleNum;
	unsigned int sunShadowSize;
	float sunShadowPartitionRatio;
	int drawSunShadow;
	int skinnedCacheReachedThreshold;
	float waterFloatTime;
};
#pragma warning( pop )

struct dynBrush_t
{
	int cmBrushIndex;
	cbrush_t* cmBrush; // ptr to the clipmap brush
	cplane_s* cmPlane[6]; // ptr's to the clipmap brush-planes (axialplanes)
	cLeaf_t* cmLeaf; // ptr to the clipmap brush-leaf
};

struct dynBrushesArray_t
{
	dynBrush_t brushes[16];
};


struct dynBrushModel_t
{
	int cmodelIndex;
	cmodel_t* cmodel;
	int entityIndex;
	gentity_s* ent;
	int radBrushIndexForDyn;
	float originalOrigin[3];
};

struct dynBrushModelsArray_t
{
	bool initiated;
	int mapped_bmodels;
	dynBrushModel_t brushes[16];
};

struct brushmodelEnt_t
{
	int cmSubmodelIndex;
	cmodel_t* cmSubmodel;
	float cmSubmodelOrigin[3];
	int cmBrushIndex;
	cbrush_t* cmBrush;
	std::vector<std::string> brushSides;
};

struct boundingBox_t
{
	int numPoints;
	//glm::vec3 points[3];
	//glm::vec3 mins;
	//glm::vec3 maxs;
	cbrush_t box;
	bool keyFlagInsert;
	bool keyFlagReset;
	bool isBoxValid;
	bool wasReset;
};

struct circleZone_t
{
	//glm::vec3 zoneCoords[4];
};

struct axialPlane_t
{
	//glm::vec3 plane;
	float dist;
};

enum GUI_MENUS
{
	DEMO = 0,
	DEVGUI = 1,
	EMPTY2 = 2,
	CHANGELOG = 3
};

struct gui_menus_t
{
	bool menustate;
	bool mouse_ignores_menustate;
	bool was_open;
	bool hk_is_clicked;
	bool hk_is_down;
	bool one_time_init;
	bool got_layout_from_menu;
	float position[2];
	float size[2];
	int horzAlign;
	int vertAlign;
};

struct gui_t
{
	bool imgui_initialized;
	bool dvars_initialized;
	bool any_menus_open;
	//gui_menus_t menus[GGUI_MENU_COUNT];
};

struct switch_material_t
{
	bool switch_material;
	bool switch_technique;
	bool switch_technique_type;

	Material* current_material;
	MaterialTechnique* current_technique;

	Material* material;
	MaterialTechnique* technique;

	MaterialTechniqueType technique_type;
};
struct cg_t
{
	int clientNum; //0x0000
	char pad_0x0004[0x1C]; //0x0004
	snapshot_s* pSnap; //0x0020
	snapshot_s* pNextSnap; //0x0024
	char pad_0x0028[0x7C]; //0x0028
	unsigned char isOnGround; //0x00A4
	char pad_0x00A5[0x6B]; //0x00A5
	int spectating_clientNum; //0x0110
	char pad_0x0114[0x14]; //0x0114
	float ads_animation_state; //0x0128
	char pad_0x012C[0x29C]; //0x012C
	int offhandAmmo; //0x03C8
	char pad_0x03CC[0x40]; //0x03CC
	int primaryAmmo; //0x040C
	char pad_0x0410[0x30]; //0x0410

}; //Size=0x0580
enum ShockViewTypes
{
	SHELLSHOCK_VIEWTYPE_BLURRED = 0x0,
	SHELLSHOCK_VIEWTYPE_FLASHED = 0x1,
	SHELLSHOCK_VIEWTYPE_NONE = 0x2,
};

struct $59BC949CAD00C1270469FCBABD8F5215
{
	int blurredFadeTime;
	int blurredEffectTime;
	int flashWhiteFadeTime;
	int flashShotFadeTime;
	ShockViewTypes type;
};
struct $B32C35443884083D3CC13DCD5C8D7874
{
	int fadeTime;
	float kickRate;
	float kickRadius;
};
struct $6C506745AE6A28CCD0D2A06866E76873
{
	bool affect;
	char loop[64];
	char loopSilent[64];
	char end[64];
	char endAbort[64];
	int fadeInTime;
	int fadeOutTime;
	float drylevel;
	float wetlevel;
	char roomtype[16];
	float channelvolume[64];
	int modEndDelay;
	int loopFadeTime;
	int loopEndDelay;
};
struct $52C58A71BD00586BA7DCB8AF66236D72
{
	bool affect;
	int fadeTime;
	float mouseSensitivity;
	float maxPitchSpeed;
	float maxYawSpeed;
};
struct $1BC6F870A2CCF543567EAA1D445E0BBA
{
	bool affect;
};
struct __declspec(align(4)) shellshock_parms_t
{
	$59BC949CAD00C1270469FCBABD8F5215 screenBlend;
	$B32C35443884083D3CC13DCD5C8D7874 view;
	$6C506745AE6A28CCD0D2A06866E76873 sound;
	$52C58A71BD00586BA7DCB8AF66236D72 lookControl;
	$1BC6F870A2CCF543567EAA1D445E0BBA movement;
};

struct cgs_t
{
	int viewX;
	int viewY;
	int viewWidth;
	int viewHeight;
	float viewAspect;
	int serverCommandSequence;
	int processedSnapshotNum;
	int localServer;
	char gametype[32];
	char szHostName[256];
	int maxclients;
	char mapname[64];
	int gameEndTime;
	int voteTime;
	int voteYes;
	int voteNo;
	char voteString[256];
	XModel* gameModels[512];
	FxEffectDef* fxs[100];
	FxEffectDef* smokeGrenadeFx;
	shellshock_parms_t holdBreathParams;
	char teamChatMsgs[8][160];
	int teamChatMsgTimes[8];
	int teamChatPos;
	int teamLastChatPos;
	float compassWidth;
	float compassHeight;
	float compassY;
	clientInfo_t corpseinfo[8];
};
//struct cg_t
//{
//	int clientNum; //0x0000
//	char pad_0x0004[0x1C]; //0x0004
//	snapshot_s* pSnap; //0x0020
//	snapshot_s* pNextSnap; //0x0024
//	char pad_0x0028[0x7C]; //0x0028
//	unsigned char isOnGround; //0x00A4
//	char pad_0x00A5[0x6B]; //0x00A5
//	int spectating_clientNum; //0x0110
//	char pad_0x0114[0x14]; //0x0114
//	float ads_animation_state; //0x0128
//	char pad_0x012C[0x29C]; //0x012C
//	int offhandAmmo; //0x03C8
//	char pad_0x03CC[0x40]; //0x03CC
//	int primaryAmmo; //0x040C
//	char pad_0x0410[0x30]; //0x0410
//
//}; //Size=0x0580
#ifdef __cplusplus
}
#endif
class Movement
{
public:
	bool forward; //0x0000
	char pad_0001[3]; //0x0001
	char N00000077[2]; //0x0004
	char pad_0006[13]; //0x0006
	int8_t N00000079; //0x0013
	bool back; //0x0014
	char pad_0015[59]; //0x0015
	bool left; //0x0050
	char pad_0051[19]; //0x0051
	bool right; //0x0064
	char pad_0065[39]; //0x0065
	bool adshold; //0x008C
	char pad_008D[19]; //0x008D
	bool jump; //0x00A0
	char pad_00A1[19]; //0x00A1
	bool lowerstance; //0x00B4
	char pad_00B5[19]; //0x00B5
	bool raisestance; //0x00C8
	char pad_00C9[39]; //0x00C9
	bool attack; //0x00F0
	char pad_00F1[19]; //0x00F1
	bool sprint; //0x0104
	char pad_0105[19]; //0x0105
	bool nade; //0x0118
	char pad_0119[39]; //0x0119
	bool knife; //0x0140
	char pad_0141[79]; //0x0141
	bool leanleft; //0x0190
	char pad_0191[19]; //0x0191
	bool leanright; //0x01A4
	char pad_01A5[287]; //0x01A5

}; //Size: 0x02C4
static_assert(sizeof(Movement) == 0x2C4);
struct DirInput
{
	char move;
	char strafe;
};
enum $B87C0110D100A68234FECCEB9075A41E //channels
{
	CON_CHANNEL_DONT_FILTER = 0,
	CON_CHANNEL_ERROR = 1,
	CON_CHANNEL_GAMENOTIFY = 2,
	CON_CHANNEL_BOLDGAME = 3,
	CON_CHANNEL_SUBTITLE = 4,
	CON_CHANNEL_OBITUARY = 5,
	CON_CHANNEL_LOGFILEONLY = 6,
	CON_CHANNEL_CONSOLEONLY = 7,
	CON_CHANNEL_GFX = 8,
	CON_CHANNEL_SOUND = 9,
	CON_CHANNEL_FILES = 0xA,
	CON_CHANNEL_DEVGUI = 0xB,
	CON_CHANNEL_PROFILE = 0xC,
	CON_CHANNEL_UI = 0xD,
	CON_CHANNEL_CLIENT = 0xE,
	CON_CHANNEL_SERVER = 0xF,
	CON_CHANNEL_SYSTEM = 10,
	CON_CHANNEL_PLAYERWEAP = 11,
	CON_CHANNEL_AI = 12,
	CON_CHANNEL_ANIM = 13,
	CON_CHANNEL_PHYS = 14,
	CON_CHANNEL_FX = 15,
	CON_CHANNEL_LEADERBOARDS = 16,
	CON_CHANNEL_PARSERSCRIPT = 17,
	CON_CHANNEL_SCRIPT = 18,
	CON_BUILTIN_CHANNEL_COUNT = 19
};
enum ERR_DROP
{
	ERR_FATAL = 0,
	ERR_DROP = 1,
	ERR_SERVERDISCONNECT = 2,
	ERR_DISCONNECT = 3,
	ERR_SCRIPT = 4,
	ERR_SCRIPT_DROP = 5,
	ERR_LOCALIZATION = 6,
	ERR_MAPLOADERRORSUMMARY = 7
};
struct PlayerNames_t
{
	char name[46];
};
#endif