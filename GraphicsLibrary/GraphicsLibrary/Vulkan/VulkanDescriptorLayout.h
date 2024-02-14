#pragma once
#include "VulkanDevice.h"

namespace Alpha
{

	class VulkanDescriptorLayout : public VulkanDeviceObject
	{
	private:


	public:
		VulkanDescriptorLayout(VulkanDevice* device);
		~VulkanDescriptorLayout();

		void Create();
	};

}