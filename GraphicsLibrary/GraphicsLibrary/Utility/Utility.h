#pragma once

namespace Alpha
{
	template<typename T, typename U>
	inline T Alignment(T base, U alignment)
	{
		return ((base + alignment - 1) / alignment) * alignment;
	}

	// 引数未使用の警告対策
	template<typename T>
	inline void UnusedArgment(T t)
	{
		(t);
	}

	/*
	* インデックスの変更(0,1)
	*/
	template<typename T>
	inline void SwapIndex(T& current)
	{
		current = (1 - current);
	}

	/*
	* indexの変更(0～max)
	*/
	template<typename T, typename U = T>
	inline void SwapIndex(T& current, const U max)
	{
		current = (current + 1) % max;
	}

	/**
	 * @brief 二つの値を比較して、比較が一致しているなら引数1を、不一致なら引数2を返す関数
	 *
	 * @tparam T 引数の型
	 * @tparam U 引数の型
	 * @param lhs 比較対象1
	 * @param rhs 比較対象2
	 * @return T 比較が一致しているなら引数3を、不一致なら引数4を返す
	 * rt = result true
	 * rf = result false
	 */
	template<typename T,typename U = T>
	inline U Compare(const T lhs, const T rhs, const U rt = lhs, const U rf = rhs)
	{
		return (lhs == rhs) ? rt : rf;
	}

}