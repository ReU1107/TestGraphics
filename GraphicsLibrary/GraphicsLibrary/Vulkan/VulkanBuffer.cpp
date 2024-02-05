#include "VulkanBuffer.h"
#include <string.h>
#include <vector>
namespace Alpha
{
	static int GetVkUsageFlags(const EBufferUsage usage)
	{
		int flags = {};

		if (EnumHasFlag(usage, EBufferUsage::Vertex))
		{
			flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		}

		if (EnumHasFlag(usage, EBufferUsage::Index))
		{
			flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
		}

		if (EnumHasFlag(usage, EBufferUsage::Uniform))
		{
			flags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		}

		// ステージングバッファ以外は基本的にDST指定
		if (EnumHasFlag(usage, EBufferUsage::Staging))
		{
			flags |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		}
		else
		{
			flags |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
		}


		return flags;
	}


	VulkanBuffer::VulkanBuffer(VulkanDevice* device, uint32_t stride, uint32_t size, EBufferUsage usage)
		: RHIBuffer(stride, size, usage)
		, VulkanDeviceObject(device)
	{

	}

	VulkanBuffer::~VulkanBuffer()
	{
		auto device = GetVkLogicalDevice();

		if (mBuffer)
			vkDestroyBuffer(device, mBuffer, nullptr);
		if (mMemory)
			vkFreeMemory(device, mMemory,nullptr);
	}

	void VulkanBuffer::CreateObject()
	{
		auto device = GetVkLogicalDevice();

		// バッファオブジェクト作成
		VkBufferCreateInfo buffer_info = {};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = GetSize();

		buffer_info.usage = GetVkUsageFlags(GetUsage());

		VkBuffer buffer = VK_NULL_HANDLE;
		vkCreateBuffer(device, &buffer_info, nullptr, &buffer);


		// メモリの確保
		VkMemoryAllocateInfo memory_info{};
		memory_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		VkMemoryRequirements memory_requirements = {};
		vkGetBufferMemoryRequirements(device, buffer, &memory_requirements);
		memory_info.allocationSize = memory_requirements.size;

		//VkPhysicalDeviceMemoryProperties;
		//vkGetPhysicalDeviceMemoryProperties();
		//memory_info.memoryTypeIndex = (memory_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		VkDeviceMemory memory = VK_NULL_HANDLE;
		vkAllocateMemory(device, &memory_info, nullptr, &memory);

		// バッファとメモリの関連付け
		vkBindBufferMemory(device, buffer, memory, 0);

		mBuffer = buffer;
		mMemory = memory;
		mMemorySize = memory_info.allocationSize;
	}

	void VulkanBuffer::TransferData(void* transfer_data)
	{
		auto device = GetVkLogicalDevice();
		auto memory = mMemory;
		auto size = mMemorySize;
		// データのコピー
		void* data = nullptr;
		auto result = vkMapMemory(device, memory, 0, size, 0, &data);
		if (result != VK_SUCCESS)
		{

		}
		memcpy(data, transfer_data, GetSize());
		vkUnmapMemory(device, memory);
	}

}