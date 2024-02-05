#pragma once
#include <Windows.h>
#include "Utility/SubsystemObject.h"

class WindowsSubsystem// : public SubsystemObject<WindowsSubsystem>
{
private:
	HWND m_hWnd;
	UINT m_width;	// ウィンドウサイズ
	UINT m_height;	// ウィンドウサイズ


public:
	WindowsSubsystem();
	~WindowsSubsystem();

	void SetHandle(HWND hWnd) { m_hWnd = hWnd; }
	void SetWidth(UINT width) { m_width = width; }
	void SetHeight(UINT height) { m_height = height; }


	HWND GetHandle() const { return m_hWnd; }
	UINT GetWidth() const { return m_width; }
	UINT GetHeight() const { return m_height; }

	bool Initialize() { return true; }

	void Finalize() {}

	// 本当はクリエイト関数等を作りたいが今回は割愛(メインループ等も実装したい)
};