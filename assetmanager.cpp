
#include "assetmanager.h"

static AssetManager* singleton;

bool AssetManager::LoadAssets()
{
	singleton = new AssetManager();

    singleton->ibmFont = gdl::LoadFont("assets/font8x16.png", 8, 16, ' ');

	// Items:
	// 0 imogen
	singleton->models.push_back(LoadModel("assets/train.fbx","assets/train_small_512.png", gdl::Linear));
	// 1 cassette
	singleton->models.push_back(LoadModel("assets/tape.fbx", "assets/test_texture.png", gdl::Nearest));
	// 2 boombox
	singleton->models.push_back(LoadModel("assets/boombox.fbx", "assets/test_texture.png", gdl::Nearest));
	// 3 crt
	singleton->models.push_back(LoadModel("assets/crt.fbx", "assets/crt_text.png", gdl::Nearest));

	// 4 wii
	singleton->models.push_back(LoadModel("assets/wii_console.fbx", "assets/wii_console_text.png", gdl::Nearest));

	// 5: PC
	singleton->models.push_back(LoadModel("assets/powermac.fbx", "assets/test_texture.png", gdl::Nearest));
	// 6: Door
	singleton->models.push_back(LoadModel("assets/door.fbx", "assets/door_texture.png", gdl::Nearest));
	Model* floppyModel = LoadModel("assets/floppy.fbx", "assets/floppy_muffintrap.png", gdl::Nearest);

	floppyModel->AddTexture(gdl::LoadImage("assets/floppy_muffintrap.png", gdl::Nearest));
	floppyModel->AddTexture(gdl::LoadImage("assets/floppy_muffinhop.png", gdl::Nearest));
	floppyModel->AddTexture(gdl::LoadImage("assets/floppy_raccoonviolet.png", gdl::Nearest));
	floppyModel->AddTexture(gdl::LoadImage("assets/floppy_vurpo.png", gdl::Nearest));
	floppyModel->AddTexture(gdl::LoadImage("assets/floppy_jamendo.png", gdl::Nearest));
	singleton->models.push_back(floppyModel);


	// Placeholders
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

