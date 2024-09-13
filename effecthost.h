#pragma once

#include "mgdl-mesh.h"
#include <vector>
#include "rocketdebug.h"

enum EffectName
{
	fxTitle = 0, 	// Show the logo or something special
	fxBgAndItem = 1,
	fxBgAndImage = 2,
	fxCredits = 3, // In case no cassette/floppy credits
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
	bool quitRequested;

private:
	void StartDraw3D();
	void DrawText();
	void DrawImage();
	void DrawBackground();
	void DrawItem();
	void DrawFade();
	EffectName activeEffect;
	RocketDebug rocketDebug;
};
