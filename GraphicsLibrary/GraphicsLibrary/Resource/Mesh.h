#pragma once
#include "Math/Vector.h"
#include <vector>

namespace Alpha
{
	using Vector2Array = std::vector<float2>;
	using Vector3Array = std::vector<float3>;

	class Mesh
	{
	private:
		Vector3Array m_positions;	// 頂点座標
		Vector3Array m_normals;		// 頂点法線
		Vector2Array m_texcoords;	// 頂点UV
	public:


	};
	/*
	* ステージングバッファを作成し
	* GPUにデータを渡す
	* そこからCPUからアクセスはしないものにコピーを行う。
	*/

}