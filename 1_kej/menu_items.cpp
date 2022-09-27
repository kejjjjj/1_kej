
#include "pch.h"

//
//only called when useFastFile is false
//
itemDef_s* Menu_PostParse(menuDef_t* menu)
{
	itemDef_s* item = Menu_PostParse_f(menu);
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "name: %s\n", menu->window.name);
	return item;
}

int UI_AddMenuList(UiContext* dc, MenuList* menuList)
{
	static UiContext* _dc;
	MenuList* _menuList;

	int count = UI_AddMenuList_f(dc, menuList);

	__asm
	{
		mov _dc, esi;
		mov menuList, eax;
	}

	menuInfo.context = _dc;
	return count;
}
char* GetExpressionResultString(int localClientNum, statement_s* statement)
{
	char* result;
	__asm {
		mov edx, localClientNum;
		mov ecx, statement;
		mov esi, 0x53F820;
		call esi;
		mov result, eax;
	}
	return result;
}