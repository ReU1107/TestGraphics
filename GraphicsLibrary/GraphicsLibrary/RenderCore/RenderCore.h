#pragma once
#include <Windows.h>

namespace Alpha
{
	class RHIDynamic;
	/*
	* D3D12,Vulkan‚Ìˆá‚¢‚Ì‹zû(“Š‡ƒNƒ‰ƒX)
	*/
	class RenderCore
	{
	private:
		RHIDynamic* m_dynamic;

	public:
		RenderCore(HWND hWnd);
		~RenderCore();

	public:
		void Draw();


	};
}
