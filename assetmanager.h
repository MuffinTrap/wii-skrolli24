#pragma once
#include <mgdl.h>
#include "mgdl-mesh.h"
#include "mgdl-model.h"

class AssetManager
{
public:
	static gdl::Sound* GetMusic();
	static gdl::Font* GetDebugFont();
	static gdl::Image* GetImage(std::string name);
	static Mesh* GetMesh();
	static Model* GetModel();

	static bool LoadAssets();
	static void FreeAssets();
};
