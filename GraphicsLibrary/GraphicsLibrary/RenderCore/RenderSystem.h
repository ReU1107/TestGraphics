#pragma once
#include <Windows.h>

class RenderSystem
{
private:
	class Impl;
	Impl* m_impl;

public:

	RenderSystem(HWND hWnd, UINT width, UINT height);
	~RenderSystem();


	void Init();

	void Load();

	void Render();

	void Test(const char* m);

	void CreateTexture(UINT width, UINT height, UINT bit, UINT8 pixels[]);

	void Translate(float dx, float dy);
};