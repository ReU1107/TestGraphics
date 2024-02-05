#pragma once
#include <cstdint>
#include <bitset>
namespace Alpha
{
	class BitFlags
	{
	private:
		std::bitset<1> a;
		uint32_t mBit;	// 
	public:
		BitFlags();
		~BitFlags();

		void OnBit(uint32_t index)
		{
			mBit |= (1 << index);
		}

		bool IsOnBit(uint32_t index) const
		{
			return (mBit & (1 << index));
		}
	};

}