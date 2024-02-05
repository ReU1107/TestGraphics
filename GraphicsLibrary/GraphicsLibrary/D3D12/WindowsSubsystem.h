#pragma once
#include <Windows.h>
#include "Utility/SubsystemObject.h"

class WindowsSubsystem// : public SubsystemObject<WindowsSubsystem>
{
private:
	HWND m_hWnd;
	UINT m_width;	// �E�B���h�E�T�C�Y
	UINT m_height;	// �E�B���h�E�T�C�Y


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

	// �{���̓N���G�C�g�֐�������肽��������͊���(���C�����[�v��������������)
};