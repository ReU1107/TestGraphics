#include "VulkanDevice.h"
#include <vector>
#include <string>
#include <sstream>
#include <Windows.h>

namespace Alpha
{
	VulkanDevice::VulkanDevice()
	{
		CreateInstance();
		CreateDevice();
	}

	VulkanDevice::~VulkanDevice()
	{
		vkDestroyDevice(mDevice, nullptr);
		
		vkDestroyInstance(mInstance, nullptr);
	}

	PFN_vkCreateDebugReportCallbackEXT	g_fCreateDebugReportCallback = VK_NULL_HANDLE;
	PFN_vkDestroyDebugReportCallbackEXT	g_fDestroyDebugReportCallback = VK_NULL_HANDLE;
	PFN_vkDebugReportMessageEXT			g_fDebugBreakCallback = VK_NULL_HANDLE;
	VkDebugReportCallbackEXT			g_fMsgCallback;

	VkBool32 DebugMessageCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t srcObject,
		size_t location,
		int32_t msgCode,
		const char* pLayerPrefix,
		const char* pMsg,
		void* pUserData)
	{
		std::string message;
		{
			std::stringstream buf;
			if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
				buf << "ERROR: ";
			}
			else if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
				buf << "WARNING: ";
			}
			else if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
				buf << "PERF: ";
			}
			else {
				return false;
			}
			buf << "[" << pLayerPrefix << "] Code " << msgCode << " : " << pMsg;
			message = buf.str();
		}
		MessageBoxA(nullptr, message.c_str(), "ErrorMessage", MB_OK);
		

		return false;
	}

	void VulkanDevice::CreateInstance()
	{
		VkApplicationInfo application_info = {};
		application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		application_info.pNext = nullptr;
		//�A�v���P�[�V�����̖��O
		application_info.pApplicationName = "TestVulkan";
		//�A�v���P�[�V�����̃o�[�W����
		application_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		//�G���W���̖��O
		application_info.pEngineName = "engine";
		//�G���W���̃o�[�W����;
		application_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		//�g�p����Vulkan�̃o�[�W������Vulkan 1.3�ɂ���
		application_info.apiVersion = VK_API_VERSION_1_3;
		//�o���f�[�V�������C���[���g��
		std::vector< const char* > layers
		{
			"VK_LAYER_KHRONOS_validation"
		};

		std::vector<const char* > extensions
		{
			"VK_KHR_surface",
			"VK_KHR_win32_surface", 
			"VK_EXT_debug_report" 
		};

		VkInstanceCreateInfo instance_info = {};
		instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instance_info.pNext = nullptr;
		instance_info.flags = 0;
		// �A�v���P�[�V�����̏����w��
		instance_info.pApplicationInfo = &application_info;
		// �g�p���郌�C���[���w��
		instance_info.enabledLayerCount = (uint32_t)layers.size();
		instance_info.ppEnabledLayerNames = layers.data();
		// �g��
		instance_info.enabledExtensionCount = (uint32_t)extensions.size();
		instance_info.ppEnabledExtensionNames = extensions.data();
		VkInstance instance;
		// �C���X�^���X���쐬
		
		auto result = vkCreateInstance(&instance_info,
			nullptr,
			&instance
		);
		if (result != VK_SUCCESS)
		{

		}
		mInstance = instance;
	}
	
	void VulkanDevice::CreateDevice()
	{
		auto instance = mInstance;
		// �����f�o�C�X(GPU�̎擾)
		// �f�o�C�X�̌����擾
		uint32_t device_count = 0;
		if (vkEnumeratePhysicalDevices(instance, &device_count, nullptr) != VK_SUCCESS)
		{
		}
		// �f�o�C�X�̏����擾
		std::vector< VkPhysicalDevice > devices(device_count);

		if (vkEnumeratePhysicalDevices(instance, &device_count, devices.data()) != VK_SUCCESS)
		{

		}
		VkPhysicalDevice physical_device = devices[0];
		uint32_t queue_props_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_props_count, nullptr);
		std::vector< VkQueueFamilyProperties > queue_props(queue_props_count);
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_props_count, queue_props.data());

		uint32_t queue_family_index = 0;
		// �O���t�B�b�N�X�v�����󂯕t����L���[��T��
		for (uint32_t i = 0; i < queue_props.size(); ++i)
		{
			if (queue_props[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
			{
				queue_family_index = i;
			}
		}

		mGraphicsQueueFamilyIndex = queue_family_index;

		const float priority = 0.0f;
		// �f�o�C�X�L���[
		VkDeviceQueueCreateInfo queue_info = {};
		queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_info.pNext = nullptr;
		queue_info.flags = 0;
		queue_info.queueFamilyIndex = queue_family_index;
		queue_info.queueCount = 1;
		queue_info.pQueuePriorities = &priority;

		
		std::vector< const char* > extension{
			"VK_KHR_swapchain",	// Swapchain���쐬����̂ɕK�v
		};

		// �_���f�o�C�X�����
		VkDeviceCreateInfo device_info = {};
		device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_info.pNext = nullptr;
		device_info.flags = 0;
		device_info.queueCreateInfoCount = 1;
		device_info.pQueueCreateInfos = &queue_info;
		device_info.enabledLayerCount = 0;
		device_info.ppEnabledLayerNames = nullptr;
		device_info.enabledExtensionCount = (uint32_t)extension.size();
		device_info.ppEnabledExtensionNames = extension.data();
		device_info.pEnabledFeatures = nullptr;
		VkDevice device;
		auto result = vkCreateDevice(
			physical_device,
			&device_info,
			nullptr,
			&device
		);
		if (result != VK_SUCCESS)
		{

		}

		mPhysicalDevice = physical_device;
		mDevice = device;

		g_fCreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		g_fDestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		g_fDebugBreakCallback = (PFN_vkDebugReportMessageEXT)vkGetInstanceProcAddr(instance, "vkDebugReportMessageEXT");

		VkDebugReportCallbackCreateInfoEXT dbgCreateInfo = {};
		dbgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		dbgCreateInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)DebugMessageCallback;
		dbgCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

		VkResult err = g_fCreateDebugReportCallback(instance, &dbgCreateInfo, nullptr, &g_fMsgCallback);
	}
}