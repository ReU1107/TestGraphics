#pragma once
#include <cstdint>

namespace Alpha
{
	/*
	* �����̕]������false�̎��ɌĂ΂�܂��B
	*/
	void Assert(bool exp)
	{

	}

	void AssertArrayIndex(size_t index, size_t max)
	{
#if _DEBUG
		/*
		* �f�o�b�O���[�h�̎��Ƀ`�F�b�N���܂��B
		* Release�̎��́A�����Ȃ����Ƃ��m�肵�Ă��Ȃ��Ƃ����Ȃ��B
		*/
		if (index >= max)
		{

		}
#endif // _DEBUG

	}

}