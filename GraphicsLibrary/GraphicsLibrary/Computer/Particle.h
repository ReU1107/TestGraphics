#pragma once
#include <vector>

namespace Alpha
{
	class ParticleModule;

	class Particle
	{
	private:
		std::vector<ParticleModule*> mModules;	// このパーティクルを動かすモジュール配列
		// パーティクルの数

	public:
		// モジュールのバッファ総数
		uint32_t GetModuleBufferSize() const;
	};

	class Shape;

	class Effect
	{
	private:
		Particle* mParticle;
		// 描画形状

	};

	struct ParticleData
	{

	};

	struct EmitterData
	{
		// どのパーティクルを動かすか
	};

	class UniformBuffer;
	// パーティクルのバッファなんかを管理する
	class ParticleSystem
	{
		UniformBuffer* m;// CPU,GPUの受け渡しを担当する
		// GPUにおいてあるデータ
	};

}