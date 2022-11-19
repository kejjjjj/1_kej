#include "pch.h"

bool r::R_Init()
{
	if (!cg::dx->device)
		return false;

	PVOID* vTable = *reinterpret_cast<PVOID**>(cg::dx->device);

	hook a;

	pEndScene = (endScene)vTable[42];
	
	if (a.install(&(PVOID&)pEndScene, draw_func) != S_OK) {
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "failed to hook endscene\n");
		return false;
	}
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "renderer successfully hooked\n");

	return true;
}
bool r::R_ImGui(IDirect3DDevice9* pDevice)
{
	if (ImGui::GetCurrentContext())
		return true;

	std::cout << "creating new imgui context!\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "creating new imgui context!\n");


	ImGui::CreateContext();

	const char* window_name = (cod4x_entry != NULL) ? "Call Of Duty 4 X" : "Call Of Duty 4";

	if (!ImGui_ImplWin32_Init(FindWindowA(NULL, window_name))) {
		fs::Log_Write(LOG_FATAL, "ImGui_ImplWin32_Init(%s) return false\n", window_name);
		return false;
	}

	if (!ImGui_ImplDX9_Init(pDevice)) {
		fs::Log_Write(LOG_FATAL, "ImGui_ImplDX9_Init() return false.. possibly null directx device\n");
		return false;
	}

	r::imagePairs.erase(r::imagePairs.begin(), r::imagePairs.end());
	r::imagePairs.clear();
	r::imagePairs.resize(0);

	r::imagePairs = fs::FS_CreatePairsForTextures();

	if (r::imagePairs.size() < 1) {
		fs::Log_Write(LOG_FATAL, "Failed to create image pairs (no images found in cod4\\1_kej\\images)\n");
		return false;
	}

	if (!r::CreateTextures(r::imagePairs)) {
		fs::Log_Write(LOG_FATAL, "Failed to create D3DX textures from images\n");
		return false;
	}

	if (!fs::FS_AllNecessaryImagesExist()) {
		fs::Log_Write(LOG_FATAL, "Stopping initialization due to missing image(s)\n");
		return false;
	}

	R_MenuStyle();

	return true;
}
LRESULT CALLBACK r::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {


	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return 1l;
	}

	switch (uMsg) {
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		r::should_draw_menu = false;
		std::cout << "calling R_RemoveInput() from WndProc() -> WM_Destroy\n";
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "destroying game window\n");
		R_RemoveInput(r::should_draw_menu);
		break;

	}

	return oWndProc(hWnd, uMsg, wParam, lParam);
}
void* r::CL_ShutdownRenderer()
{
	r::should_draw_menu = false;
	std::cout << "shutdown renderer!\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "shutting down renderer\n");

	if (ImGui::GetCurrentContext()) {

		if (tex_Z) {
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "Releasing texture '%s'\n", "tex_Z");

			tex_Z->Release();
			tex_Z = nullptr;
		}
		if (tex_noZ) {
			Com_Printf(CON_CHANNEL_CONSOLEONLY, "Releasing texture '%s'\n", "tex_noZ");

			tex_noZ->Release();
			tex_noZ = nullptr;
		}

		for (auto& i : r::imagePairs)
			if (i.second) {
				Com_Printf(CON_CHANNEL_CONSOLEONLY, "Releasing texture '%s'\n", i.first.c_str());
				i.second->Release();
				i.second = nullptr;
			}

		r::imagePairs.erase(r::imagePairs.begin(), r::imagePairs.end());
		r::imagePairs.clear();
		r::imagePairs.resize(0);



		Com_Printf(CON_CHANNEL_CONSOLEONLY, "also removing imgui context\n");
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

	}
	CL_ShutdownRenderer_f();

	return 0;
}
char r::R_RecoverLostDevice()
{
	if (!r::device_needs_reset && ImGui::GetCurrentContext()) {
		if (analyzer.isPreviewing()) {
			analyzer.setPreviewState(false);

			dvar_s* g_gravity = Dvar_FindMalleableVar("g_gravity");

			if (g_gravity) {
				g_gravity->latched.value = 800;
				g_gravity->current.value = 800;
			}

		}
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "R_RecoverLostDevice(): restoring input\n");
		r::device_needs_reset = true;
		r::should_draw_menu = false;
		r::R_RemoveInput(false);
		ImGui_ImplDX9_InvalidateDeviceObjects();
		std::cout << "R_RecoverLostDevice(): restoring input\n";
	}
	//if (ImGui::GetCurrentContext()) {
	//	ImGui_ImplDX9_InvalidateDeviceObjects();
	//	r::should_draw_menu = false;
	//	//std::cout << "calling R_RemoveInput() from R_RecoverLostDevice()\n";
	//	//R_RemoveInput(r::should_draw_menu);

	//}

	return R_RecoverLostDevice_f();
}

