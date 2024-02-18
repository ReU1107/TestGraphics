#pragma once
#include "RHIDeclarations.h"

namespace Alpha
{
	class RHIDescriptorHeap
	{
	public:
		virtual ~RHIDescriptorHeap() {}

		virtual void Create(const RHIDescriptorHeapDesc& desc) = 0;
	};

}