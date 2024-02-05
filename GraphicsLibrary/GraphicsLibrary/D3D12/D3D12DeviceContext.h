#pragma once
#include <Windows.h>

class D3D12DeviceContext
{
private:
	class Impl;
	Impl* m_impl;


public:
	D3D12DeviceContext();
	~D3D12DeviceContext();

	void Startup(HWND hWnd, UINT width, UINT height);


	void Render(float color[4]);



	//void Cleanup();

	



};