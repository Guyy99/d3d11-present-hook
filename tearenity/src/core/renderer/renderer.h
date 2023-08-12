#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <iostream>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define safe_release(p) if (p) { p->Release(); p = nullptr; } 

#include "shadez.h"



#include "../math/vector.h"

#define VMT_PRESENT (UINT)IDXGISwapChainVMT::Present
#define PRESENT_STUB_SIZE 5
#define MAINVP 0

using namespace DirectX;

struct HandleData
{
	DWORD pid;
	HWND hWnd;
};
HWND FindMainWindow(DWORD dwPID);
BOOL CALLBACK EnumWindowsCallback(HWND hWnd, LPARAM lParam);

class Renderer
{
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwapchain = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11InputLayout* pVertexLayout = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11Buffer* pVertexBuffer = nullptr;
	ID3D11Buffer* pIndexBuffer = nullptr;
	ID3D11Buffer* pConstantBuffer = nullptr;

	UINT sWidth = 0, sHeight = 0;

	D3D11_VIEWPORT pViewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE]{ 0 };
	XMMATRIX mOrtho;

	struct ConstantBuffer
	{
		XMMATRIX mProjection;
	};

	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT4 color;
	};

	bool Hook(void* pSrc, void* pDst, size_t size);
	bool WriteMem(void* pDst, char* pBytes, size_t size);
	bool CompileShader(const char* szShader, const char* szEntrypoint, const char* szTarget, ID3D10Blob** pBlob);

	void normalize_vec2(vec2& point);

	using fnPresent = HRESULT(__stdcall*)(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
	fnPresent externalPresent = nullptr;
	




public:

	bool init = false;

	fnPresent ogPresentTramp = nullptr;

	bool HookPresent();
	bool InitD3DHook(IDXGISwapChain* pSwapchain);
	void CleanupD3D();

	void render_demo_triangle();
	void draw_line(vec2 p1, vec2 p2, color c);
	void draw_rect(vec2 p1, vec2 p2, vec2 p3, vec2 p4, color c);
	void draw_box(vec2 p1, vec2 p2, color c);

	Renderer(uintptr_t PresentFunction);

};

