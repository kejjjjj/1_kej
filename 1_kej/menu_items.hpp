#pragma once

#ifndef menuitems
#define menuitems

#include "pch.h"

using namespace cg;

inline itemDef_s*(*Menu_PostParse_f)(menuDef_t* menu);
itemDef_s* Menu_PostParse(menuDef_t* menu);


inline int(*UI_AddMenuList_f)(UiContext* dc, MenuList* menuList);
int UI_AddMenuList(UiContext* dc, MenuList* menuList);

char* GetExpressionResultString(int localClientNum, statement_s* statement);

struct menuinfo_s
{
	UiContext* context;
};
inline menuinfo_s menuInfo;

#endif