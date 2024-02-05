#pragma once
#include <cstdint>

namespace Alpha
{
	/*
	* 引数の評価式がfalseの時に呼ばれます。
	*/
	void Assert(bool exp)
	{

	}

	void AssertArrayIndex(size_t index, size_t max)
	{
#if _DEBUG
		/*
		* デバッグモードの時にチェックします。
		* Releaseの時は、超えないことが確定していないといけない。
		*/
		if (index >= max)
		{

		}
#endif // _DEBUG

	}

}