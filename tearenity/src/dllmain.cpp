#include <stdio.h>
#include <stdlib.h>

#include "core/hooks/hook.h"


DWORD main(HMODULE hModule)
{
	if (renderer->HookPresent())
	{
		while (!GetAsyncKeyState(VK_F9)) Sleep(10);
	}

	renderer->CleanupD3D();

	Sleep(1000);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);
	if (fdwReason == DLL_PROCESS_ATTACH)
		if (const auto threadHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, hModule, 0, nullptr))
			CloseHandle(threadHandle);
	return TRUE;
}