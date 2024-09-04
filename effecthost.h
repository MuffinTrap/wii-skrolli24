#pragma once

#include "mgdl-mesh.h"
#include <vector>

enum EffectName
{
	fxTitle = 0,
	fxHouse = 1,
	fxRoom = 2,
	fxEmptyRoom = 3,
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


	EffectName activeEffect;
	int visibleItem;
	std::vector<Mesh*> items;
};
