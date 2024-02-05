#pragma once
#include <vulkan/vulkan.h>


namespace Alpha
{
	class VulkanDevice
	{
	public:
		VulkanDevice();
		~VulkanDevice();
		// �C���X�^���X�擾
		VkInstance GetVkInstance() const { return mInstance; }
		// �����f�o�C�X�擾
		VkPhysicalDevice GetVkPhysicalDevice() const { return mPhysicalDevice; }
		// �_���f�o�C�X�擾
		VkDevice GetVkDevice() const { return mDevice; }
		// 
		uint32_t GetGraphicsQueueFamilyIndex() const { return mGraphicsQueueFamilyIndex; }
	private:
		// �C���X�^���X�쐬
		void CreateInstance();
		// ����,�_���f�o�C�X�쐬
		void CreateDevice();

	private:
		VkDevice mDevice{ VK_NULL_HANDLE };						// 
		VkPhysicalDevice mPhysicalDevice{ VK_NULL_HANDLE };		//
		VkInstance mInstance{ VK_NULL_HANDLE };					// 
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
		// �C���X�^���X�擾
		VkInstance GetVkInstance() const { return mDevice->GetVkInstance(); }
		// �����f�o�C�X�擾
		VkPhysicalDevice GetVkPhysicalDevice() const { return mDevice->GetVkPhysicalDevice(); }
		// �_���f�o�C�X�擾
		VkDevice GetVkLogicalDevice() const { return mDevice->GetVkDevice(); }

		uint32_t GetGraphicsQueueFamilyIndex() const { return mDevice->GetGraphicsQueueFamilyIndex(); }

	private:
		VulkanDevice* mDevice{ nullptr };		// 
	};

//#define DeclareVulkanObject()\
//	private:\
//		VulkanDeviceObject mObject;\
//		VkInstance GetVkInstance() const { return mObject.GetVkInstance(); }\

}