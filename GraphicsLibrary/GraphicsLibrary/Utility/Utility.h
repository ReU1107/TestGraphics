#pragma once

namespace Alpha
{
	template<typename T, typename U>
	inline T Alignment(T base, U alignment)
	{
		return ((base + alignment - 1) / alignment) * alignment;
	}

	// ˆø”–¢g—p‚ÌŒx‘Îô
	template<typename T>
	inline void UnusedArgment(T t)
	{
		(t);
	}

	/*
	* ƒCƒ“ƒfƒbƒNƒX‚Ì•ÏX(0,1)
	*/
	template<typename T>
	inline void SwapIndex(T& current)
	{
		current = (1 - current);
	}

	/*
	* index‚Ì•ÏX(0`max)
	*/
	template<typename T, typename U = T>
	inline void SwapIndex(T& current, const U max)
	{
		current = (current + 1) % max;
	}

	/**
	 * @brief “ñ‚Â‚Ì’l‚ğ”äŠr‚µ‚ÄA”äŠr‚ªˆê’v‚µ‚Ä‚¢‚é‚È‚çˆø”1‚ğA•sˆê’v‚È‚çˆø”2‚ğ•Ô‚·ŠÖ”
	 *
	 * @tparam T ˆø”‚ÌŒ^
	 * @tparam U ˆø”‚ÌŒ^
	 * @param lhs ”äŠr‘ÎÛ1
	 * @param rhs ”äŠr‘ÎÛ2
	 * @return T ”äŠr‚ªˆê’v‚µ‚Ä‚¢‚é‚È‚çˆø”3‚ğA•sˆê’v‚È‚çˆø”4‚ğ•Ô‚·
	 * rt = result true
	 * rf = result false
	 */
	template<typename T,typename U = T>
	inline U Compare(const T lhs, const T rhs, const U rt = lhs, const U rf = rhs)
	{
		return (lhs == rhs) ? rt : rf;
	}

}