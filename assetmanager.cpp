
#include "assetmanager.h"

static Mesh* trainMesh;
static gdl::Image* texture;
static gdl::Font* ibmFont;
static gdl::Sound* music;
static Model* trainModel;

bool AssetManager::LoadAssets()
{
    // Test fbx loading
	trainMesh = new Mesh();
    trainMesh->LoadFile("assets/train.fbx");
    texture = gdl::LoadImage("assets/train_small_512.png", gdl::TextureFilterModes::Linear);
    ibmFont = gdl::LoadFont("assets/font8x16.png", 8, 16, ' ');
	music = gdl::LoadSound("plink.wav");

	trainModel = new Model();
	trainModel->AddTexturedMesh(trainMesh, texture);

	return (texture && ibmFont && music && trainModel);
}

void AssetManager::FreeAssets()
{
	delete(trainMesh);
	delete(texture);
	delete(ibmFont);
	delete(music);
	delete(trainModel);
}


gdl::Sound* AssetManager::GetMusic() { return music;}
gdl::Font* AssetManager::GetDebugFont() {return ibmFont;}
gdl::Image* AssetManager::GetImage(std::string name)
{
	if (name == "train")
	{
		return texture;
	}
	return nullptr;
}
Mesh* AssetManager::GetMesh()
{
	return trainMesh;
}

Model * AssetManager::GetModel()
{
	return trainModel;
}

