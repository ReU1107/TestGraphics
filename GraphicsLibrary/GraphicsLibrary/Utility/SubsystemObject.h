#pragma once
#include <cassert>
namespace Alpha
{

	template<typename T>
	class SubsystemObject
	{
	private:
		static T* s_instance;
	public:
		// コンストラクタ
		SubsystemObject()
		{
		}
		// デストラクタ
		virtual ~SubsystemObject()
		{
		};
	private:
		SubsystemObject(const SubsystemObject<T>&) = delete;
		SubsystemObject(SubsystemObject<T>&&) = delete;
		SubsystemObject& operator = (const SubsystemObject<T>&) = delete;

	public:

		static void Startup()
		{
			s_instance = new T();
			assert(s_instance->Initialize());
		}

		static void Shutdown()
		{
			s_instance->Finalize();
			delete s_instance;
			s_instance = nullptr;
		}

		static T* GetPtr()
		{
			return s_instance;
		}

		static T& Get()
		{
			return *s_instance;
		}

	};

	template<typename T>
	typename T* SubsystemObject<T>::s_instance = nullptr;
}