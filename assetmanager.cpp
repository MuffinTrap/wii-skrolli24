
#include "assetmanager.h"

static AssetManager* singleton;

bool AssetManager::LoadAssets()
{
	singleton = new AssetManager();

    singleton->ibmFont = gdl::LoadFont("assets/font8x16.png", 8, 16, ' ');


	// Placeholders
	singleton->models.push_back(LoadModel("assets/crt.fbx", "assets/crt_text.png", gdl::Nearest));
	singleton->models.push_back(LoadModel("assets/camera.fbx", "assets/camera_text.png", gdl::Nearest));
	singleton->models.push_back(LoadModel("assets/wii_console.fbx", "assets/wii_console_text.png", gdl::Nearest));

	// Ready
	singleton->models.push_back(LoadModel("assets/train.fbx","assets/train_small_512.png", gdl::Linear));
	// missing textures
	singleton->models.push_back(LoadModel("assets/cassette.fbx", "assets/test_texture.png", gdl::Nearest));
	singleton->models.push_back(LoadModel("assets/powermac.fbx", "assets/test_texture.png", gdl::Nearest));
	singleton->models.push_back(LoadModel("assets/boombox.fbx", "assets/test_texture.png", gdl::Nearest));

	// Load background images

	singleton->images.push_back(gdl::LoadImage("assets/housebg.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/roombg.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/front.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/behind.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/facebg.png", gdl::TextureFilterModes::Linear));

#ifdef GEKKO
	#ifdef SYNC_PLAYER
		singleton->music = gdl::LoadOgg("assets/chillstep.ogg");
	#endif
#else
	singleton->music = gdl::LoadSound("assets/chillstep.wav");
#endif


	return true;
}
Model * AssetManager::LoadModel(std::string fbx, std::string png, gdl::TextureFilterModes filter)
{
	Mesh* aMesh = new Mesh();
    aMesh->LoadFile(fbx.c_str());
	gdl::Image* aTexture = gdl::LoadImage(png.c_str(), filter);

	Model* aModel = new Model();
	aModel->AddTexturedMesh(aMesh, aTexture);
	return aModel;
}

void AssetManager::FreeAssets()
{
	delete(singleton);
}


AssetManager::~AssetManager()
{
	delete(ibmFont);
	delete(music);
	for(gdl::Image* image : images)
	{
		delete(image);
	}
	for(Model* model : models)
	{
		delete(model);
	}
}

gdl::Sound* AssetManager::GetMusic() { return singleton->music;}
gdl::Font* AssetManager::GetDebugFont() {return singleton->ibmFont;}
gdl::Image* AssetManager::GetImage(int index)
{
	if (index >=0 && index < (int)singleton->images.size())
	{
		return singleton->images[index];
	}
	return nullptr;
}

Model * AssetManager::GetModel(int index)
{
	if (index >=0 && index < (int)singleton->models.size())
	{
		return singleton->models[index];
	}
	return nullptr;
}

