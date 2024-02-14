#pragma once
#include <vector>

namespace Alpha
{
	class ParticleModule;

	class Particle
	{
	private:
		std::vector<ParticleModule*> mModules;	// ���̃p�[�e�B�N���𓮂������W���[���z��
		// �p�[�e�B�N���̐�

	public:
		// ���W���[���̃o�b�t�@����
		uint32_t GetModuleBufferSize() const;
	};

	class Shape;

	class Effect
	{
	private:
		Particle* mParticle;
		// �`��`��

	};

	struct ParticleData
	{

	};

	struct EmitterData
	{
		// �ǂ̃p�[�e�B�N���𓮂�����
	};

	class UniformBuffer;
	// �p�[�e�B�N���̃o�b�t�@�Ȃ񂩂��Ǘ�����
	class ParticleSystem
	{
		UniformBuffer* m;// CPU,GPU�̎󂯓n����S������
		// GPU�ɂ����Ă���f�[�^
	};

}