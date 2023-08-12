#include "hook.h"

HRESULT __stdcall hooks::HkPresent(IDXGISwapChain* pSwapchain, UINT SyncInterval, UINT flags)
{
	if (!renderer->init)
		renderer->InitD3DHook(pSwapchain);



	renderer->draw_line({ 0,0 }, { 1920,1080 }, { 1,0,0,1 });
	/*
	for (int i = 0; i < offsets::name_array_size; i++)
	{
		uintptr_t entity = SDK::get_player(i);
		ESP::draw_box(entity);
	}
	*/
	return renderer->ogPresentTramp(pSwapchain, SyncInterval, flags);
}
