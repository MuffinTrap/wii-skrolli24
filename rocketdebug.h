#pragma once

#include <mgdl/mgdl-font.h>

class RocketDebug
{
	public:
	void Init();
	void Draw(gdl::Font* font);
	void DrawThirds();
	void Free();
	float* frameTimes;
	float* cpuTimes;
	size_t index;
	const size_t size = 1024;
};
