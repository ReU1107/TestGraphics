#pragma once
#include "VulkanDevice.h"
#include "RHI/RHIFence.h"

namespace Alpha
{
	class VulkanFence : public RHIFence, public VulkanDeviceChild
	{
	private:
		VkFence mFence{ VK_NULL_HANDLE };


	public:
		VulkanFence(VulkanDevice* device);
		~VulkanFence();

		void Create();

	};
}