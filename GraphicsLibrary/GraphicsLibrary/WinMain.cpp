#include <windows.h>
#include <cstdint>
#include <wrl/wrappers/corewrappers.h>
#include <locale.h>
//#include <cassert>
//#include <wrl/client.h>
#include <thread>
#include "RenderCore/RenderCore.h"

HWND hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
wchar_t szClassNme[] = L"ウィンドウクラス・ネーム";

static long s_Width = 1280;
static long s_Height = 960;

static Alpha::RenderCore* render = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
	LPSTR lpszCmdLine, int nCmdShow)
{
	setlocale(LC_ALL, "");

	MSG msg;
	WNDCLASS myProg;
	if (!hPreInst)
	{
		myProg.style = CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc = WndProc;
		myProg.cbClsExtra = 0;
		myProg.cbWndExtra = 0;
		myProg.hInstance = hInstance;
		myProg.hIcon = nullptr;
		myProg.hCursor = LoadCursor(nullptr, IDC_ARROW);
		myProg.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		myProg.lpszMenuName = nullptr;
		myProg.lpszClassName = szClassNme;
		if (!RegisterClass(&myProg))
			return false;
	}

	const DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	const DWORD dwExStyle = 0;
	const DWORD hasMenu = false;

	// クライアント領域サイズからウィンドウサイズを計算する。
	RECT rect;
	rect.left = 0;
	rect.right = s_Width;
	rect.top = 0;
	rect.bottom = s_Height;
	AdjustWindowRectEx(&rect, dwStyle, hasMenu, dwExStyle);

	SIZE windowSize;
	windowSize.cx = rect.right - rect.left;
	windowSize.cy = rect.bottom - rect.top;

	// 画面中央にセンタリング
	POINT windowPos;
	windowPos.x = (LONG)(GetSystemMetrics(SM_CXSCREEN) - windowSize.cx) / 2;
	windowPos.y = (LONG)(GetSystemMetrics(SM_CYSCREEN) - windowSize.cy) / 2;


	hWnd = CreateWindowEx(
		WS_EX_ACCEPTFILES,
		szClassNme,
		L"VoxelGI",
		WS_OVERLAPPEDWINDOW,
		windowPos.x,
		windowPos.y,
		windowSize.cx,
		windowSize.cy,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	render = new Alpha::RenderCore(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	float deltaTime = 1.0f / 30.0f;

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//test.Update(deltaTime);
			//test.Render();
		}
	}

	delete render;

	return (int)(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;
		uint32_t count = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
		for (uint32_t i = 0; i < count; ++i)
		{
#ifdef _UNICODE
			wchar_t filePath[512];
#else
			char filePath[512];
#endif // _UNICODE

			DragQueryFile(hDrop, i, filePath, 512);
			int a = 0;
		}
	}	break;
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}