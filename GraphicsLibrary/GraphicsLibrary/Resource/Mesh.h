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
		Vector3Array m_positions;	// ���_���W
		Vector3Array m_normals;		// ���_�@��
		Vector2Array m_texcoords;	// ���_UV
	public:


	};
	/*
	* �X�e�[�W���O�o�b�t�@���쐬��
	* GPU�Ƀf�[�^��n��
	* ��������CPU����A�N�Z�X�͂��Ȃ����̂ɃR�s�[���s���B
	*/

}