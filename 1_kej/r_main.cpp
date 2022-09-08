#include "pch.h"


LRESULT CALLBACK r::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {


	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) && GetKeyState(VK_END) == 1)
		return 1l;

	switch (uMsg) {
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		ImGui_ImplDX9_InvalidateDeviceObjects();
	}

	return oWndProc(hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall r::draw_func(IDirect3DDevice9* pDevice)
{
	R_ImGui(pDevice);

	return pEndScene(pDevice);
}
void __cdecl r::CG_DrawActive()
{
	Mod_DrawVelocity();
	

	return CG_DrawActive_f();
}