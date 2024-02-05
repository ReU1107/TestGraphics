#pragma once
#include "VulkanDevice.h"
#include "RHI/RHIResource.h"

namespace Alpha
{
	class VulkanBuffer : public RHIBuffer, public VulkanDeviceObject
	{
	private:
		VkDeviceMemory	mMemory{ VK_NULL_HANDLE };
		VkBuffer		mBuffer{ VK_NULL_HANDLE };

		uint32_t		mMemorySize{ 0 };
	public:
		VulkanBuffer(VulkanDevice* device, uint32_t stride, uint32_t size, EBufferUsage usage);
		virtual ~VulkanBuffer();

		virtual void CreateObject() override final;
		virtual void TransferData(void* transfer_data) override final;
	};
}