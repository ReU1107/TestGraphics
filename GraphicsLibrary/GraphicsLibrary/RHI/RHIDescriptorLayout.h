#pragma once
#include "RHIDeclarations.h"

namespace Alpha
{
	class RHIDescriptorLayout
	{
	public:
		virtual ~RHIDescriptorLayout() {}

		virtual void Create(RHIDescriptorLayoutDesc& desc) = 0;
	};

}