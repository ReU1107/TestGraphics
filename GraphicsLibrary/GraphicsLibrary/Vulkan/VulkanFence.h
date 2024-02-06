#pragma once
#include "VulkanDevice.h"
#include "RHI/RHIFence.h"

namespace Alpha
{
	class VulkanFence : public RHIFence, public VulkanDeviceObject
	{
	private:
		VkFence mFence;


	public:
		VulkanFence(VulkanDevice* device);
		~VulkanFence();

		void Create();

	};
}