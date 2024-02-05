#pragma once

// レンダーターゲット指定
enum class ERenderTargets
{
	BackBuffer = 0x00,
	BaseColor = 0x01,
	Metalic = 0x02,
	Specular = 0x04,
	Roughness = 0x08,
	Emissive = 0x10,

	Deferred = BaseColor | Metalic | Specular | Roughness | Emissive

};