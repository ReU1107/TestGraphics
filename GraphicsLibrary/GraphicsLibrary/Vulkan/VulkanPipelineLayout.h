#pragma once
#include "VulkanDevice.h"

namespace Alpha
{
	class VulkanPipelineLayout : public VulkanDeviceChild
	{

	public:
		VulkanPipelineLayout(VulkanDevice* device);
		~VulkanPipelineLayout();
	};

}