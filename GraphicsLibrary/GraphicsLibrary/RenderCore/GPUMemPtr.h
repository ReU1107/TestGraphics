#pragma once
#include <cstdint>

namespace Alpha
{
	class GPUMemPtr
	{
	private:
		uint8_t* m_data;

	public:
		GPUMemPtr();
		~GPUMemPtr();

		uint8_t* Alloc(uint32_t stride, uint32_t num);

		// GPUにCPUデータの書き込み(コピー)
		void CPUData();


	};

}


/*
* class VertexBuffer
* {
*	MemPtr
* 
*/