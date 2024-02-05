#pragma once

#if RHI_D3D12
#include "D3D12/D3D12Dynamic.h"
namespace Alpha 
{ 
	using RenderHardwareInterface = D3D12Dynamic; 
}
#elif RHI_VK
#include "Vulkan/VulkanDynamic.h"
namespace Alpha
{
	using RenderHardwareInterface = VulkanDynamic;
}
#endif
