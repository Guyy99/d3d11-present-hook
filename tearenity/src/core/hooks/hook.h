#pragma once

#include "../renderer/renderer.h"


namespace hooks
{
	HRESULT __stdcall HkPresent(IDXGISwapChain* pSwapchain, UINT SyncInterval, UINT flags);
}

inline Renderer* renderer = new Renderer((uintptr_t)hooks::HkPresent);