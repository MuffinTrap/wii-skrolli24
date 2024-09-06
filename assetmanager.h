#pragma once
#include <mgdl.h>
#include "mgdl-mesh.h"
#include "mgdl-model.h"
#include <vector>

class AssetManager
{
public:
	static gdl::Sound* GetMusic();
	static gdl::Font* GetDebugFont();
	static gdl::Image* GetImage(std::string name);
	static Mesh* GetMesh();
	static Model* GetModel(int imageIndex);

	static std::vector<Model*> models;

	static bool LoadAssets();
	static void FreeAssets();
};