bool r::CreateTextures(std::vector<std::pair<std::string, LPDIRECT3DTEXTURE9>>& pair)
{
	WCHAR _imagepath[MAX_PATH];


	if (pair.size() < 1) {
		fs::Log_Write(LOG_ERROR, "Failed to create image pairs (no images found in cod4\\1_kej\\images)\n");

		std::cout << "no textures can be loaded due to no pairs\n";
		return false;
	}

	for (size_t i = 0; i < pair.size(); i++) {
		std::string curImage = fs::GetExePath() + "\\1_kej\\images\\" + pair[i].first;

		char imagepath[MAX_PATH]{};

		memcpy(imagepath, curImage.c_str(), curImage.size());

		MultiByteToWideChar(0, 0, imagepath, IM_ARRAYSIZE(imagepath), _imagepath, IM_ARRAYSIZE(imagepath));
		HRESULT result = D3DXCreateTextureFromFileW(cg::dx->device, _imagepath, &pair[i].second);

		if (result != S_OK) {
			std::wcout << _imagepath;
			std::cout << " failed with ";
			return ReturnErrorCode(result);
		}

		else {
			printf("[%s]: S_OK\n", curImage.c_str());
			fs::Log_Write(LOG_NONE, "[%s]: S_OK\n", curImage.c_str());
		}
	}
	return true;
}

bool r::ReturnErrorCode(HRESULT result)
{
	switch (result) {
	case D3DERR_NOTAVAILABLE:
		fs::Log_Write(LOG_ERROR, "CreateTextures(): failed with D3DERR_NOTAVAILABLE\n");
		std::cout << "D3DERR_NOTAVAILABLE\n";
		return true;
		break;
	case D3DERR_OUTOFVIDEOMEMORY:
		fs::Log_Write(LOG_ERROR, "CreateTextures(): failed with D3DERR_OUTOFVIDEOMEMORY\n");
		std::cout << "D3DERR_OUTOFVIDEOMEMORY\n";
		break;
	case D3DERR_INVALIDCALL:
		fs::Log_Write(LOG_ERROR, "CreateTextures(): failed with D3DERR_INVALIDCALL\n");
		std::cout << "D3DERR_INVALIDCALL\n";
		break;
	case D3DXERR_INVALIDDATA:
		fs::Log_Write(LOG_ERROR, "CreateTextures(): failed with D3DXERR_INVALIDDATA\n");
		std::cout << "D3DXERR_INVALIDDATA\n";
		break;
	case E_OUTOFMEMORY:
		fs::Log_Write(LOG_ERROR, "CreateTextures(): failed with E_OUTOFMEMORY\n");
		std::cout << "E_OUTOFMEMORY\n";
		break;
	default:
		fs::Log_Write(LOG_ERROR, "CreateTextures(): failed with no common return value (code %i)?\n", result);
		std::cout << "no common return value?\n";
		break;
	}
	return false;
}