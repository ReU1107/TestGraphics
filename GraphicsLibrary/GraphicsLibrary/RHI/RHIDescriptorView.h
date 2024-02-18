#pragma once
#include "RHIDeclarations.h"

namespace Alpha
{
	class RHIDescriptorView
	{
	public:
		virtual ~RHIDescriptorView() {};

		virtual void Create(RHIDescriptorViewDesc& desc) = 0;
	};
}