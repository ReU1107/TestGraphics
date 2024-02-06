#pragma once

namespace Alpha
{
	template<typename T, typename U>
	inline T Alignment(T base, U alignment)
	{
		return ((base + alignment - 1) / alignment) * alignment;
	}

	// �������g�p�̌x���΍�
	template<typename T>
	inline void UnusedArgment(T t)
	{
		(t);
	}

	/*
	* �C���f�b�N�X�̕ύX(0,1)
	*/
	template<typename T>
	inline void SwapIndex(T& current)
	{
		current = (1 - current);
	}

	/*
	* index�̕ύX(0�`max)
	*/
	template<typename T, typename U = T>
	inline void SwapIndex(T& current, const U max)
	{
		current = (current + 1) % max;
	}

	/**
	 * @brief ��̒l���r���āA��r����v���Ă���Ȃ����1���A�s��v�Ȃ����2��Ԃ��֐�
	 *
	 * @tparam T �����̌^
	 * @tparam U �����̌^
	 * @param lhs ��r�Ώ�1
	 * @param rhs ��r�Ώ�2
	 * @return T ��r����v���Ă���Ȃ����3���A�s��v�Ȃ����4��Ԃ�
	 * rt = result true
	 * rf = result false
	 */
	template<typename T,typename U = T>
	inline U Compare(const T lhs, const T rhs, const U rt = lhs, const U rf = rhs)
	{
		return (lhs == rhs) ? rt : rf;
	}

}