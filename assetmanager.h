#pragma once
#include <mgdl.h>
#include "mgdl-mesh.h"
#include "mgdl-model.h"
#include <vector>


class AssetManager
{
public:
	~AssetManager();
	static gdl::Sound* GetMusic();
	static gdl::Font* GetDebugFont();
	static gdl::Image* GetImage(int index);
	static Model* GetModel(int index);

	static bool LoadAssets();
	static void FreeAssets();

	static Model* LoadModel(std::string fbx, std::string png, gdl::TextureFilterModes filter);

	gdl::Font* ibmFont;
	gdl::Sound* music;
	std::vector<Model*> models;
	std::vector<gdl::Image*> images;
};
