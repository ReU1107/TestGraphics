#pragma once
#include <memory>
#include <wrl.h>

namespace Alpha
{
	template<typename T>
	using UniquePtr = std::unique_ptr<T>;

	template<typename T>
	using SharedPtr = std::shared_ptr<T>;

	template<typename T>
	using WeakPtr = std::weak_ptr<T>;

	/*
	*
	*/
	class RawPtr
	{
	private:

	};

	using Microsoft::WRL::ComPtr;
}

#define AlphaDelete(data) if(data != nullptr) delete data; data = nullptr
#define AlphaDeleteArray(arr) do { if(arr) { delete[] (arr); (arr) = nullptr; } } while(false)
