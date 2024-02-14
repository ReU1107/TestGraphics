#pragma once
#include "RHI/RHITexture.h"
#include "VulkanDevice.h"

namespace Alpha
{
	class VulkanTexture : public RHITexture, public VulkanDeviceObject
	{
	private:
		VkImage mImage{ VK_NULL_HANDLE };
		VkDeviceMemory mMemory{ VK_NULL_HANDLE };


	};

}