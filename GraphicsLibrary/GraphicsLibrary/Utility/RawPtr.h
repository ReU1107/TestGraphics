#pragma once
#include <cstdint>

namespace Alpha
{
	class RawPtr
	{
	private:
		uint8_t* m_addr;			// 
		uint64_t m_byteOffset;		// 
	public:
		RawPtr(uint8_t* data)
			: m_addr(nullptr)
			, m_byteOffset(0)
		{

		}

		~RawPtr()
		{
			// このクラスはポインター先の管理者ではないためdeleteを呼ばない
			m_addr = nullptr;
		}

		template<typename T>
		T* GetPtr()
		{
			return reinterpret_cast<T*>(m_addr + m_byteOffset);
		}

		void SetOffset(uint64_t offset)
		{
			m_byteOffset = offset;
		}

		template<typename T>
		void StepOffset(uint32_t num = 1)
		{
			m_byteOffset += sizeof(T) * num;
		}

	};

}