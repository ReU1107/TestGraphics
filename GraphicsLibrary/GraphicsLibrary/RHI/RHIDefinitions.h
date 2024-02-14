#pragma once
#include <cstdint>

#include "RHIResource.h"

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
			ERHIResourceType ResourceType;	// 
			uint32_t ReservationCount;		// 予約数
		}Parameter[10];
		uint32_t ParameterCount{ 0 };
	};

}