#pragma once
#include "RHI/RHIDescriptorHeap.h"
#include "VulkanDevice.h"

namespace Alpha
{
	class VulkanDescriptorHeap : public RHIDescriptorHeap, public VulkanDeviceObject
	{
	private:
		VkDescriptorPool mPool{ VK_NULL_HANDLE };

	public:
		VulkanDescriptorHeap(VulkanDevice* device);
		~VulkanDescriptorHeap();

		void Create(const RHIDescriptorHeapDesc& desc);


	};


}