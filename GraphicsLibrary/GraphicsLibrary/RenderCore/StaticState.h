#pragma once

namespace Alpha
{
	template<typename Type, typename RHI>
	class TStaticState
	{
	public:
		TStaticState()
		{
			RHI rhi = Type::CreateState();
		}

		static RHI GetRHI()
		{
			return;
		}
	};


	class BlendStateRef;

	template<bool AlphaToCoverage = false>
	class TStaticBlendState : public TStaticState<TStaticBlendState<AlphaToCoverage>, BlendStateRef>
	{
	public:

		TStaticBlendState()
		{

		}

		static BlendStateRef CreateState()
		{
			BlendStateDesc desc = {};
			desc.


				//return CreateState();
		}

	};
}