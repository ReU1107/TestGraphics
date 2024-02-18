#pragma once
#include <cstdint>

#include "RHITypes.h"

#ifdef _WIN64
#include <Windows.h>
#endif

namespace Alpha
{
	struct RHIBufferDesc
	{
		uint32_t Stride;
		uint32_t Size;
		EBufferUsage Usage;

	};

	struct RHITextureDesc
	{

	};

	struct RHISwapchainDesc
	{
#ifdef _WIN64
		HWND hWnd;
#endif

	};

	struct RHICommandBufferDesc
	{
		uint32_t Count;
	};

	struct RHICommandQueueDesc
	{

	};

	struct RHIShaderDesc
	{

		const char* path;
	};

	struct RHIDescriptorHeapDesc
	{
		struct
		{
			ERHIResourceViewType ViewType;	// 
			uint32_t ReservationCount;		// 予約数
		}Parameters[10];
		uint32_t ParameterCount{ 0 };
	};

	struct RHIDescriptorLayoutDesc
	{
		struct
		{
			uint32_t RegisterIndex{ 0 };		// この番号は
			uint32_t ResourceCount{ 0 };		// この数だけ
			ERHIResourceViewType ViewType;		// この種類のリソースをバインドする
			ERHIShaderFlags ShaderFlags;		// 使用するシェーダーはこれ
		}Parameters[10];
		uint32_t ParameterCount{ 0 };
	};

	struct RHIDescriptorViewDesc
	{
		RHIDescriptorHeap* Heap{ nullptr };
		RHIDescriptorLayout* Layouts[4];
		uint32_t LayoutCount{ 0 };

	};

	struct RHIPipelineLayoutDesc
	{
		RHIDescriptorLayout* Layouts[4];
		uint32_t LayoutCount{ 0 };
	};

	struct RHIGraphicsPipelineDesc
	{
		RHIShader* VertexShader{ nullptr };
		RHIShader* PixelShader{ nullptr };
		RHIDescriptorView* View{ nullptr };
		struct
		{
			uint32_t BindIndex{ 0 };
			uint32_t Offset{ 0 };
		};
	};

}