#pragma once
#include <vulkan/vulkan.h>


namespace Alpha
{
	class VulkanDevice
	{
	public:
		VulkanDevice();
		~VulkanDevice();
		// インスタンス取得
		VkInstance GetVkInstance() const { return mInstance; }
		// 物理デバイス取得
		VkPhysicalDevice GetVkPhysicalDevice() const { return mPhysicalDevice; }
		// 論理デバイス取得
		VkDevice GetVkDevice() const { return mDevice; }
		// 
		uint32_t GetGraphicsQueueFamilyIndex() const { return mGraphicsQueueFamilyIndex; }

		uint32_t GetMemoryTypeIndex(uint32_t requirements, const VkMemoryPropertyFlags flag) const;

	private:
		// インスタンス作成
		void CreateInstance();
		// 物理,論理デバイス作成
		void CreateDevice();

	private:
		VkDevice mDevice{ VK_NULL_HANDLE };						// 
		VkPhysicalDevice mPhysicalDevice{ VK_NULL_HANDLE };		//
		VkInstance mInstance{ VK_NULL_HANDLE };					// 
		VkPhysicalDeviceMemoryProperties mProperties{};			// 
		uint32_t mGraphicsQueueFamilyIndex{ 0 };				// 
		uint32_t mComputeQueueFamilyIndex{ 0 };					// 
	};

	class VulkanDeviceObject
	{
	public:
		VulkanDeviceObject(VulkanDevice* device)
			: mDevice(device)
		{

		}
		virtual ~VulkanDeviceObject()
		{
			mDevice = nullptr;
		}

	protected:
		// インスタンス取得
		VkInstance GetVkInstance() const { return mDevice->GetVkInstance(); }
		// 物理デバイス取得
		VkPhysicalDevice GetVkPhysicalDevice() const { return mDevice->GetVkPhysicalDevice(); }
		// 論理デバイス取得
		VkDevice GetVkLogicalDevice() const { return mDevice->GetVkDevice(); }

		uint32_t GetGraphicsQueueFamilyIndex() const { return mDevice->GetGraphicsQueueFamilyIndex(); }

		uint32_t GetMemoryTypeIndex(uint32_t requirements, const VkMemoryPropertyFlags flag)  const { return mDevice->GetMemoryTypeIndex(requirements, flag); }

	private:
		VulkanDevice* mDevice{ nullptr };		// 
	};

//#define DeclareVulkanObject()\
//	private:\
//		VulkanDeviceObject mObject;\
//		VkInstance GetVkInstance() const { return mObject.GetVkInstance(); }\

}