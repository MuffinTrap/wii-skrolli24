#pragma once

#include "mgdl-mesh.h"
#include <vector>
#include "rocketdebug.h"

enum EffectName
{
	fxTitle = 0,
	fxBgAndItem = 1,
	//////////////////////////
	fxQUIT_DEMO = 999
};

class EffectHost
{
public:
	EffectHost();
	void Init();
	void Update();
	void Draw();
	void Save();
	void Free();

private:
	void StartDraw3D();
	void DrawText();
	void DrawBackground();
	void DrawItem();
	EffectName activeEffect;
	RocketDebug rocketDebug;
};
