
#include "assetmanager.h"

static AssetManager* singleton;

bool AssetManager::LoadAssets()
{
	singleton = new AssetManager();

    //singleton->ibmFont = gdl::LoadFont("assets/font8x16.png", 8, 16, ' ');

	// Items:
	// 0 imogen
	singleton->models.push_back(LoadModel("assets/train.fbx","assets/train_cut.png", gdl::Linear));
	// 1 cassette
	singleton->models.push_back(LoadModel("assets/tape_fixed.fbx", "assets/tape_cut.png", gdl::Linear));
	// 2 boombox
	singleton->models.push_back(LoadModel("assets/boombox.fbx", "assets/boombox_cut.png", gdl::Linear));
	// 3 crt
	//singleton->models.push_back(LoadModel("assets/crt.fbx", "assets/crt_text.png", gdl::Nearest));

	// 4 wii

	Model* wiiModel = LoadModel("assets/wii_fixed.fbx", "assets/wii-off_cut.png", gdl::Linear);
	wiiModel->AddTexture(gdl::LoadImage("assets/wii-on_cut.png", gdl::Linear));
	singleton->models.push_back(wiiModel);

	// 5: PC
	singleton->models.push_back(LoadModel("assets/powermac.fbx", "assets/powermac_cut.png", gdl::Linear));
	// 6: Door
	singleton->models.push_back(LoadModel("assets/door_fixed.fbx", "assets/door_cut.png", gdl::Linear));

	Model* floppyModel = LoadModel("assets/floppy_fixed.fbx", "assets/credits-muffintrap_cut.png", gdl::Linear);

	floppyModel->AddTexture(gdl::LoadImage("assets/credits-muffinhop_cut.png", gdl::Linear));
	floppyModel->AddTexture(gdl::LoadImage("assets/credits-raccoonviolet_cut.png", gdl::Linear));
	floppyModel->AddTexture(gdl::LoadImage("assets/credits-vurpo_cut.png", gdl::Linear));
	floppyModel->AddTexture(gdl::LoadImage("assets/credits-music_cut.png", gdl::Linear));
	singleton->models.push_back(floppyModel);


	// Placeholder
	// singleton->models.push_back(LoadModel("assets/camera.fbx", "assets/camera_text.png", gdl::Nearest));

	// Load background images

	// 0-2
	singleton->images.push_back(gdl::LoadImage("assets/housebg.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/skybg.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/roombg.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/emptyroombg.png", gdl::TextureFilterModes::Linear));

	// Load character images
	// 3-5
	singleton->images.push_back(gdl::LoadImage("assets/facebg.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/behind.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/front.png", gdl::TextureFilterModes::Linear));

	// Logo
	singleton->images.push_back(gdl::LoadImage("assets/marmot.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/logotext.png", gdl::TextureFilterModes::Linear));
	singleton->images.push_back(gdl::LoadImage("assets/doorface.png", gdl::TextureFilterModes::Linear));

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

